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

#define HOURS_IN_A_DAY 24
#define MINUTES_IN_A_HOUR 60
class Shift
{
public:
    double getHours(void);
    void clockIn(void);
    void clockOut(void);
    void modifyTime(int sHour,int sMin,int fHour,int fMin);
    void modifyStarted(bool s);
    void modifyWorked(bool w);
    bool hasWorked(void);
    bool hasStarted(void);
    
    int getStartHour(void);
    int getStartMin(void);
    int getFinishMin(void);
    int getFinishHour(void);
    
    Shift();    //Constructor
    ~Shift();   //Destructor
private:
    bool started;
    double hours;
    bool worked;
    
    int startHour;
    int startMin;
    int finishHour;
    int finishMin;
    
    
};

#endif /* defined(__BundySystem__Shift__) */
