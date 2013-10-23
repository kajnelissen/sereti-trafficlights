/* 
 * File:   Crosswalk.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:15
 */

#include "PedestrianLight.h"

#ifndef CROSSWALK_H
#define	CROSSWALK_H

typedef struct{
    PedestrianLight pedestrianlight[2];
} Crosswalk;

Crosswalk create_crosswalk();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CROSSWALK_H */

