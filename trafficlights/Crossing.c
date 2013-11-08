#include <stdio.h>
#include <stdlib.h>
#include "Crossing.h"
#include "ntk.h"
#include "Light.h"
#include "CarSensor.h"
#include "PushButton.h"


/*Crossing Actions*/

/**/
static void lightsAction1(Crossing *crossing) {
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            crossing->roads[i].crosswalk.pedestrianlight[j].light = GREEN;
        }
    }
    
    print_state(crossing);
    
    sleep(crossing->seconds_green);
}

static void lightsAction2(Crossing *crossing) {
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 2; j++) {
            crossing->roads[i].crosswalk.pedestrianlight[j].light = RED;
        }
    }
    print_state(crossing);
    sleep(crossing->seconds_orange);
//    sleep(2);
}

//0 = links
//1 = rechtdoor
//2 = rechts
static void lightsAction3(Crossing *crossing) {
    //Road 1
    crossing->roads[0].lanes[1].trafficlight.light = GREEN;
    crossing->roads[0].lanes[2].trafficlight.light = GREEN;
    //Road 3
    crossing->roads[2].lanes[1].trafficlight.light = GREEN;
    crossing->roads[2].lanes[2].trafficlight.light = GREEN;
    
    print_state(crossing);
    sleep(crossing->seconds_green);
}


static void lightsAction4(Crossing *crossing) {
    int i;
    int j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (crossing->roads[i].lanes[j].trafficlight.light == GREEN)
            {
                crossing->roads[i].lanes[j].trafficlight.light = ORANGE;
            }
        }
    }
    
    print_state(crossing);
    sleep(crossing->seconds_orange);
}

static void lightsAction5(Crossing *crossing) {
    int i;
    int j;
    
    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (crossing->roads[i].lanes[j].trafficlight.light == ORANGE)
            {
                crossing->roads[i].lanes[j].trafficlight.light = RED;
            }
        }
    }
    
    print_state(crossing);
//    sleep(2);
}

static void lightsAction6(Crossing *crossing) {
     //Road 2
    crossing->roads[1].lanes[1].trafficlight.light = GREEN;
    crossing->roads[1].lanes[2].trafficlight.light = GREEN;
    //Road 4
    crossing->roads[3].lanes[1].trafficlight.light = GREEN;
    crossing->roads[3].lanes[2].trafficlight.light = GREEN;
    
    print_state(crossing);
    sleep(crossing->seconds_green);
}

static void lightsAction7(Crossing *crossing) {
     //Road 1
    crossing->roads[0].lanes[0].trafficlight.light = GREEN;
    //Road 3
    crossing->roads[2].lanes[0].trafficlight.light = GREEN;
    
    print_state(crossing);
    sleep(crossing->seconds_green);
}

static void lightsAction8(Crossing *crossing) {
     //Road 2
    crossing->roads[1].lanes[0].trafficlight.light = GREEN;
    //Road 4
    crossing->roads[3].lanes[0].trafficlight.light = GREEN;
    
    print_state(crossing);
    sleep(crossing->seconds_green);
}

/*Voetgangers groen*/
static void action1(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K1;
    lightsAction1(crossing);
}

/*Voetgangers rood - na bepaalde tijd*/
static void action2(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K6;
    lightsAction2(crossing);
}

/*Weg 1 en 3 rechtdoor en rechtsaf groen*/
static void action3(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K2;
    lightsAction3(crossing);
}

/*Alle groene lichten naar oranje*/
static void action4(void* v) {
    Crossing* crossing = (Crossing*) v;
    lightsAction4(crossing);
}

/*Alle oranje lichten naar rood*/
static void action5(void* v) {
    Crossing* crossing = (Crossing*) v;
    lightsAction5(crossing);
}

/*Weg 2 en 4 rechtdoor en rechtsaf groen*/
static void action6(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K3;
    lightsAction6(crossing);
}

/*Weg 1 en 3 linksaf groen*/
static void action7(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K4;
    lightsAction7(crossing);
}

/*Weg 2 en 4 linksaf groen*/
static void action8(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K5;
    lightsAction8(crossing);
}

/*Alles lichten rood*/
static void defaultAction(void* v) {
    Crossing* crossing = (Crossing*) v;
    crossing->status = K6;
}

//Taak voor het vat object
static unsigned __stdcall crossingTask(void* arg) {
	task* t = (task*)arg;
	Crossing* c = *((Crossing**)(getArgument_task(t)));
	eventForCrossing e;
	actionType a;

	//Zolang het vat nog bestaat, zal deze taak actief blijven
	while (!isTerminated_task(t)) {
		//Wacht tot er een gebeurtenis (event) plaats heeft gevonden, mbv een mailbox
		get_mailBox(&(c->mailForCrossing), &e);

		//Zoek de status op en voer de juiste actie uit.

		//<NIEUWE TOESTAND> = lookUp_STD(<VERWIJZING NAAR STD>, <HUIDIGE TOESTAND>, <GEBEURTENIS>, <WELKE ACTIE?>)
		c->status = (crossingState) lookUp_STD(crossing_STD, c->status, e, &a);
		
		//Voer actie uit
		a(c);
	}

	return 0;
}

//void crossing_init(int countRoads){
void crossing_init(Crossing* c, int countRoads){
        
        if (crossing_STD == NULL) {
            crossing_STD = (STD*)malloc(sizeof(STD));
            
            //create_STD(<VERWIJZING NAAR STD>, <AANTAL TOESTANDEN>, 
            //	<WELKE ACTIE STANDAARD GEDAAN WORDT BIJ EEN ONGELDIGE OVERGANG>);
            
            create_STD(crossing_STD, 10, defaultAction);
            
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
        create_mailBox(&(c->mailForCrossing), 16, sizeof(eventForCrossing));
        
        //Crossing in beginstatus brengen
        c->status = K6;
        
        int i;
        for (i = 0; i < countRoads; i++) {
            add_road(c, i);
        }
        
        //Taak creeren en starten voor het vat
	c->crossingController = (task*)malloc(sizeof(task));
	create_task(c->crossingController, crossingTask, &c, sizeof(Crossing*), 0);
    } 
        
void add_road(Crossing* c, int i) {
    c->roads[i] = create_road();
}

void print_state(Crossing* c) {
    printf("\t> State = [%d] = ((%c, %c, %c, %c),(%c, %c, %c, %c),(%c, %c, %c, %c),(%c, %c, %c, %c))\n", 
            c->status,
            str_light(c->roads[0].crosswalk.pedestrianlight[0].light),
            str_light(c->roads[0].lanes[0].trafficlight.light),
            str_light(c->roads[0].lanes[1].trafficlight.light),
            str_light(c->roads[0].lanes[2].trafficlight.light), 
            str_light(c->roads[1].crosswalk.pedestrianlight[0].light),
            str_light(c->roads[1].lanes[0].trafficlight.light),
            str_light(c->roads[1].lanes[1].trafficlight.light),
            str_light(c->roads[1].lanes[2].trafficlight.light), 
            str_light(c->roads[2].crosswalk.pedestrianlight[0].light),
            str_light(c->roads[2].lanes[0].trafficlight.light),
            str_light(c->roads[2].lanes[1].trafficlight.light),
            str_light(c->roads[2].lanes[2].trafficlight.light), 
            str_light(c->roads[3].crosswalk.pedestrianlight[0].light),
            str_light(c->roads[3].lanes[0].trafficlight.light),
            str_light(c->roads[3].lanes[1].trafficlight.light),
            str_light(c->roads[3].lanes[2].trafficlight.light)
    );
}

//Functie om een gebeurtenis (event) te sturen naar het vat
void sendEvent_crossing(Crossing* c, eventForCrossing e){
    put_mailBox(&(c->mailForCrossing), &e);
}

void trigger_sensor(Crossing* crossing, int road, int lane) {
    change_sensor_state(&(crossing->roads[road].lanes[lane].carsensor), 1);
    printf("\nA car triggered the sensor in lane %d of road %d!\n", lane + 1, road + 1);
    
    if ( (road == 0 && lane == 1) || (road == 0 && lane == 2) || (road == 2 && lane == 1) || (road == 2 && lane == 2) ) {
        // change state to K2
        sendEvent_crossing(crossing, Event3);
        sendEvent_crossing(crossing, Event4);
        sendEvent_crossing(crossing, Event5);
    }
    
    if ( (road == 1 && lane == 1) || (road == 1 && lane == 2) || (road == 3 && lane == 1) || (road == 3 && lane == 2) ) {
        // change state to K3
        sendEvent_crossing(crossing, Event6);
        sendEvent_crossing(crossing, Event4);
        sendEvent_crossing(crossing, Event5);
    }
    
    if ( (road == 0 && lane == 0) || (road == 2 && lane == 0) ) {
        // change state to K4
        sendEvent_crossing(crossing, Event7);
        sendEvent_crossing(crossing, Event4);
        sendEvent_crossing(crossing, Event5);
    }
    
    if ( (road == 1 && lane == 0) || (road == 3 && lane == 0) ) {
        // change state to K5
        sendEvent_crossing(crossing, Event8);
        sendEvent_crossing(crossing, Event4);
        sendEvent_crossing(crossing, Event5);
    }
}

void cancel_sensor(Crossing* crossing, int road, int lane) {
    change_sensor_state(&(crossing->roads[road].lanes[lane].carsensor), 0);
}

void trigger_crosswalk(Crossing* crossing, int road) {
    change_button_state(&(crossing->roads[road].crosswalk.pedestrianlight[0].pushbutton), 1);
    change_button_state(&(crossing->roads[road].crosswalk.pedestrianlight[1].pushbutton), 1);
    printf("\nA pedestrian pressed the push button on road %d!\n", road + 1);
    
    sendEvent_crossing(crossing, Event1);
    sendEvent_crossing(crossing, Event2);
}

void cancel_crosswalk(Crossing* crossing, int road) {
    change_button_state(&(crossing->roads[road].crosswalk.pedestrianlight[0].pushbutton), 0);
    change_button_state(&(crossing->roads[road].crosswalk.pedestrianlight[1].pushbutton), 0);
}
