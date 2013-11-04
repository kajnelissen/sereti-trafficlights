/* 
 * File:   TrafficLight.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:05
 */

#include "Light.h"

#ifndef TRAFFICLIGHT_H
#define	TRAFFICLIGHT_H

#ifdef	__cplusplus
extern "C" {
#endif

    typedef struct TrafficLight{
        Light light;
    } TrafficLight;

    TrafficLight create_trafficlight();
    
#ifdef	__cplusplus
}
#endif

#endif	/* TRAFFICLIGHT_H */

