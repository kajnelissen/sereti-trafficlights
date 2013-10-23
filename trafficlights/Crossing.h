/* 
 * File:   Crossing.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:16
 */

#include "Road.h"

#ifndef CROSSING_H
#define	CROSSING_H

#ifdef	__cplusplus
extern "C" {
#endif

    Crossing* crossing;
    
    struct Crossing{
        //STD state;
        Road roads[4];
    };
    typedef struct Crossing Crossing;

    void crossing_init(int countRoads);
    void add_road(int i);
     
#ifdef	__cplusplus
}
#endif

#endif	/* CROSSING_H */

