/* 
 * File:   Light.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:08
 */

#ifndef LIGHT_H
#define	LIGHT_H

typedef enum {
    GREEN,
    ORANGE,
    RED        
} Light;

static inline char *str_light(Light l) {
    char* strings[3] = { "g", "o", "r" };
    return *strings[l];
}

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* LIGHT_H */

