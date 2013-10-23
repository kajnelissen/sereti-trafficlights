#include "PedestrianLight.h"

PedestrianLight create_pedestrianlight(){
    PedestrianLight pedestrianlight;
    Light light;
    pedestrianlight->light = light->RED;
    pedestrianlight->pushbutton = create_pushbutton();
    
    return pedestrianlight;
}