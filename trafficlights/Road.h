/* 
 * File:   Road.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:15
 */

#include "Crosswalk.h"
#include "Lane.h"

#ifndef ROAD_H
#define	ROAD_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef struct{
        Lane lanes[3];
        Crosswalk crosswalk;
    } Road;
    
    Road create_road();


#ifdef	__cplusplus
}
#endif

#endif	/* ROAD_H */

