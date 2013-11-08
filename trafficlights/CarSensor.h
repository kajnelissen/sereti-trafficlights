/* 
 * File:   CarSensor.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:10
 */

#ifndef CARSENSOR_H
#define	CARSENSOR_H

typedef struct {
    int status;
} CarSensor;


CarSensor create_carsensor();

void change_sensor_state(CarSensor* sensor, int state);

#ifdef	__cplusplus
extern "C" {
#endif
    

#ifdef	__cplusplus
}
#endif

#endif	/* CARSENSOR_H */

