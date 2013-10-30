/* 
 * File:   main.c
 * Author: Kaj
 *
 * Created on 3 oktober 2013, 12:56
 */

#include <stdio.h>
#include <stdlib.h>
#include "Crossing.h"   

/*
 * 
 */
int main(int argc, char** argv) {
    Crossing* crossing;
    crossing_init(4);
    
    printf("Als deze tekst getoond wordt heeft er een wonder voor u ogen plaatsgevonden!");
    
    return (EXIT_SUCCESS);
}