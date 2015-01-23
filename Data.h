//
//  Data.h
//  BundySystem
//
//  Created by Tom Mitchell on 23/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#ifndef __BundySystem__Data__
#define __BundySystem__Data__

#include <stdio.h>
#include <list>
#include <string>
#include <assert.h>

#include "Employee.h"
#include "Week.h"

#define WEEKS_IN_A_YEAR 52

class Data {
public:
    int getEmplyeeNumber(std::string s);
    Employee* getEmployee(std::string s);
    Week* getWeek(int n);
    void addEmployee(void);
    void saveData(void);
    void loadData(void);
    void newYear(void);
    void printWeeklyPay(void);
    void printEmployeeYearlyWork(int n);
    void printEmployeeMonthly(int n);

private:
    int week;
    int day;
    std::list<Employee> shifts;
    Week* weeks[WEEKS_IN_A_YEAR];
};



#endif /* defined(__BundySystem__Data__) */
