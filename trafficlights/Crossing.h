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
    
    void crossing_init(int countRoads){
        struct Crossing *ptr;
        ptr = (struct Crossing *) calloc(1, sizeof(struct Crossing ) );
        
        for(int i = 0; i < countRoads; i++){
            add_road(i);
        }
    } 
    
    void add_road(int i){
        crossing.roads[i] = create_road();
    }

#ifdef	__cplusplus
}
#endif

#endif	/* CROSSING_H */

