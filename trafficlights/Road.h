/* 
 * File:   Road.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:15
 */

#ifndef ROAD_H
#define	ROAD_H

#ifdef	__cplusplus
extern "C" {
#endif

    struct Road{
        Lane lanes[3];
        Crosswalk crosswalk;
    };


#ifdef	__cplusplus
}
#endif

#endif	/* ROAD_H */

