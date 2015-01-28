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
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <assert.h>
#include <iomanip>
#include <sys/stat.h>

#include "Employee.h"
#include "Week.h"


#define JANUARY 0
#define FEBRUARY 1
#define MARCH 2
#define APRIL 3
#define MAY 4
#define JUNE 5
#define JULY 6
#define AUGUST 7
#define SEPTEMBER 8
#define OCTOBER 9
#define NOVEMBER 10
#define DECEMBER 11

#define DAYS_IN_JAN 31
#define DAYS_IN_FEB 28
#define DAYS_IN_FEBL 29
#define DAYS_IN_MAR 31
#define DAYS_IN_APR 30
#define DAYS_IN_MAY 31
#define DAYS_IN_JUN 30
#define DAYS_IN_JUL 31
#define DAYS_IN_AUG 31
#define DAYS_IN_SEP 30
#define DAYS_IN_OCT 31
#define DAYS_IN_NOV 30
#define DAYS_IN_DEC 31

#define START_OF_A_MONTH 1




#define DAYS_IN_A_WEEK 7
#define WEEKS_IN_A_YEAR 52
#define START_OF_WEEK 0
#define END_OF_WEEK 6
class Data {
public:
    int getEmployeeNumber(std::string s);
    Employee* getEmployee(std::string s);
    Week* getWeek(int n);
    int getCurrentWeek(void);
    int getCurrentDay(void);
    void addEmployee(std::string name,double wage,int taxFileNumber);
    void addShifts(void);
    
    void saveData(void);
    void loadData(void);
    
    void newDay();
    void newYear(void);
    void fillCalendar(void);
    bool isLeapyear(int year);
    
    void printWeeklyPay(void);
    void printEmployeeYearlyWork(int n);
    void printEmployeeMonthly(int n);
    
    Data(int d, int m, int y);
    ~Data();
private:
    int week;
    int day;
    int initialDay;
    int initialMonth;
    int initialYear;
    int numberOfEmployees;
    std::list<Employee> workers;
    Week* weeks[WEEKS_IN_A_YEAR];
};



#endif /* defined(__BundySystem__Data__) */
