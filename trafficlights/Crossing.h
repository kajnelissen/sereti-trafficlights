/* 
 * File:   Crossing.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:16
 */

#ifndef CROSSING_H
#define	CROSSING_H

#ifdef	__cplusplus
extern "C" {
#endif

    struct Crossing{
        STD state;
        Road roads[4];
    };
    typedef struct Crossing Crossing;
    
    void create_crossing(Crossing* c);

#ifdef	__cplusplus
}
#endif

#endif	/* CROSSING_H */

