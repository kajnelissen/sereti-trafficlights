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

#define NR_ROADS        4

/*
 * 
 */
int main(int argc, char** argv) {
    Crossing* crossing;
//    crossing_init(NR_ROADS);
    crossing_init(crossing, NR_ROADS);
    simulate(crossing);
    
    return (EXIT_SUCCESS);
}
