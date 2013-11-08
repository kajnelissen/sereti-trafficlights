#include <stdio.h>
#include <stdlib.h>
#include "CarSensor.h"
#include "Crossing.h"

CarSensor create_carsensor(){
    CarSensor carsensor;
    carsensor.status = 0;
    
    return carsensor;
}

void change_sensor_state(CarSensor* sensor, int state) {
    sensor->status = state;
//    if ( state == 1 ) {
//        // trigger event
//        printf("Trigger event!\n");
//    }
}
