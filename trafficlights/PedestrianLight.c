#include "PedestrianLight.h"

PedestrianLight create_pedestrianlight(){
    PedestrianLight pedestrianlight;
//    Light light;
    pedestrianlight.light = 2;
    pedestrianlight.pushbutton = create_pushbutton();
    
    return pedestrianlight;
}
