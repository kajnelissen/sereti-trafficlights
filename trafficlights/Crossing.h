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
    
    typedef struct {
        //STD state;
        Road roads[4];
    } Crossing;

    Crossing crossing;
    
    void crossing_init(int countRoads);
    void add_road(int i);
     
#ifdef	__cplusplus
}
#endif

#endif	/* CROSSING_H */

