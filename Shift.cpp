//
//  Shift.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 20/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Shift.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define SECONDS_IN_HOUR 3600


//Member Functions

Shift::Shift(void){
    std::cout <<"Creating shift\n";
    started=false;
    hours=0;
    worked=false;
    startingTime=0;
    finishingTime=0;
}

Shift::~Shift(void){
    std::cout <<"Destroying shift\n";
}

double Shift::getHours(void){
    return hours;
}

void Shift::clockIn(){
    time(&startingTime);
    worked=true;
}

void Shift::clockOut(void){
    int x=0;
    time(&finishingTime);
    x=difftime(finishingTime, startingTime);
    hours=x/SECONDS_IN_HOUR;
}

bool Shift::hasWorked(void){
    return worked;
}

void Shift::modifyTime(double d){
    worked=true;
    hours=d;
}
