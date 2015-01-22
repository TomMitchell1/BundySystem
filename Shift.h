//
//  Shift.h
//  BundySystem
//
//  Created by Tom Mitchell on 20/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#ifndef __BundySystem__Shift__
#define __BundySystem__Shift__

#include <stdio.h>
#include <time.h>

class Shift
{
public:
    double getHours(void);
    void clockIn(void);
    void clockOut(void);
    void modifyTime(double);
    bool hasWorked(void);
    Shift();    //Constructor
    ~Shift();   //Destructor
private:
    bool started;
    double hours;
    bool worked;
    time_t startingTime;
    time_t finishingTime;
};

#endif /* defined(__BundySystem__Shift__) */
