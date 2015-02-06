//
//  main.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 20/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "Data.h"
#include "Day.h"
#include "Employee.h"
#include "Shift.h"
#include "Week.h"

void saveTests(void);
void tests(void);
void interface(void);

int main(int argc, const char * argv[]) {
    // insert code here...
    interface();
    //tests();
    //saveTests();
    return EXIT_SUCCESS;
}

void saveTests(){
    Data data;
    data.saveData();
    
    data.getWeek(data.getCurrentWeek())->getDay(3)->getShift(0)->modifyWorked(true);
    data.getWeek(data.getCurrentWeek())->getDay(3)->getShift(0)->modifyTime(4,30,6,30);
    std::cout << data.getWeek(data.getCurrentWeek())->getDay(3)->getShift(0)->getHours() << std::endl;
    assert(data.getWeek(data.getCurrentWeek())->getDay(3)->getShift(0)->getHours()==2);
    assert(data.getWeek(data.getCurrentWeek())->totalHoursWorked(0)==9.5);
    
    
    data.saveData();
}


void tests(void){
    std::cout <<"Testing the shift class";
    Shift t;
    t.clockIn();
    t.modifyWorked(true);
    t.modifyTime(0,0,10,12);
    
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
    d.getShift(0)->modifyWorked(true);
    d.getShift(1)->modifyWorked(true);
    d.getShift(0)->modifyTime(8,0,13,0);
    d.getShift(1)->modifyTime(0,0,3,0);
    assert((d.getShift(0)->hasWorked()==true)&&(d.getShift(0)->getHours()==5));
    assert((d.getShift(1)->hasWorked()==true)&&(d.getShift(1)->getHours()==3));
    std::cout << "... completed!" << std::endl;
    
    
    
    std::cout << "Testing the Week class";
    Week w;
    assert(w.getDay(0)!=NULL);
    w.getDay(0)->addShift();
    assert(w.getDay(0)->getShift(0)!=NULL);
    w.getDay(0)->getShift(0)->modifyWorked(true);
    w.getDay(0)->getShift(0)->modifyTime(14,15,18,15);
    assert((w.getDay(0)->getShift(0)->getHours()==4));
    std::cout << "... completed!" << std::endl;
    
    
    
    std::cout << "Tests for the Employee class";
    Employee e("tom",22.65,1234567,true);
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
    data.addEmployee("Tom", 22.22, 12345,true);
    assert(data.getEmployee("Tom")!=NULL);
    assert(data.getEmployeeNumber("Tom")==0);
    assert(data.getEmployee("Tom")->getName()=="Tom");
    assert(data.getEmployee("Tom")->getWage()==22.22);
    assert(data.getEmployee("Tom")->getTaxFileNumber()==12345);
    
    assert(data.getWeek(0)!=NULL);
    data.newDay();
    
    int i=0;
    i=data.getEmployeeNumber("Tom");
    assert(data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)!=NULL);
    assert(data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->getHours()==0);
    data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->modifyWorked(true);
    data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->modifyTime(0,0,4,0);
    assert(data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(i)->getHours()==4);
    //assert(data.getWeek(data.getCurrentWeek())->totalHoursWorked(i)==4);
    
    data.newDay();
    
    data.getWeek(data.getCurrentWeek())->getDay(2)->getShift(i)->modifyWorked(true);
    data.getWeek(data.getCurrentWeek())->getDay(2)->getShift(i)->modifyTime(3,0,6,30);
    assert(data.getWeek(data.getCurrentWeek())->getDay(2)->getShift(i)->getHours()==3.5);
    assert(data.getWeek(data.getCurrentWeek())->totalHoursWorked(i)==7.5);
    assert(data.getEmployee("James")==NULL);
    
    std::cout << "... completed!" << std::endl;
    data.printWeeklyPay();
    data.addEmployee("James", 45.34, 1234,true);
    assert(data.getEmployee("James")!=NULL);
    
    data.saveData();
    std::cout <<"Tests are completed!" << std::endl;
};

void interface(void){
    Data data;
    std::string line;
    std::string name;
    std::string restOfLine;
    double wage;
    int taxFileNumber;
    
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    
    std::cout << "What would you like to do: ";
    std::getline(std::cin, line);
    while(strcmp(line.c_str(), "end")&& strcmp(line.c_str(), "finish") && strcmp(line.c_str(), "close")){
        wage=0;
        taxFileNumber=0;
        if(!strcmp(line.c_str(), "add employee")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            std::cout << "Employee's wage: ";
            std:: cin >> wage;
            std::cout << "Employee's TFN: ";
            std::cin >>taxFileNumber;
            std::cin.ignore();
            data.addEmployee(name, wage, taxFileNumber, true);
            assert(data.getEmployee(name)!=NULL);
            std::cout << name << std::endl;
            std::cout << "Employee was added." << std::endl;
            data.saveData();
            
        } else if(!strcmp(line.c_str(), "remove employee")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            if(data.getEmployee(name)!=NULL){
                data.getEmployee(name)->endEmployment();
                std::cout << name << " is no longer employed." <<std::endl;
                data.saveData();
            } else {
                std::cout << "Not a valid employee name." << std::endl;
            }
        } else if(!strcmp(line.c_str(), "re-employ employee")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            if(data.getEmployee(name)!=NULL){
                data.getEmployee(name)->endEmployment();
                std::cout << name << " is now re-employed." <<std::endl;
                data.saveData();
            } else {
                std::cout << "Not a valid employee name." << std::endl;
            }
        } else if(!strcmp(line.c_str(),"change wage")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            if(data.getEmployee(name)!=NULL){
                std::cout << "Employee's current wage: " <<data.getEmployee(name)->getWage() << std::endl;
                std::cout << "Employee's new wage: ";
                std::cin >> wage;
                std::cin.ignore();
                data.getEmployee(name)->modifyWage(wage);
                std::cout << name << "'s new wage is " << data.getEmployee(name)->getWage()<< "." <<std::endl;
                data.saveData();
            } else {
                std::cout << "Not a valid employee name." << std::endl;
            }
        } else if(!strcmp(line.c_str(),"clock in")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            if(data.getEmployee(name)!=NULL){
                aTime = localtime(&theTime);
                if(aTime->tm_mday!=data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getDay()){
                    data.newDay();
                    while(aTime->tm_mday!=data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getDay()         && (aTime->tm_mon+1)!=data.getWeek(data.getCurrentWeek())->
                           getDay(data.getCurrentDay())->getMonth()
                        && (aTime->tm_year+1900)!=data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getYear()){
                        data.newDay();
                    }
                }
                data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(data.getEmployeeNumber(name))->clockIn();
                std::cout << name << " has now been clocked in for the day." << std::endl;
                data.saveData();
            } else {
                std::cout << "Not a valid employee name." << std::endl;
            }
            
        } else if(!strcmp(line.c_str(),"clock out")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            if(data.getEmployee(name)!=NULL){
                aTime = localtime(&theTime);
                if(aTime->tm_mday!=data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getDay()){
                    data.newDay();
                    while(aTime->tm_mday!=data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getDay()         && (aTime->tm_mon+1)!=data.getWeek(data.getCurrentWeek())->
                          getDay(data.getCurrentDay())->getMonth()
                          && (aTime->tm_year+1900)!=data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getYear()){
                        data.newDay();
                    }
                }
                data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(data.getEmployeeNumber(name))->clockOut();
                std::cout << name << " has now been clocked out for the day. Hours worked ";
                std::cout << data.getWeek(data.getCurrentWeek())->getDay(data.getCurrentDay())->getShift(data.getEmployeeNumber(name))->getHours() << std::endl;
                data.saveData();
            } else {
                std::cout << "Not a valid employee name." << std::endl;
            }
            
        } else if(!strcmp(line.c_str(), "review data")){
            std::cout << "Employee's name: ";
            std::getline(std::cin, name);
            if(data.getEmployee(name)!=NULL){
                data.printEmployeeYearlyWork(name);
            } else {
                std::cout << "Not a valid employee name." << std::endl;
            }
        } else {
            std::cout << "Invalid command" <<std::endl;
        }
        std::cout << "What would you like to do: ";
        std::getline(std::cin, line);
    }
    
    
    
}

