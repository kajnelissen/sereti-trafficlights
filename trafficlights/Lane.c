#include "Lane.h"

Lane create_lane(){
    Lane lane;
    lane.carsensor = create_carsensor();
    lane.trafficlight = create_trafficlight();
}
