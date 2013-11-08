#include "PushButton.h"

PushButton create_pushbutton(){
    PushButton pushbutton;
    pushbutton.status = 0;
    
    return pushbutton;
}

void change_button_state(PushButton* btn, int state) {
    btn->status = state;
}
