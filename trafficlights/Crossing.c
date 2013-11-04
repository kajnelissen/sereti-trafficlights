#include "Crossing.h"
#include <stdlib.h>
#include "ntk.h"



/*Crossing Actions*/

/**/
static void lightsAction1(Crossing *crossing){
    int i;
    for(i = 0; i < 4; i++){
        int j;
        for(j = 0; j < 2; j++){
            crossing->roads[i].crosswalk.pedestrianlight[j].light=GREEN;
        }
    }
}

static void lightsAction2(Crossing *crossing){
    int i;
    for(i = 0; i < 4; i++){
        int j;
        for(j = 0; j < 2; j++){
            crossing->roads[i].crosswalk.pedestrianlight[j].light=RED;
        }
    }
}

//0 = links
//1 = rechtdoor
//2 = rechts
static void lightsAction3(Crossing *crossing){
    //Road 1
    crossing->roads[0].lanes[1].trafficlight.light=GREEN;
    crossing->roads[0].lanes[2].trafficlight.light=GREEN;
    //Road 3
    crossing->roads[2].lanes[1].trafficlight.light=GREEN;
    crossing->roads[2].lanes[2].trafficlight.light=GREEN;
}


static void lightsAction4(Crossing *crossing){
    int i;
    int j;
    
    for(i = 0; i<4; i++)
    {
        for(j = 0; j<3; j++)
        {
            if(crossing->roads[i].lanes[j].trafficlight.light=GREEN)
            {
                crossing->roads[i].lanes[j].trafficlight.light=ORANGE;
            }
        }
    }
}

static void lightsAction5(Crossing *crossing){
    int i;
    int j;
    
    for(i = 0; i<4; i++)
    {
        for(j = 0; j<3; j++)
        {
              if(crossing->roads[i].lanes[j].trafficlight.light=ORANGE)
            {
                crossing->roads[i].lanes[j].trafficlight.light=RED;
            }
        }
    }
}

static void lightsAction6(Crossing *crossing){
     //Road 2
    crossing->roads[1].lanes[1].trafficlight.light=GREEN;
    crossing->roads[1].lanes[2].trafficlight.light=GREEN;
    //Road 4
    crossing->roads[3].lanes[1].trafficlight.light=GREEN;
    crossing->roads[3].lanes[2].trafficlight.light=GREEN;
}

static void lightsAction7(Crossing *crossing){
     //Road 1
    crossing->roads[0].lanes[0].trafficlight.light=GREEN;
    //Road 3
    crossing->roads[2].lanes[0].trafficlight.light=GREEN;
}

static void lightsAction8(Crossing *crossing){
     //Road 2
    crossing->roads[1].lanes[0].trafficlight.light=GREEN;
    //Road 4
    crossing->roads[3].lanes[0].trafficlight.light=GREEN;
}

/*Voetgangers groen*/
static void action1(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K1;
    lightsAction1(crossing);
}

/*Voetgangers rood - na bepaalde tijd*/
static void action2(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K6;
    lightsAction2(crossing);
}

/*Weg 1 en 3 rechtdoor en rechtsaf groen*/
static void action3(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K2;
    lightsAction3(crossing);
}

/*Alle groene lichten naar oranje*/
static void action4(void* v){
    Crossing* crossing = (Crossing*) v;
    lightsAction4(crossing);
}

/*Alle oranje lichten naar rood*/
static void action5(void* v){
    Crossing* crossing = (Crossing*) v;
    lightsAction5(crossing);
}

/*Weg 2 en 4 rechtdoor en rechtsaf groen*/
static void action6(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K3;
    lightsAction6(crossing);
}

/*Weg 1 en 3 linksaf groen*/
static void action7(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K4;
    lightsAction7(crossing);
}

/*Weg 2 en 4 linksaf groen*/
static void action8(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K5;
    lightsAction8(crossing);
}

/*Alles lichten rood*/
static void defaultAction(void* v){
    Crossing* crossing = (Crossing*) v;
    crossing->status=K6;
}

//Taak voor het vat object
static unsigned __stdcall crossingTask(void* arg){
	task* t=(task*)arg;
	Crossing* c=*((Crossing**)(getArgument_task(t)));
	eventForCrossing e;
	actionType a;

	//Zolang het vat nog bestaat, zal deze taak actief blijven
	while(!isTerminated_task(t)){
		//Wacht tot er een gebeurtenis (event) plaats heeft gevonden, mbv een mailbox
		get_mailBox(&(c->mailForCrossing),&e);

		//Zoek de status op en voer de juiste actie uit.

		//<NIEUWE TOESTAND> = lookUp_STD(<VERWIJZING NAAR STD>, <HUIDIGE TOESTAND>, <GEBEURTENIS>, <WELKE ACTIE?>)
		c->status = (crossingState)lookUp_STD(crossing_STD,c->status,e,&a);
		
		//Voer actie uit
		a(c);
	}

	return 0;
}

//void crossing_init(int countRoads){
void crossing_init(Crossing* c, int countRoads){
        //struct Crossing *ptr;
//        crossing = (struct Crossing *) calloc(1, sizeof crossing );
//        c = (struct Crossing *) calloc(1, sizeof c );
        
        if(crossing_STD==NULL){
            crossing_STD=(STD*)malloc(sizeof(STD));
            
            //create_STD(<VERWIJZING NAAR STD>, <AANTAL TOESTANDEN>, 
            //	<WELKE ACTIE STANDAARD GEDAAN WORDT BIJ EEN ONGELDIGE OVERGANG>);
            
            create_STD(crossing_STD,10,defaultAction);
            
            //Alle mogelijke overgangen toevoegen
		//addTransition_STD(<VERWIJZING NAAR STD>, <HUIDIGE TOESTAND (ENUM)>, <GEBEURTENIS>, <NIEUWE TOESTAND>, <UIT TE VOEREN ACTIE>);    
            addTransition_STD(crossing_STD, K6, Event1, K1, action1);
            addTransition_STD(crossing_STD, K1, Event2, K6, action2);
            addTransition_STD(crossing_STD, K6, Event3, K2, action3);
            addTransition_STD(crossing_STD, K2, Event4, Orange2, action4);
            addTransition_STD(crossing_STD, Orange2, Event5, K6, action5);
            addTransition_STD(crossing_STD, K6, Event6, K3, action6);
            addTransition_STD(crossing_STD, K3, Event4, Orange3, action4);
            addTransition_STD(crossing_STD, Orange3, Event5, K6, action5);
            addTransition_STD(crossing_STD, K6, Event7, K4, action7);
            addTransition_STD(crossing_STD, K4, Event4, Orange4, action4);
            addTransition_STD(crossing_STD, Orange4, Event5, K6, action5);
            addTransition_STD(crossing_STD, K6, Event8, K5, action8);
            addTransition_STD(crossing_STD, K5, Event4, Orange5, action4);
            addTransition_STD(crossing_STD, Orange5, Event5, K6, action5);
        }
        
        //Mailbox aanmaken, waar 16 berichten in passen
//	create_mailBox(&(crossing->mailForCrossing),16,sizeof(eventForCrossing));
        create_mailBox(&(c->mailForCrossing),16,sizeof(eventForCrossing));
        
        //Crossing in beginstatus brengen
//	ptr->status=K6;
        c->status=K6;
        
        //Taak creeren en starten voor het vat
//	ptr->vatController=(task*)malloc(sizeof(task));
//	create_task(ptr->crossingController,vatTask,&v,sizeof(vat*),0);
        
        int i;
        for(i = 0; i < countRoads; i++){
            add_road(c, i);
        }
        
        //Taak creeren en starten voor het vat
	c->crossingController=(task*)malloc(sizeof(task));
	create_task(c->crossingController,crossingTask,&c,sizeof(Crossing*),0);
    } 
        
void add_road(Crossing* c, int i){
    c->roads[i] = create_road();
}

//Functie om een gebeurtenis (event) te sturen naar het vat
void sendEvent_crossing(Crossing* c,eventForCrossing e){
	put_mailBox(&(c->mailForCrossing),&e);
}