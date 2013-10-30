/* 
 * File:   simulation.h
 * Author: Kaj
 *
 * Created on 30 oktober 2013, 10:00
 */

#include <stdlib.h>
#include "Crossing.h"
#include "CarSensor.h"
#include "PushButton.h"

#ifndef SIMULATION_H
#define	SIMULATION_H

#ifdef	__cplusplus
extern "C" {
#endif


    void simulate(Crossing* c);
    
    void car(Crossing* c);


#ifdef	__cplusplus
}
#endif

#endif	/* SIMULATION_H */

