/* 
 * File:   STD_Vat.c
 * Author: verheijenrc
 *
 * Created on September 25, 2013, 8:50 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "STD_Vat.h"

static STD* vatSTD=NULL; /*meta data, alle vat objecten hebben het STD gemeen!!*/

//Alle mogelijke acties worden een losse functie. Binnen deze functie kan vanalles gebeuren
static void action0(void* v){
	vat* V=(vat*)v;
	V->gasKlep=open;
	
	//via de interface naar de fysieke hardware wordt hier de gasklep daadwerkelijk geopend
}

static void action1(void* v){
	vat* V=(vat*)v;
	V->gasKlep=dicht;

	//via de interface naar de fysiek hardware wordt hier de gasklep daadwerkelijk gesloten
}

static void action2(void* v){
	vat* V=(vat*)v;
	V->losKlep=open;
	//via de interface naar de fysiek hardware wordt hier de losklep daadwerkelijk geopend
}

static void action3(void* v){
	vat* V=(vat*)v;
	V->losKlep=dicht;
	//via de interface naar de fysiek hardware wordt hier de losklep daadwerkelijk gesloten
	
	V->readyProducts++;
}

static void action4(void* v){
	vat* V=(vat*)v;
	V->gasKlep=dicht;
	//via de interface naar de fysiek hardware wordt hier de gasklep daadwerkelijk gesloten

	V->cancelledProducts++;
}

static void action5(void* v){
	vat* V=(vat*)v;
	V->cancelledProducts++;
}

//Default actie geeft aan dat er een ongeldige overgang plaats heeft gevonden
static void defaultAction(void* v){
	vat* V=(vat*)v;
	V->illegalEvents++;
}

//Taak voor het vat object
static unsigned __stdcall vatTask(void* arg){
	task* t=(task*)arg;
	vat* v=*((vat**)(getArgument_task(t)));
	eventForVat e;
	actionType a;

	//Zolang het vat nog bestaat, zal deze taak actief blijven
	while(!isTerminated_task(t)){
		//Wacht tot er een gebeurtenis (event) plaats heeft gevonden, mbv een mailbox
		get_mailBox(&(v->mailForVat),&e);

		//Zoek de status op en voer de juiste actie uit.

		//<NIEUWE TOESTAND> = lookUp_STD(<VERWIJZING NAAR STD>, <HUIDIGE TOESTAND>, <GEBEURTENIS>, <WELKE ACTIE?>)
		v->status = (vatStatus)lookUp_STD(vatSTD,v->status,e,&a);
		
		//Voer actie uit
		a(v);
	}

	return 0;
}
void create_vat(vat* v){
	//Als het vatSTD nog niet bestaat
	if(vatSTD==NULL){
		//Reserveer geheugen
		vatSTD=(STD*)malloc(sizeof(STD));

		//create_STD(<VERWIJZING NAAR STD>, <AANTAL TOESTANDEN>, 
		//	<WELKE ACTIE STANDAARD GEDAAN WORDT BIJ EEN ONGELDIGE OVERGANG>);
		create_STD(vatSTD,4,defaultAction);

		//Alle mogelijke overgangen toevoegen
		//addTransition_STD(<VERWIJZING NAAR STD>, <HUIDIGE TOESTAND (ENUM)>, <GEBEURTENIS>, <NIEUWE TOESTAND>, <UIT TE VOEREN ACTIE>);
		addTransition_STD(vatSTD, idle, vatStart, opwarmen, action0);
		addTransition_STD(vatSTD, opwarmen, vatOpTemp, reaktie, action1);
		addTransition_STD(vatSTD, reaktie, vatTijdOm, leegLopen, action2);
		addTransition_STD(vatSTD, leegLopen, vatLeeg, idle, action3);
		addTransition_STD(vatSTD, opwarmen, vatStop, idle, action4);
		addTransition_STD(vatSTD, reaktie, vatStop, idle, action5);
	}

	//Vat in beginstatus brengen
	v->status=idle;
	v->gasKlep=v->losKlep=dicht;
	v->readyProducts=v->cancelledProducts=v->illegalEvents=0;
	
	//Mailbox aanmaken, waar 10 berichten in passen
	create_mailBox(&(v->mailForVat),10,sizeof(eventForVat));

	//Taak creeren en starten voor het vat
	v->vatController=(task*)malloc(sizeof(task));
	create_task(v->vatController,vatTask,&v,sizeof(vat*),0);
}

//Functie om een gebeurtenis (event) te sturen naar het vat
void sendEvent_vat(vat* v,eventForVat e){
	put_mailBox(&(v->mailForVat),&e);
}