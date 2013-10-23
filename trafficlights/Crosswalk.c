#include "Crosswalk.h"

Crosswalk create_crosswalk(){
    Crosswalk crosswalk;
    
    int i;
    for(i = 0; i < 2; i++){
        crosswalk.pedestrianlight[i] = create_pedestrianlight();
    }
    
    return crosswalk;
}