//
//  Week.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 22/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//


#include "Week.h"

Week::Week(){
    int i=0;
    while(i<DAYS_IN_A_WEEK){
        days[i]=(Day*) malloc(sizeof(Day));
        assert(days[i]!=NULL);
        new (days[i]) Day();
        i++;
    }
}

Week::~Week(){
    int i=0;
    while(i<DAYS_IN_A_WEEK){
        free(days[i]);
        i++;
    }
}

Day* Week::getDay(int n){
    return days[n];
}

double Week::totalHoursWorked(int n){
    double total=0;
    int i=0;
    while (i<DAYS_IN_A_WEEK){
        total +=days[i]->getShift(n)->getHours();
        i++;
    }
    return total;
}