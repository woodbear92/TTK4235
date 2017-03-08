//
//  elevatorControl.c
//  heis
//
//  Created by Vebjørn Steinsholt on 08.03.2017.
//  Copyright © 2017 Vebjørn Steinsholt. All rights reserved.
//

#include "elevatorControl.h"
int floorsAbove[N_FLOORS-1] = {-1,-1,-1};
int floorsBelow[N_FLOORS-1] = {-1,-1,-1};
int lastFloor = -1;
int requestCounterUp = 0;
int requestCounterDown = 0;
void validateCounters(){
    if (requestCounterDown > 3 ) {
        requestCounterDown = 0;
    }
    if (requestCounterUp > 3 ) {
        requestCounterUp = 0;
    }
}
void getUpOrders(){
    for(int floori = 0; floori <= N_FLOORS-2; floori++){
        if (elev_get_button_signal(BUTTON_CALL_UP, floori) == 1){
            
            if(!(isvalueinarray(floori, floorsAbove, N_FLOORS-1))){
                floorsAbove[requestCounterUp++] = floori;
            }
        }
        
    }
}
void getDownOrders(){
    for(int floori = 1; floori <= N_FLOORS-1; floori++){
        if (elev_get_button_signal(BUTTON_CALL_DOWN, floori) == 1){
            
            if(!(isvalueinarray(floori, floorsBelow, N_FLOORS-1))){
                floorsBelow[requestCounterDown++] = floori;
            }
        }
        
    }
}
bool isvalueinarray(int val, int arr[], int size){
    int i;
    for (i=0; i < size; i++) {
        if (arr[i] == val)
            return true;
    }
    return false;
}
void stop(){
if (elev_get_stop_signal()) {
    elev_set_motor_direction(DIRN_STOP);
    
}
}
void startUp(){
    clearOrdersDown();
    clearOrdersUp();
    while (elev_get_floor_sensor_signal()==-1){
        elev_set_motor_direction(DIRN_DOWN);
    }
    if (elev_get_floor_sensor_signal()!=-1) {
         elev_set_motor_direction(DIRN_STOP);
    }
}
void clearOrdersDown(){
    for (int i=0; i<=N_FLOORS-1; i++) {
        if (floorsBelow[i]!=-1) {
            floorsBelow[i]=-1;
        }
    }
    requestCounterDown=0;
}
void clearOrdersUp(){
    for (int i=0; i<N_FLOORS-1; i++) {
        if (floorsAbove[i]!=-1) {
            floorsAbove[i]=-1;
        }
    }
    requestCounterUp=0;
}
int currentFloor(){
    if (elev_get_floor_sensor_signal() != -1 ) {
        return  elev_get_floor_sensor_signal();
    }
    else{
        return -1;
    }
}
void runOrders(){
    lastFloor=currentFloor();
    for(int i = 0; i <= 2; ++i){
        if ((floorsAbove[i] != (-1)) && (floorsAbove[i] > lastFloor)) {
            elev_set_motor_direction(DIRN_UP);
            if (elev_get_floor_sensor_signal() == floorsAbove[i]){
                floorsAbove[i] = -1;
                requestCounterUp=requestCounterUp-1;
            }
            break;
            
        }else {
            elev_set_motor_direction(DIRN_STOP);
            
        }
        
        
        
        if ((floorsBelow[i] != (-1)) && (floorsBelow[i] < lastFloor)) {
            elev_set_motor_direction(DIRN_DOWN);
            if (elev_get_floor_sensor_signal() == floorsBelow[i]){
                floorsBelow[i] = -1;
                requestCounterDown=requestCounterDown-1;
            }
            break;
        }else{
            elev_set_motor_direction(DIRN_STOP);
        }
        
    }
        
    }

bool ordersExist(){
    return requestCounterDown+requestCounterUp;
}
void getOrders(){
    getUpOrders();
    getDownOrders();
}
