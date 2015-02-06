//
//  Employee.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 23/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Employee.h"

Employee::Employee(std::string n,double w,int taxNum, bool working){
    name=n;
    wage=w;
    currentlyWorking=working;
    taxFileNumber=taxNum;
    
}

std::string Employee::getName(void){
    return name;
}

double Employee::getWage(void){
    return wage;
}

bool Employee::getEmploymentStatus(void){
    return currentlyWorking;
}

int Employee::getTaxFileNumber(void){
    return taxFileNumber;
}

void Employee::endEmployment(void){
    currentlyWorking=false;
}

void Employee::reEmploy(void){
    currentlyWorking=true;
}

void Employee::modifyWage(double w){
    wage=w;
}