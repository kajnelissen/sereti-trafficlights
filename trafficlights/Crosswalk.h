/* 
 * File:   Crosswalk.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:15
 */

#include "PedestrianLight.h"

#ifndef CROSSWALK_H
#define	CROSSWALK_H

struct Crosswalk{
    PedestrianLight pedestrianlight[2];
};

Crosswalk create_crosswalk(){
    Crosswalk crosswalk;
    
    for(int i = 0; i < 2; i++){
        crosswalk->pedestrianlight[i] = create_pedestrianlight();
    }
}

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* CROSSWALK_H */

