/* 
 * File:   Lane.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:09
 */

#include "CarSensor.h"
#include "TrafficLight.h"

#ifndef LANE_H
#define	LANE_H

typedef struct {
    CarSensor carsensor;
    TrafficLight trafficlight;
} Lane;

Lane create_lane();

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LANE_H */

