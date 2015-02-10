//
//  Day.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 21/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Day.h"
#include <iostream>

/*
 Constructor
*/
Day::Day(void){
    day=0;
    month=0;
    year=0;
    
}

/*
 Destructor
 */
Day::~Day(void){
    shifts.clear();
}
/*
 Returns the current calendar day
*/
int Day::getDay(){
    return day;
}

/*
 Returns the current calendar month
 */
int Day::getMonth(){
    return month;
}

/*
 Returns the current calendar year
 */
int Day::getYear(){
    return year;
}

/*
 Sets the calendar date
 */
void Day::modifyDate(int d,int m,int y){
    day=d;
    month=m;
    year=y;
}

/*
 Returns the shift for a person specified by int n
 */
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

/*
 Adds a shift to the current day
 */
void Day::addShift(void){
    Shift s;
    shifts.push_back(s);
    
}