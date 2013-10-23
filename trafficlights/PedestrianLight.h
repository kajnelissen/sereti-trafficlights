/* 
 * File:   PedestrianLight.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:13
 */

#include "PushButton.h"
#include "Light.h"

#ifndef PEDESTRIANLIGHT_H
#define	PEDESTRIANLIGHT_H

typedef struct{
    Light light;
    PushButton pushbutton;
} PedestrianLight;

PedestrianLight create_pedestrianlight();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PEDESTRIANLIGHT_H */

