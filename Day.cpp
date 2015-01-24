//
//  Day.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 21/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Day.h"
#include <iostream>


Day::Day(void){
    day=0;
    month=0;
    year=0;
    
}

Day::~Day(void){
    shifts.clear();
}

int Day::getDay(){
    return day;
}

int Day::getMonth(){
    return month;
}

int Day::getYear(){
    return year;
}

void Day::modifyDate(int d,int m,int y){
    day=d;
    month=m;
    year=y;
}

Shift* Day::getShift(int n){
    std::list<Shift>::iterator it=shifts.begin();
    int i=0;
    Shift* s=NULL;
    bool finished=false;
    while (it!=shifts.end() && (!finished)){
        if(i==n){
            s= &*it;
            finished=true;
        }
        it++;
        i++;
    }
    return s;
}



void Day::addShift(void){
    Shift s;
    shifts.push_back(s);
    
}