//
//  main.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 20/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "Data.h"
#include "Day.h"
#include "Employee.h"
#include "Shift.h"
#include "Week.h"


void tests(void);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    tests();
    
    return EXIT_SUCCESS;
}


void tests(void){
    std::cout <<"Testing the shift class";
    Shift t;
    t.clockIn();
    t.modifyTime(10.2);
    assert((t.hasWorked()==true)&&t.getHours()==10.2);
    t = Shift();   // << This works for deleting and remaking an object;
    assert((t.getHours()==0)&&t.hasWorked()==false);
    std::cout << "... completed!" << std::endl;
    
    
    
    std::cout << "Testing the day class";
    Day d;
    d.addShift();
    d.addShift();
    assert(d.getShift(0)!=NULL);
    assert(d.getShift(1)!=NULL);
    d.getShift(0)->modifyTime(5);
    d.getShift(1)->modifyTime(3);
    assert((d.getShift(0)->hasWorked()==true)&&(d.getShift(0)->getHours()==5));
    assert((d.getShift(1)->hasWorked()==true)&&(d.getShift(1)->getHours()==3));
    std::cout << "... completed!" << std::endl;
    
    
    
    std::cout << "Testing the Week class";
    Week w;
    assert(w.getDay(0)!=NULL);
    w.getDay(0)->addShift();
    assert(w.getDay(0)->getShift(0)!=NULL);
    w.getDay(0)->getShift(0)->modifyTime(4);
    assert((w.getDay(0)->getShift(0)->getHours()==4));
    std::cout << "... completed!" << std::endl;
    
    
    
    std::cout << "Tests for the Employee class";
    Employee e("tom",22.65,1234567);
    assert(e.getName()=="tom");
    assert(e.getWage()==22.65);
    assert(e.getTaxFileNumber()==1234567);
    assert(e.getEmploymentStatus()==true);
    e.endEmployment();
    assert(e.getEmploymentStatus()==false);
    e.reEmploy();
    assert(e.getEmploymentStatus()==true);
    std::cout << "... completed!" << std::endl;
    
    
    
    std::cout << "Testing the data class";
    Data data;
    data.addEmployee("Tom", 22.22, 12345);
    assert(data.getEmployee("Tom")!=NULL);
    assert(data.getEmplyeeNumber("Tom")==0);
    assert(data.getEmployee("Tom")->getName()=="Tom");
    assert(data.getEmployee("Tom")->getWage()==22.22);
    assert(data.getEmployee("Tom")->getTaxFileNumber()==12345);
    
    assert(data.getWeek(0)!=NULL);
    assert(data.getCurrentDay()==0);
    assert(data.getCurrentWeek()==0);
    data.newDay(25, 1, 2014);
    assert(data.getCurrentDay()==1);
    assert(data.getCurrentWeek()==0);
    
    assert(data.getWeek(0)->getDay(1)->getDay()==25);
    assert(data.getWeek(0)->getDay(1)->getMonth()==1);
    assert(data.getWeek(0)->getDay(1)->getYear()==2014);
    
    
    
    int i=0;
    i=data.getEmplyeeNumber("Tom");
    assert(data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)!=NULL);
    assert(data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->getHours()==0);
    data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->modifyTime(4);
    assert(data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->getHours()==4);
    assert(data.getWeek(data.getCurrentWeek())->totalHoursWorked(i)==4);
    std::cout << "... completed!" << std::endl;
    
    
    
    
    std::cout <<"Tests are completed!" << "\n";
};

