#include "PedestrianLight.h"

PedestrianLight create_pedestrianlight(){
    PedestrianLight pedestrianlight;
    Light light;
    pedestrianlight.light = 0;
    pedestrianlight.pushbutton = create_pushbutton();
    
    return pedestrianlight;
}