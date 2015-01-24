//
//  Day.h
//  BundySystem
//
//  Created by Tom Mitchell on 21/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#ifndef __BundySystem__Day__
#define __BundySystem__Day__

#include <stdio.h>
#include <list>

#include "Shift.h"

#define NUMBER_OF_SHIFTS 10

class Day {
public:
    Shift *getShift(int n);
    int getYear();
    int getDay();
    int getMonth();
    void modifyDate(int d,int m,int y);
    void addShift(void);
    Day(void);
    ~Day(void);
private:
    std::list<Shift> shifts;
    int day;
    int month;
    int year;
};






#endif /* defined(__BundySystem__Day__) */
