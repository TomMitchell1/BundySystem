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


#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

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


//Defines for calendar and financial weeks

#define DAYS_IN_A_WEEK 7
#define WEEKS_IN_A_YEAR 52
#define START_OF_WEEK 0
#define END_OF_WEEK 6

#define SUPER_CONTRIBUTION 0.095

//Tax thresholds
#define tax_threshold_355 355
#define tax_threshold_395 395
#define tax_threshold_493 493
#define tax_threshold_711 711
#define tax_threshold_1282 1282
#define tax_threshold_1538 1538
#define tax_threshold_3461 3461
//Tax constants
//y=ax-b
//a constants
#define tax_threshold_395_a 0.1900
#define tax_threshold_493_a 0.2900
#define tax_threshold_711_a 0.2100
#define tax_threshold_1282_a 0.3477
#define tax_threshold_1538_a 0.3450
#define tax_threshold_3461_a 0.3900
#define tax_threshold_over_a 0.4900
//b constants
#define tax_threshold_395_b 67.4635
#define tax_threshold_493_b 106.9673
#define tax_threshold_711_b 67.4642
#define tax_threshold_1282_b 165.4431
#define tax_threshold_1538_b 161.9815
#define tax_threshold_3461_b 231.2123
#define tax_threshold_over_b 577.3662
class Data {
public:
    int getEmployeeNumber(std::string s);
    Employee* getEmployee(std::string s);
    Employee* getEmployee(int n);
    Week* getWeek(int n);
    std::string getPassword(void);
    int getCurrentWeek(void);
    int getCurrentDay(void);
    int getNumberOfEmployees(void);
    void addEmployee(std::string name,double wage,int taxFileNumber,int bsb,int accountNumber,bool working);
    void addShifts(void);
    
    void modifyPassword(std::string s);
    
    void saveData(void);
    void loadData(void);
    
    void newDay();
    void newYear(void);
    void fillCalendar(void);
    bool isLeapyear(int year);
    
    void allocateWeeks(void);
    void freeWeeks(void);
    
    void printWeeklyPay(void);
    void printEmployeeYearlyWork(std::string name);
    
    Data();
    ~Data();
private:
    int week;
    int day;
    int initialDay;
    int initialMonth;
    int initialYear;
    int numberOfEmployees;
    std::string password;
    std::list<Employee> workers;
    Week* weeks[WEEKS_IN_A_YEAR];
};

void printMonth(int n);
double calculateTax(double earnings);

#endif /* defined(__BundySystem__Data__) */
