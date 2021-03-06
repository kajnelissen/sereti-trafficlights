/* 
 * File:   Crossing.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:16
 */

#include "Road.h"
#include "ntk.h"

#ifndef CROSSING_H
#define	CROSSING_H

#ifdef	__cplusplus
extern "C" {
#endif
    
    typedef enum {
	Event1, // Drukknop ingedrukt door voetganger
	Event2, // Time-out(15sec)
	Event3, // Detecteren auto's op weg
	Event4, // Time-out(15sec), verkeerslichten op groen naar oranje
	Event5, // Time-out(5sec), verkeerslichten van oranje naar rood
        Event6, // Detecteren auto's op weg
        Event7, // Detecteren auto's op weg
        Event8 // Detecteren auto's op weg
    } eventForCrossing;	//Mogelijke gebeurtenissen (events)
    
    typedef enum {
        K1,
        K2,
        K3,
        K4,
        K5,
        K6,
        Orange2,
        Orange3,
        Orange4,
        Orange5               
    } crossingState;
    
//    static inline char *str_state(crossingState cs) {
//        static const char *strings[] = { "K1", "K2", "K3", "K4", "K5", "K6", "Orange2", "Orange3", "Orange4", "Orange5" };
//        return strings[cs];
//    }
    
    typedef struct {
        crossingState status;
        task* crossingController;	/*implementatie concurrent gedrag, actief object*/
        mailBox mailForCrossing;
        Road roads[4];
        int seconds_green;
        int seconds_orange;
    } Crossing;

    Crossing* crossing;
    
    static STD* crossing_STD = NULL;
    
    void crossing_init(Crossing* c, int countRoads);
    void add_road(Crossing* c, int i);
    
    void print_state(Crossing* c);
    
    void sendEvent_crossing(Crossing* c, eventForCrossing e);
    
    void trigger_sensor(Crossing* c, int road, int lane);
    void cancel_sensor(Crossing* c, int road, int lane);
    
    void trigger_crosswalk(Crossing* c, int road);
    void cancel_crosswalk(Crossing* c, int road);
     
#ifdef	__cplusplus
}
#endif

#endif	/* CROSSING_H */

