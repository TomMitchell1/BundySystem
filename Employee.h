//
//  Employee.h
//  BundySystem
//
//  Created by Tom Mitchell on 23/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#ifndef __BundySystem__Employee__
#define __BundySystem__Employee__

#include <stdio.h>
#include <string>

class Employee {
public:
    std::string getName(void);
    double getWage(void);
    bool getEmploymentStatus(void);
    int getTaxFileNumber(void);
    int getAccountNumber(void);
    int getBSB(void);
    void endEmployment(void);
    void reEmploy(void);
    void modifyWage(double w);
    void modifyAccountNumber(int n);
    void modifyBSB(int n);
    Employee(std::string n, double w, int taxNum, int b, int account, bool working);
    
private:
    std::string name;
    double wage;
    bool currentlyWorking;
    int taxFileNumber;
    
    int accountNumber;
    int bsb;
    
};

#endif /* defined(__BundySystem__Employee__) */
