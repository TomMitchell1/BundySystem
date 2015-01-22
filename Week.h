//
//  Week.h
//  BundySystem
//
//  Created by Tom Mitchell on 22/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#ifndef __BundySystem__Week__
#define __BundySystem__Week__

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <assert.h>

#include "Day.h"
#include "Shift.h"


#define DAYS_IN_A_WEEK 7

class Week {
public:
    Day* getDay(int n);
    double totalHoursWorked(int n);
    Week();
    ~Week();
private:
    Day* days[DAYS_IN_A_WEEK];
    
};

#endif /* defined(__BundySystem__Week__) */
