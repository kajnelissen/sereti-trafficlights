#include "Crossing.h"

void crossing_init(int countRoads){
        struct Crossing *ptr;
        ptr = (struct Crossing *) calloc(1, sizeof(struct Crossing ) );
        
        for(int i = 0; i < countRoads; i++){
            add_road(i);
        }
    } 
        
void add_road(int i){
    crossing.roads[i] = create_road();
}