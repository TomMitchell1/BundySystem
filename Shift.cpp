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
/*
 Constructor
*/
Shift::Shift(void){
    started=false;
    hours=0;
    worked=false;
    
    startHour=0;
    startMin=0;
    finishHour=0;
    finishMin=0;
    
}

/*
 Destructor
 */
Shift::~Shift(void){

}

/*
 Returns the number of hours worked in this shift
*/
double Shift::getHours(void){
    return hours;
}

/*
 Returns the starting hour of a shift
 */
int Shift::getStartHour(){
    return startHour;
}

/*
 Returns the finishing hour of a shift
 */
int Shift::getFinishHour(){
    return finishHour;
}

/*
 Returns the starting minute of a shift
 */
int Shift::getStartMin(){
    return startMin;
}

/*
 Returns the finishing minute of a shift
 */
int Shift::getFinishMin(){
    return finishMin;
}

/* 
 Begins the shift
*/
void Shift::clockIn(){
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    startHour=aTime->tm_hour;
    startMin= aTime->tm_min;

    started=true;
}

/*
 Ends the shift
 */
void Shift::clockOut(void){
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    finishHour=aTime->tm_hour;
    finishMin=aTime->tm_min;
    
    double x=0;
    
    if(started && !worked){
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

/*
 Function to determine if a person finished working the shift
*/
bool Shift::hasWorked(void){
    return worked;
}

/*
 Function to determine if a person started working the shift
*/
bool Shift::hasStarted(void){
    return started;
}

/*
 Changes the amount of hours worked in the shift
*/
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

/*
 Changes if the shift has started
 */
void Shift::modifyStarted(bool s){
    started=s;
}

/*
 Changes if the shift has finished
 */
void Shift::modifyWorked(bool w){
    worked=w;
}

