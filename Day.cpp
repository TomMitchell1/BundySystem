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
}

Shift* Day::getShift(int n){
    std::list<Shift>::iterator it=shifts.begin();
    int i=0;
    Shift* s=NULL;
    while (it!=shifts.end()){
        if(i==n){
            s= &*it;
        }
        it++;
        i++;
    }
    return s;
}

Day::~Day(void){
    shifts.clear();
}

void Day::addShift(void){
    Shift s;
    shifts.push_back(s);
    
}