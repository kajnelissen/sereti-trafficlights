#include <stdio.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <time.h>
#include "Crossing.h"
#include "manual.h"

void manual(Crossing* c) {
    printf("Starting manual run...\n\n");
    
    int road = - 1;
    int lane = -1;
    
    display_help();
    
    while ( 1 ) {
        while ( road < 0 || road > 3 ) {
            printf("Trigger something on which road? Value must be in range [0,3]\n");
            scanf("%d",&road);
        }

        while ( lane < 0 || lane > 3 ) {
            printf("Which lane? Value must be in set [1,2,3,4]\n");
            scanf("%d",&lane);
        }
        
        if ( lane == 4 ) {
            trigger_crosswalk(crossing, road);
        } else {
            trigger_sensor(crossing, road, lane - 1);
        }
    }
    
    printf("End of manual run.");
    
}

void display_help() {
    printf("Help\n====================\n\n"
            "Keys for lanes:\n--------------------\n"
//            "a :: Weg 1 - Voetgangers\n"
//            "b :: Weg 1 - Linksaf\n"
//            "c :: Weg 1 - Rechtdoor\n"
//            "d :: Weg 1 - Rechtsaf\n\n"
//            "e :: Weg 2 - Voetgangers\n"
//            "f :: Weg 2 - Linksaf\n"
//            "g :: Weg 2 - Rechtdoor\n"
//            "h :: Weg 2 - Rechtsaf\n\n"
//            "i :: Weg 3 - Voetgangers\n"
//            "j :: Weg 3 - Linksaf\n"
//            "k :: Weg 3 - Rechtdoor\n"
//            "l :: Weg 3 - Rechtsaf\n\n"
//            "m :: Weg 4 - Voetgangers\n"
//            "n :: Weg 4 - Linksaf\n"
//            "o :: Weg 4 - Rechtdoor\n"
//            "p :: Weg 4 - Rechtsaf\n\n"
            "1 :: Left\n"
            "2 :: Straight\n"
            "3 :: Right\n"
            "4 :: Pedestrian\n"
            "--------------------\n\n"
    );
}