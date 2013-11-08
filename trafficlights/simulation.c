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
void simulation(Crossing* crossing) {
    printf("\nStarting simulation...\n\n");
    
    int key;
    int seconds_wait = crossing->seconds_green + crossing->seconds_orange + 3;
    
    // hier iets dat auto's gaat triggeren bij willekeurige verkeerslichten
    // deze auto's triggeren het carsensor event dat bij dat verkeerslicht
    // hoort
    timeout(0);
    srand(time(NULL));
    
    while ( 1 ) {
        // break on pressing escape key (key code = 27))
//        key = getch();
//        if ( key == 27 ) {
//            break;
//        } else {
            int random = rand() % 10;
            if ( random <= 6 ) {
                sim_car(crossing);
            } else {
                sim_pedestrian(crossing);
            }
            sleep(seconds_wait);
//        }
    }
    
    printf("End of simulation.");
}

/**
 * Triggers a car sensor in one of the lanes of a road.
 * @param crossing
 */
void sim_car(Crossing* crossing) {    
    int road = rand() % 4;
    int lane = rand() % 3;
    trigger_sensor(crossing, road, lane);
}

/**
 * Triggers a push button on one of the crosswalks.
 * @param crossing
 */
void sim_pedestrian(Crossing* crossing) {
    int road = rand() % 4;
    trigger_crosswalk(crossing, road);
}
