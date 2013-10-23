#include "Road.h"

Road create_road(){
    Road road;    
    road->crosswalk = create_crosswalk();  
    
    for(int i = 0; i < 3; i++){
        road->lanes[i] = create_lane();
    }
}