/* 
 * File:   main.c
 * Author: Kaj
 *
 * Created on 3 oktober 2013, 12:56
 */

#include <stdio.h>
#include <stdlib.h>
#include "Crossing.h" 
#include "simulation.h"
#include "manual.h"

#define NR_ROADS        4

/*
 * 
 */
int main(int argc, char** argv) {
    Crossing* crossing;
    int mode = 0; // run in simulated mode by default
    int key;
    int seconds;

    crossing_init(crossing, NR_ROADS);
    
    display_intro();
    
    printf("How many seconds will the lights be green?");
    scanf("%d",&seconds);
    crossing->seconds_green = seconds;
    
    printf("How many seconds will the lights be orange?");
    scanf("%d",&seconds);
    crossing->seconds_orange = seconds;
    
    printf("Press \"s\" for a simulated run, or \"m\" for a manual run.\n");

    // see http://expandinghead.net/keycode.html for key codes
    do key = getchar(); while ((key != 's') && (key != 'm'));
    if ( key == 's' ) {
        run(crossing, 0);
    } else if ( key == 'm' ) {
        run(crossing, 1);
    }
    
    return (EXIT_SUCCESS);
}

/**
 * Runs the program in the specified mode.
 * @param c     Pointer to crossing
 * @param mode  Mode to run program in (0 = simulated, 1 = manual)
 */
void run(Crossing* c, int mode) {
    if ( mode == 0 ) {
        printf("Simulated run was selected!\n");
        simulation(c);
    } else {
        printf("Manual run was selected!\n");
        manual(c);
    }
}

void display_intro() {
    printf("Course:\t\tSereti\nCase:\t\tTraffic Lights\nStudents:\tRuben Hamers, Kaj Nelissen, Erwin Vaes\n\n\n");
}
