//
//  main.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 20/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include <iostream>
#include <assert.h>

#include "Shift.h"
#include "Day.h"
#include "Week.h"
#include "Employee.h"

void tests(void);

int main(int argc, const char * argv[]) {
    // insert code here...
    
    tests();
    
    return EXIT_SUCCESS;
}


void tests(void){
    std::cout <<"Testing the shift class\n";
    Shift t;
    t.clockIn();
    t.modifyTime(10.2);
    assert((t.hasWorked()==true)&&t.getHours()==10.2);
    
    t = Shift();   // << This works for deleting and remaking an object;
    assert((t.getHours()==0)&&t.hasWorked()==false);
    
    std::cout << "Testing the day class\n";
    
    Day d;
    d.addShift();
    d.addShift();
    assert(d.getShift(0)!=NULL);
    assert(d.getShift(1)!=NULL);
    
    d.getShift(0)->modifyTime(5);
    d.getShift(1)->modifyTime(3);
    assert((d.getShift(0)->hasWorked()==true)&&(d.getShift(0)->getHours()==5));
    assert((d.getShift(1)->hasWorked()==true)&&(d.getShift(1)->getHours()==3));
    
    
    
    std::cout << "Testing the Week class\n";
    
    Week w;
    assert(w.getDay(0)!=NULL);
    w.getDay(0)->addShift();
    assert(w.getDay(0)->getShift(0)!=NULL);
    w.getDay(0)->getShift(0)->modifyTime(4);
    assert((w.getDay(0)->getShift(0)->getHours()==4));
    
    std::cout << "Tests for the Employee class\n";
    Employee e("tom",22.65,1234567);
    assert(e.getName()=="tom");
    assert(e.getWage()==22.65);
    assert(e.getTaxFileNumber()==1234567);
    assert(e.getEmploymentStatus()==true);
    e.endEmployment();
    assert(e.getEmploymentStatus()==false);
    e.reEmploy();
    assert(e.getEmploymentStatus()==true);
    std::cout <<"Tests are completed!\n";
};

