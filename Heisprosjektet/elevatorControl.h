//
//  elevatorControl.h
//  heis
//
//  Created by Vebjørn Steinsholt on 08.03.2017.
//  Copyright © 2017 Vebjørn Steinsholt. All rights reserved.
//

#ifndef elevatorControl_h
#define elevatorControl_h
#include "elev.h"
#include <stdio.h>
#include <stdbool.h>

void startUp();
void getUpOrders();
void getDownOrders();
bool isvalueinarray(int val, int arr[], int size);
void stop();
void clearOrdersDown();
void clearOrdersUp();
int currentFloor();
void validateCounters();
void runOrders();
bool ordersExist();
void getOrders();
#endif /* elevatorControl_h */
