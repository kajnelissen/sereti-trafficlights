/* 
 * File:   PushButton.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:11
 */

#ifndef PUSHBUTTON_H
#define	PUSHBUTTON_H

struct PushButton{
    bool status;
};

PushButton create_pushbutton(){
    PushButton pushbutton;
    pushbutton->status = false;
}

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PUSHBUTTON_H */

