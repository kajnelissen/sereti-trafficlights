#include <ncurses/curses.h>
#include "simulation.h"

/**
 * 
 * @param crossing
 */
void simulate(Crossing* crossing) {
    printf("Start simulatie...");
    
    int key;
    
    // hier iets dat auto's gaat triggeren bij willekeurige verkeerslichten
    // deze auto's triggeren het carsensor event dat bij dat verkeerslicht
    // hoort
    timeout(0);
    while ( 1 ) {
        // break on pressing escape key (key code = 27))
        key = getch();
        if ( key == 27 ) {
            break;
        } else {
            car(crossing);
        }
    }
    
    printf("Einde simulatie");
}

/**
 * Triggers a car sensor in one of the lanes of a road,
 * but only 
 * @param crossing
 */
void car(Crossing* crossing) {
    
    
    
    printf("Sensor merkt auto op!\n");
    
}


