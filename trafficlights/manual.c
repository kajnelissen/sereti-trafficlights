#include <stdio.h>
#include <stdlib.h>
#include <ncurses/curses.h>
#include <time.h>
#include "Crossing.h"
#include "manual.h"

void manual(Crossing* crossing) {
    printf("\nStarting manual run...\n\n");
    
    int road = - 1;
    int lane = -1;
    
    int seconds_wait = crossing->seconds_green + crossing->seconds_orange + 3;
    
    display_help();
    
    while ( 1 ) {
        while ( road < 1 || road > 4 ) {
            printf("\nTrigger something on which road? Value must be in range [1,4]\n");
            scanf("%d",&road);
        }

        while ( lane < 1 || lane > 4 ) {
            printf("Which lane? Value must be in range [1,4]\n");
            scanf("%d",&lane);
        }
        
        if ( lane == 4 ) {
            trigger_crosswalk(crossing, road - 1);
        } else {
            trigger_sensor(crossing, road - 1, lane - 1);
        }
        
        road = -1;
        lane = -1;
        
        sleep(seconds_wait);
    }
    
    printf("End of manual run.");
    
}

void display_help() {
    printf("Help\n====================\n"
            "Keys for lanes:\n--------------------\n"
            "1 :: Left\n"
            "2 :: Straight\n"
            "3 :: Right\n"
            "4 :: Pedestrian\n"
            "--------------------\n\n"
    );
}