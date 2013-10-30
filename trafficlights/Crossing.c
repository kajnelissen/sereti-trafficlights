#include "Crossing.h"
#include <stdlib.h>
#include "ntk.h"

static STD* crossing_STD=NULL;

/*Crossing Actions*/

/*Voetgangers groen*/
static void action1(void* v){
    
}

/*Voetgangers rood - na bepaalde tijd*/
static void action2(void* v){
    
}

/*Weg 1 en 3 rechtdoor en rechtsaf groen*/
static void action3(void* v){
    
}

/*Alle groene lichten naar oranje*/
static void action4(void* v){
    
}

/*Alle oranje lichten naar rood*/
static void action5(void* v){
    
}

/*Weg 2 en 4 rechtdoor en rechtsaf groen*/
static void action6(void* v){
    
}

/*Weg 1 en 3 linksaf groen*/
static void action7(void* v){
    
}

/*Weg 2 en 4 linksaf groen*/
static void action8(void* v){
    
}

/*Alles lichten rood*/
static void defaultAction(void* v){
    
}

void crossing_init(int countRoads){
        struct Crossing *ptr;
        ptr = (struct Crossing *) calloc(1, sizeof ptr );
        
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
        
        int i;
        for(i = 0; i < countRoads; i++){
            add_road(i);
        }
    } 
        
void add_road(int i){
    crossing.roads[i] = create_road();
}