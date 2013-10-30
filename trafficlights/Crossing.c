#include "Crossing.h"
#include <stdlib.h>

void crossing_init(int countRoads){
        struct Crossing *ptr;
        ptr = (struct Crossing *) calloc(1, sizeof ptr );
        
        int i;
        for(i = 0; i < countRoads; i++){
            add_road(i);
        }
    } 
        
void add_road(int i){
    crossing.roads[i] = create_road();
}

Road get_road(Crossing* c, int i) {
    return c->roads[i];
}