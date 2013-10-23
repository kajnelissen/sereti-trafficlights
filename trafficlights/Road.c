#include "Road.h"

Road create_road(){
    Road road;    
    road.crosswalk = create_crosswalk();  
    
    int i;
    for(i = 0; i < 3; i++){
        road.lanes[i] = create_lane();
    }
    
    return road;
}