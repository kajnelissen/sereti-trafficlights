#include <ncurses/curses.h>
#include "simulation.h"


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
        if ( key == KEY_ENTER ) {
            break;
        }
        car(crossing);
    }
    
    printf("Einde simulatie");
}

void car(Crossing* crossing) {
    
    printf("Sensor merkt auto op!");
    
}
