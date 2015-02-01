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
    
    loadData();
    
    numberOfEmployees=0;
    std::string s=("data/"+std::to_string(initialYear)+"-"+std::to_string(initialYear+1));
    mkdir("data", 0777);
    mkdir(s.c_str(),0777);
    while(i<WEEKS_IN_A_YEAR){
        weeks[i]=(Week*) malloc(sizeof(Week));
        assert(weeks[i]!=NULL);
        new (weeks[i]) Week();
        i++;
    }
    fillCalendar();
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
    if(!finished){
        p=NULL;
    }
    
    return p;
}

int Data::getEmployeeNumber(std::string s){
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
    if(!finished){
        i=-1;
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

void Data::newDay(){
    
   
    //TODO if shifts are open for the day need to close them
    //As this would mean that someone forgot to clock off
    int i=0;
    while(i<numberOfEmployees){
        getWeek(week)->getDay(day)->getShift(i)->clockOut();
        i++;
    }
    
    
    day++;
    
    if(day==DAYS_IN_A_WEEK){
        day=0;
        printWeeklyPay();
        week++;
    }
    
    if(week==WEEKS_IN_A_YEAR){
        newYear();
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

void Data::printWeeklyPay(){
    int i=0;
    std::ofstream outfile1;
    std::ofstream outfile2;
    std::string s=("data/"+std::to_string(initialYear)+"-"+std::to_string(initialYear+1)+"/week "+ std::to_string(week+1));
    std::list<Employee>::iterator it=workers.begin();
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    mkdir(s.c_str(),0777);
    outfile1.open((s+"/totalpayments.txt"));
    outfile1 << "\nPayments required for week "<<week+1 <<"\n" <<std::endl;
    outfile1 << "Starting on "<< getWeek(week)->getDay(START_OF_WEEK)->getDay()
              << "/" << getWeek(week)->getDay(START_OF_WEEK)->getMonth()
              << "/" << getWeek(week)->getDay(START_OF_WEEK)->getYear() <<std::endl;
    
    outfile1 << "Finishing on "<< getWeek(week)->getDay(END_OF_WEEK)->getDay()
    << "/" << getWeek(week)->getDay(END_OF_WEEK)->getMonth()
    << "/" << getWeek(week)->getDay(END_OF_WEEK)->getYear()<< "\n" <<std::endl;

    
    
    while(i<numberOfEmployees){
        //Saving employee data to the overall text file
        outfile1 << "Employee: " << it->getName() << std::endl;
        outfile1 << "Hourly rate:";
        if(it->getWage() <10){
            outfile1 << " " <<it->getWage() <<std::endl;
        } else {
            outfile1 <<it->getWage() <<std::endl;
        }
        outfile1 << "Hours worked:";
        if(getWeek(week)->totalHoursWorked(i)<10){
            outfile1 << " " << getWeek(week)->totalHoursWorked(i) << std::endl;
        } else {
            outfile1 << getWeek(week)->totalHoursWorked(i) << std::endl;
        }
        outfile1 << "Total weekly pay: " <<it->getWage()*getWeek(week)->totalHoursWorked(i) << "\n" <<std::endl;
        
        
        
        //Saving an employees data to own personal payslip
        outfile2.open((s+"/"+it->getName()+".txt"));
        
        outfile2 << "Employee: " << it->getName() << std::endl;
        outfile2 << "Hourly rate:";
        if(it->getWage() <10){
            outfile2 << " " <<it->getWage() <<std::endl;
        } else {
            outfile2 <<it->getWage() <<std::endl;
        }
       outfile2 << "Hours worked:";
        if(getWeek(week)->totalHoursWorked(i)<10){
            outfile2 << " " << getWeek(week)->totalHoursWorked(i) << std::endl;
        } else {
            outfile2 << getWeek(week)->totalHoursWorked(i) << std::endl;
        }
        outfile2 << "Total weekly pay: " <<it->getWage()*getWeek(week)->totalHoursWorked(i) << "\n" <<std::endl;
        outfile2.close();
        i++;
        it++;
    }
    outfile1.close();
}

void Data::newYear(void){
    
}

void Data::fillCalendar(){
    int d=START_OF_WEEK;
    int w=0;
    int actualDay=initialDay;
    int actualMonth=initialMonth;
    int actualYear=initialYear;
    while(w<WEEKS_IN_A_YEAR){
        d=START_OF_WEEK;
        while(d<DAYS_IN_A_WEEK){
            getWeek(w)->getDay(d)->modifyDate(actualDay, actualMonth, actualYear);
            d++;
            actualDay++;
            if(actualMonth==JANUARY){
                if(!(actualDay<DAYS_IN_JAN)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=FEBRUARY;
                }
            } else if(actualMonth==FEBRUARY){
                if(isLeapyear(actualYear)){
                    if(!(actualDay<DAYS_IN_FEBL)){
                        actualDay=START_OF_A_MONTH;
                        actualMonth=MARCH;
                    }
                } else {
                    if(!(actualDay<DAYS_IN_FEB)){
                        actualDay=START_OF_A_MONTH;
                        actualMonth=MARCH;
                    }
                }
            } else if(actualMonth==MARCH){
                if(!(actualDay<DAYS_IN_MAR)) {
                    actualDay=START_OF_A_MONTH;
                    actualMonth=APRIL;
                }
            } else if(actualMonth==APRIL){
                if(!(actualDay<DAYS_IN_APR)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=MAY;
                }
            } else if(actualMonth==MAY){
                if(!(actualDay<DAYS_IN_MAY)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=JUNE;
                }
            } else if(actualMonth==JUNE){
                if(!(actualDay<DAYS_IN_JUN)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=JULY;
                }
            } else if(actualMonth==JULY){
                if(!(actualDay<DAYS_IN_JUL)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=AUGUST;
                }
            } else if(actualMonth==AUGUST){
                if(!(actualDay<DAYS_IN_AUG)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=SEPTEMBER;
                }
            } else if(actualMonth==SEPTEMBER){
                if(!(actualDay<DAYS_IN_SEP)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=OCTOBER;
                }
            } else if(actualMonth==OCTOBER){
                if(!(actualDay<DAYS_IN_OCT)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=NOVEMBER;
                }
            } else if(actualMonth==OCTOBER){
                if(!(actualDay<DAYS_IN_NOV)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=DECEMBER;
                }
            } else if(actualMonth==DECEMBER){
                if(!(actualDay<DAYS_IN_DEC)){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=JANUARY;
                    actualYear++;
                }
            }
        }
        w++;
    }
}

bool Data::isLeapyear(int year) {
    
    bool leapyear;
    assert (year >=1582);
    if ((year % 4) ==0) {
        if ((year % 100) ==0) {
            if ((year % 400) ==0) {
                leapyear=true;
            } else {
                leapyear=false;
            }
        } else {
            leapyear=true;
        }
    } else {
        leapyear=true;
    }
    return leapyear;
}

void Data::saveData(){
    
    int i=0;
    int d=0;
    int w=0;
    std::list<Employee>::iterator it=workers.begin();
    std::string s=("data/"+std::to_string(initialYear)+"-"+std::to_string(initialYear+1)+"/dataFile.txt");
    std::string l=("data/day.txt");
    std::ofstream dayFile;
    std::ofstream dataFile;
    Employee* e=NULL;
    dayFile.open(l);  //Used for saving the current days to a file;
    dataFile.open(s); //Used for saving data about employees and shifts worked
    
    
    dayFile << initialDay << " " << initialMonth << " " << initialYear << " " <<day << " " << week <<std::endl;
    //Add employees to the dataFile
    while(i<numberOfEmployees){
        
        e=&*it;
        dataFile << "e " << e->getName() << " " << e->getWage() << " " <<e->getTaxFileNumber()
            << " " << e->getEmploymentStatus() << std::endl;
        it++;
        i++;
    }
    
    i=0;
    
    //Save all the shifts into the data file
    while(w<=week){
        d=0;
        while(d<DAYS_IN_A_WEEK){
            i=0;
            while(i<numberOfEmployees){
                if(weeks[w]->getDay(d)->getShift(i)->hasWorked()){
                    //Then it needs to be added into the file
                    dataFile << "s "<< d << " " << w << " " <<weeks[w]->getDay(d)->getShift(i)->getHours()
                        <<std::endl;
                }
                i++;
            }
            d++;
        }
        w++;
    }
    
    dayFile.close();
    dataFile.close();
    
}

void Data::loadData(){
    bool isSaveData=false;
    std::string s="data/day.txt";
    std::ifstream f(s.c_str());
    std::ifstream inputFile("data/day.txt");
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);
    
    if (f.good()) {
        f.close();
        isSaveData=true;
    }
    if(isSaveData){
        inputFile >> initialDay >> initialMonth >> initialYear >> day >> week;
        inputFile.close();
    } else {
        initialDay = aTime->tm_mday;
        initialMonth = aTime->tm_mon + 1;
        initialYear = aTime->tm_year + 1900;
        day=0;
        week=0;
    }
}