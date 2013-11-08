/* 
 * File:   PushButton.h
 * Author: Erwin
 *
 * Created on 7 oktober 2013, 23:11
 */

#ifndef PUSHBUTTON_H
#define	PUSHBUTTON_H

typedef struct{
    int status;
} PushButton;

PushButton create_pushbutton();

void change_button_state(PushButton* sensor, int state);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* PUSHBUTTON_H */

