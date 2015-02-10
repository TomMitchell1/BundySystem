//
//  Employee.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 23/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Employee.h"

/*
 Constructor
 */
Employee::Employee(std::string n,double w,int taxNum, bool working){
    name=n;
    wage=w;
    currentlyWorking=working;
    taxFileNumber=taxNum;
    
}

/*
 Returns the employee's name
 */
std::string Employee::getName(void){
    return name;
}

/*
 Returns the employee's wage
 */
double Employee::getWage(void){
    return wage;
}

/*
 Returns true if the employee is still working at the business
 */
bool Employee::getEmploymentStatus(void){
    return currentlyWorking;
}

/*
 Returns the employee's tax file number
 */
int Employee::getTaxFileNumber(void){
    return taxFileNumber;
}

/*
 Causes the employee to not be working, so that they are not on the payroll for the next financial year
 */
void Employee::endEmployment(void){
    currentlyWorking=false;
}
/* 
 Causes the employee to be working again, so that they are in the payroll for the next financial year
*/
void Employee::reEmploy(void){
    currentlyWorking=true;
}
/*
 Changes the employee's wage
*/
void Employee::modifyWage(double w){
    wage=w;
}