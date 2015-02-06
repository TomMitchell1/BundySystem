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
    started=false;
    hours=0;
    worked=false;
    
    startHour=0;
    startMin=0;
    finishHour=0;
    finishMin=0;
    
}

Shift::~Shift(void){

}

double Shift::getHours(void){
    return hours;
}

int Shift::getStartHour(){
    return startHour;
}

int Shift::getFinishHour(){
    return finishHour;
}

int Shift::getStartMin(){
    return startMin;
}

int Shift::getFinishMin(){
    return finishMin;
}

void Shift::clockIn(){
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    startHour=aTime->tm_hour;
    startMin= aTime->tm_min;

    started=true;
}

void Shift::clockOut(void){
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    finishHour=aTime->tm_hour;
    finishMin=aTime->tm_min;
    
    double x=0;
    
    if(started){
        if(finishHour<startHour){
            x=finishHour+HOURS_IN_A_DAY-startHour;
            if(finishMin<startMin){
                x+= (double) (finishMin+MINUTES_IN_A_HOUR-startMin)/MINUTES_IN_A_HOUR;
            } else {
                x+= (double) (finishMin-startMin)/MINUTES_IN_A_HOUR;
            }
        } else {
            x=finishHour-startHour;
            if(finishMin<startMin){
                x+= (double) (finishMin+MINUTES_IN_A_HOUR-startMin)/MINUTES_IN_A_HOUR;
            } else {
                
                x+= (double) (finishMin-startMin)/MINUTES_IN_A_HOUR;
            }
        }
        hours=x;
        worked=true;
    }
}

bool Shift::hasWorked(void){
    return worked;
}

bool Shift::hasStarted(void){
    return started;
}

void Shift::modifyTime(int sHour,int sMin,int fHour,int fMin){
    double x=0;
    startHour=sHour;
    startMin=sMin;
    finishHour=fHour;
    finishMin=fMin;
    if(worked){
        if(finishHour<startHour){
            x=finishHour+HOURS_IN_A_DAY-startHour;
            if(finishMin<startMin){
                x+= (double) (finishMin+MINUTES_IN_A_HOUR-startMin)/MINUTES_IN_A_HOUR;
            } else {
                x+= (double) (finishMin-startMin)/MINUTES_IN_A_HOUR;
            }
        } else {
            x=finishHour-startHour;
            if(finishMin<startMin){
                x+= (double) (finishMin+MINUTES_IN_A_HOUR-startMin)/MINUTES_IN_A_HOUR;
            } else {
                
                x+= (double) (finishMin-startMin)/MINUTES_IN_A_HOUR;
            }
        }
        hours=x;
    }
    
    
}

void Shift::modifyStarted(bool s){
    started=s;
}

void Shift::modifyWorked(bool w){
    worked=w;
}

