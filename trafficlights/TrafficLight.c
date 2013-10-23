#include "TrafficLight.h"
#include "Light.h"

TrafficLight create_trafficlight(){
    TrafficLight trafficlight;
    trafficlight.light = Light.RED;
    
    return trafficlight;
}