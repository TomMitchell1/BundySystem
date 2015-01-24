//
//  Data.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 23/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Data.h"



Data::Data(){
    int i=0;
    actualDay=0;
    actualMonth=0;
    actualYear=0;
    numberOfEmployees=0;
    week=0;
    day=0;
    while(i<WEEKS_IN_A_YEAR){
        weeks[i]=(Week*) malloc(sizeof(Week));
        assert(weeks[i]!=NULL);
        new (weeks[i]) Week();
        i++;
    }
}

Data::~Data(){
    int i=0;
    while(i<WEEKS_IN_A_YEAR){
        free(weeks[i]);
        i++;
    }
    workers.clear();
}

Employee* Data::getEmployee(std::string s){
    std::list<Employee>::iterator it=workers.begin();
    int i=0;
    Employee* p=NULL;
    bool finished=false;
    while ((it!=workers.end())&&(!finished)){
        p= &*it;
        if(s==p->getName()){
            finished=true;
        } else {
            it++;
            i++;
        }
    }
    return p;
}

int Data::getEmplyeeNumber(std::string s){
    std::list<Employee>::iterator it=workers.begin();
    int i=0;
    Employee* p=NULL;
    bool finished=false;
    
    while ((it!=workers.end())&&(!finished)){
        p= &*it;
        if(s==p->getName()){
            finished=true;
        } else {
            it++;
            i++;
        }
    }
    return i;
}

Week* Data::getWeek(int n){
    return weeks[n];
}

int Data::getCurrentDay(){
    return day;
}

int Data::getCurrentWeek(){
    return week;
}

void Data::newDay(int d,int m,int y){
    
   
    //TODO if shifts are open for the day need to close them
    //As this would mean that someone forgot to clock off
    actualDay=d;
    actualMonth=m;
    actualYear=y;
    day++;
    
    if(day==DAYS_IN_A_WEEK){
        day=0;
        week++;
    }
    
    if(week==WEEKS_IN_A_YEAR){
        newYear();
    } else {
        weeks[week]->getDay(day)->modifyDate(actualDay, actualMonth, actualYear);
    }
}
void Data::addEmployee(std::string name,double wage,int taxFileNumber){
    Employee e=Employee(name, wage, taxFileNumber);
    numberOfEmployees++;
    addShifts();
    workers.push_back(e);
}

void Data::addShifts(){
    int d=0;
    int w=0;
    while(w<WEEKS_IN_A_YEAR){
        d=0;
        while (d<DAYS_IN_A_WEEK){
            weeks[w]->getDay(d)->addShift();
            d++;
        }
        w++;
    }
}



void Data::newYear(){
    
}






