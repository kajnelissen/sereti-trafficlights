#include <stdio.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <time.h>
#include "simulation.h"
#include "Road.h"
#include "Crossing.h"

/**
 * 
 * @param crossing
 */
void simulate(Crossing* crossing) {
    printf("Start simulatie...\n\n");
    
    int key;
    
    // hier iets dat auto's gaat triggeren bij willekeurige verkeerslichten
    // deze auto's triggeren het carsensor event dat bij dat verkeerslicht
    // hoort
    timeout(0);
    srand(time(NULL));
    
    while ( 1 ) {
        // break on pressing escape key (key code = 27))
        key = getch();
        if ( key == 27 ) {
            break;
        } else {
//            int random = rand() % 10000;
//            if ( random == 9999 ) {
                car_arrival(crossing);
//            }
        }
    }
    
    printf("Einde simulatie");
}

/**
 * Triggers a car sensor in one of the lanes of a road.
 * @param crossing
 */
void car_arrival(Crossing* crossing) {
    
//    struct Road r = get_road(crossing, 1);
//    struct Road* r;
//    r = (struct Road*) calloc(1, sizeof r );
//    r = get_road(crossing, 1);
    
    sleep(2);
    
    printf("Sensor merkt auto op!\n");
    
    int random = rand() % 8;
    switch (random) {
        case 0:
            printf("Event #1.\n");
            sendEvent_crossing(crossing, Event1);
            break;
        case 1:
            printf("Event #2.\n");
            sendEvent_crossing(crossing, Event2);
            break;    
        case 2:
            printf("Event #3.\n");
            sendEvent_crossing(crossing, Event3);
            break;
        case 3:
            printf("Event #4.\n");
            sendEvent_crossing(crossing, Event4);
            break;
        case 4:
            printf("Event #5.\n");
            sendEvent_crossing(crossing, Event5);
            break;
        case 5:
            printf("Event #6.\n");
            sendEvent_crossing(crossing, Event6);
            break;
        case 6:
            printf("Event #7.\n");
            sendEvent_crossing(crossing, Event7);
            break;
        case 7:
            printf("Event #8.\n");
            sendEvent_crossing(crossing, Event8);
            break;
        default:
            printf("Geen actie.\n");
            break;
    }
    
    
    
}
