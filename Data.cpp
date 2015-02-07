//
//  Data.cpp
//  BundySystem
//
//  Created by Tom Mitchell on 23/01/2015.
//  Copyright (c) 2015 Tom Mitchell. All rights reserved.
//

#include "Data.h"

Data::Data(){
    numberOfEmployees=0;
    mkdir("data", 0777);
    allocateWeeks();
    loadData();
}

Data::~Data(){
    freeWeeks();
    workers.clear();
}

void Data::allocateWeeks(){
    int i=0;
    while(i<WEEKS_IN_A_YEAR){
        weeks[i]=(Week*) malloc(sizeof(Week));
        assert(weeks[i]!=NULL);
        new (weeks[i]) Week();
        i++;
    }
}

void Data::freeWeeks(){
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

Employee* Data::getEmployee(int n){
    std::list<Employee>::iterator it=workers.begin();
    int i=0;
    Employee* p=NULL;
    
    bool finished=false;
    while ((it!=workers.end())&&(!finished)){
        p= &*it;
        if(i==n){
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

int Data::getNumberOfEmployees(){
    return numberOfEmployees;
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
        if(getWeek(week)->getDay(day)->getShift(i)->hasStarted()){
            getWeek(week)->getDay(day)->getShift(i)->clockOut();
        }
        i++;
    }
    
    
    day++;
    
    if(day==DAYS_IN_A_WEEK){
        day=0;
        printWeeklyPay();
        week++;
        if(week==WEEKS_IN_A_YEAR){
            newYear();
        }
        
    }
}

void Data::addEmployee(std::string name,double wage,int taxFileNumber,bool working){
    Employee e=Employee(name, wage, taxFileNumber,working);
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
    outfile1 << std::fixed;
    outfile1 << std::setprecision(2);
    outfile2 << std::fixed;
    outfile2 << std::setprecision(2);
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
    int d=0;
    int m=0;
    int y=0;
    numberOfEmployees=0;

    //Get the current day
    d=weeks[WEEKS_IN_A_YEAR-1]->getDay(DAYS_IN_A_WEEK-1)->getDay();
    m=weeks[WEEKS_IN_A_YEAR-1]->getDay(DAYS_IN_A_WEEK-1)->getMonth();
    y=weeks[WEEKS_IN_A_YEAR-1]->getDay(DAYS_IN_A_WEEK-1)->getYear();
    
    saveData();
    freeWeeks();
    allocateWeeks();
    //Move employees over to the ne
    std::list<Employee> list;
    std::list<Employee> temp;
    std::list<Employee>::iterator it=workers.begin();

    if(m==JANUARY){
        if(d>DAYS_IN_JAN){
            d=START_OF_A_MONTH;
            m=FEBRUARY;
        }
    } else if(m==FEBRUARY){
        if(isLeapyear(y)){
            if(d>DAYS_IN_FEBL){
                d=START_OF_A_MONTH;
                m=MARCH;
            }
        } else {
            if(d>DAYS_IN_FEB){
                d=START_OF_A_MONTH;
                m=MARCH;
            }
        }
    } else if(m==MARCH){
        if(d>DAYS_IN_MAR) {
            d=START_OF_A_MONTH;
            m=APRIL;
        }
    } else if(m==APRIL){
        if(d>DAYS_IN_APR){
            d=START_OF_A_MONTH;
            m=MAY;
        }
    } else if(m==MAY){
        if(d>DAYS_IN_MAY){
            d=START_OF_A_MONTH;
            m=JUNE;
        }
    } else if(m==JUNE){
        if(d>DAYS_IN_JUN){
            d=START_OF_A_MONTH;
            m=JULY;
        }
    } else if(m==JULY){
        if(d>DAYS_IN_JUL){
            d=START_OF_A_MONTH;
            m=AUGUST;
        }
    } else if(m==AUGUST){
        if(d>DAYS_IN_AUG){
            d=START_OF_A_MONTH;
            m=SEPTEMBER;
        }
    } else if(m==SEPTEMBER){
        if(d>DAYS_IN_SEP){
            d=START_OF_A_MONTH;
            m=OCTOBER;
        }
    } else if(m==OCTOBER){
        if(d>DAYS_IN_OCT){
            d=START_OF_A_MONTH;
            m=NOVEMBER;
        }
    } else if(m==OCTOBER){
        if(d>DAYS_IN_NOV){
            d=START_OF_A_MONTH;
            m=DECEMBER;
        }
    } else if(m==DECEMBER){
        if(d>DAYS_IN_DEC){
            d=START_OF_A_MONTH;
            m=JANUARY;
            y++;
        }
    }
    
    initialDay=d;
    initialMonth=m;
    initialYear=y;
    
    while (it!=workers.end()){
        if(it->getEmploymentStatus()){
            Employee e=Employee(it->getName(), it->getWage(), it->getTaxFileNumber(),true);
            list.push_back(e);
            numberOfEmployees++;
            addShifts();
        }
    }
    temp=workers;
    workers=list;
    temp.clear();
    
    fillCalendar();
    day=0;
    week=0;
    saveData();
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
                if(actualDay>DAYS_IN_JAN){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=FEBRUARY;
                }
            } else if(actualMonth==FEBRUARY){
                if(isLeapyear(actualYear)){
                    
                    if(actualDay>DAYS_IN_FEBL){
                        actualDay=START_OF_A_MONTH;
                        actualMonth=MARCH;
                    }
                } else {
                    if(actualDay>DAYS_IN_FEB){
                        actualDay=START_OF_A_MONTH;
                        actualMonth=MARCH;
                    }
                }
            } else if(actualMonth==MARCH){
                if(actualDay>DAYS_IN_MAR) {
                    actualDay=START_OF_A_MONTH;
                    actualMonth=APRIL;
                }
            } else if(actualMonth==APRIL){
                if(actualDay>DAYS_IN_APR){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=MAY;
                }
            } else if(actualMonth==MAY){
                if(actualDay>DAYS_IN_MAY){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=JUNE;
                }
            } else if(actualMonth==JUNE){
                if(actualDay>DAYS_IN_JUN){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=JULY;
                }
            } else if(actualMonth==JULY){
                if(actualDay>DAYS_IN_JUL){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=AUGUST;
                }
            } else if(actualMonth==AUGUST){
                if(actualDay>DAYS_IN_AUG){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=SEPTEMBER;
                }
            } else if(actualMonth==SEPTEMBER){
                if(actualDay>DAYS_IN_SEP){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=OCTOBER;
                }
            } else if(actualMonth==OCTOBER){
                if(actualDay>DAYS_IN_OCT){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=NOVEMBER;
                }
            } else if(actualMonth==NOVEMBER){
                if(actualDay>DAYS_IN_NOV){
                    actualDay=START_OF_A_MONTH;
                    actualMonth=DECEMBER;
                }
            } else if(actualMonth==DECEMBER){
                if(actualDay>DAYS_IN_DEC){
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
    
    bool leapyear=false;;
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
        leapyear=false;
    }
    return leapyear;
}

void Data::saveData(){
    
    int i=0;
    int d=0;
    int w=0;
    std::list<Employee>::iterator it=workers.begin();
    std::string folder=("data/"+std::to_string(initialYear)+"-"+std::to_string(initialYear+1));
    mkdir(folder.c_str(),0777);
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
        if(e->getEmploymentStatus()){
            dataFile << "e " << e->getName() << " " << e->getWage() << " " <<e->getTaxFileNumber()
                << " 1" << std::endl;
            it++;
            i++;
        } else {
            dataFile << "e " << e->getName() << " " << e->getWage() << " " <<e->getTaxFileNumber()
            << " 0" << std::endl;
            it++;
            i++;
        }
    }
    
    i=0;
    
    //Save all the shifts into the data file
    while(w<=week){
        d=0;
        while(d<DAYS_IN_A_WEEK){
            i=0;
            while(i<numberOfEmployees){
                if(weeks[w]->getDay(d)->getShift(i)->hasStarted()){
                    //Then it needs to be added into the file
                    dataFile << "s "<< d << " " << w << " " <<weeks[w]->getDay(d)->getShift(i)->getStartMin()
                        << " " <<weeks[w]->getDay(d)->getShift(i)->getStartHour()<< " "
                        <<weeks[w]->getDay(d)->getShift(i)->getFinishMin()<< " "
                        <<weeks[w]->getDay(d)->getShift(i)->getFinishHour()<< " ";
                    
                    if(weeks[w]->getDay(d)->getShift(i)->hasStarted()){
                        dataFile << "1 ";
                    } else {
                        dataFile << "0 ";
                    }
                    if(weeks[w]->getDay(d)->getShift(i)->hasWorked()){
                        dataFile << "1 ";
                    } else {
                        dataFile << "0 ";
                    }
                    dataFile << i <<std::endl;
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
    fillCalendar();
    std::string folder=("data/"+std::to_string(initialYear)+"-"+std::to_string(initialYear+1));
    mkdir(folder.c_str(),0777);
    s="data/"+std::to_string(initialYear)+"-"+std::to_string(initialYear+1)+"/dataFile.txt";
    inputFile.open(s.c_str());
    
    //Add employees and shifts back into the data class
    //Employee variables
    int i=0;
    int taxFileNumber=0;
    double wage=0;
    bool currentlyWorking;
    std::string line;
    std::string name;
    //Shift variables
    int d=0;
    int w=0;
    int employeeNumber=0;
    
    int startHour=0;
    int finishHour=0;
    int startMin=0;
    int finishMin=0;
    
    bool started=false;
    bool worked=true;
    
    
    while(getline(inputFile, line)){
        i=0;
        taxFileNumber=0;
        wage=0;
        currentlyWorking=false;
        d=0;
        w=0;
        employeeNumber=0;
        startHour=0;
        finishHour=0;
        startMin=0;
        finishMin=0;
        
        started=false;
        worked=false;
        
        if(line.substr(0,1)=="e") {
            //Search for the name
            line=line.substr(2);
            i=(int) line.find(" ");
            name=line.substr(0,i);
            line=line.substr(i+1);
            //Find out the wage
            i=0;
            i=(int) line.find(" ");
            wage=atof(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find out the TFN for a worker
            i=0;
            i=(int) line.find(" ");
            taxFileNumber=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find their current employment status
            i=0;
            if(line=="1"){
                currentlyWorking=true;
            } else {
                currentlyWorking=false;
            }
            addEmployee(name, wage, taxFileNumber, currentlyWorking);
        } else if(line.substr(0,1)=="s"){
            //Add a shift to a day
            line=line.substr(2);
            //Find the day
            i=0;
            i=(int) line.find(" ");
            d=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find the week
            i=0;
            i=(int) line.find(" ");
            w=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find the starting minute
            i=0;
            i=(int) line.find(" ");
            startMin=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find the starting hour
            i=0;
            i=(int) line.find(" ");
            startHour=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find the finishing minute
            i=0;
            i=(int) line.find(" ");
            finishMin=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Find the finishing hour
            i=0;
            i=(int) line.find(" ");
            finishHour=atoi(line.substr(0,i).c_str());
            line=line.substr(i+1);
            //Has shift started
            i=0;
            i=(int) line.find(" ");
            if(i==1){
                started=true;
            }
            line=line.substr(i+1);
            //Has finished work that day
            i=0;
            i=(int) line.find(" ");
            if(i==1){
                worked=true;
            }
            line=line.substr(i+1);
            //Employee number
            employeeNumber=atoi(line.c_str());
            getWeek(w)->getDay(d)->getShift(employeeNumber)->modifyStarted(started);
            getWeek(w)->getDay(d)->getShift(employeeNumber)->modifyWorked(worked);
            getWeek(w)->getDay(d)->getShift(employeeNumber)->modifyTime(startHour,startMin,finishHour,finishMin);
        }
    }
}

void Data::printEmployeeYearlyWork(std::string name){
    int d=0;
    int w=0;
    int month=-1;
    int n=getEmployeeNumber(name);
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
    std::cout << "Printing yearly work for " << name << std::endl;
    std::cout << "Financial year starts on: ";
    std::cout << getWeek(w)->getDay(START_OF_WEEK)->getDay()
    << "/" << getWeek(w)->getDay(START_OF_WEEK)->getMonth()
    << "/" << getWeek(w)->getDay(START_OF_WEEK)->getYear() <<std::endl;
    while (w<WEEKS_IN_A_YEAR){
        d=0;
        while (d<DAYS_IN_A_WEEK){
            if(getWeek(w)->getDay(d)->getShift(n)->hasWorked()){
                if(month!=getWeek(w)->getDay(d)->getMonth()){
                    
                    month=getWeek(w)->getDay(d)->getMonth();
                    printMonth(month);
                    std::cout << getWeek(w)->getDay(d)->getYear() << ":" << std::endl;
                }
                std::cout << getWeek(w)->getDay(d)->getDay()
                << "/" << getWeek(w)->getDay(d)->getMonth()
                << "/" << getWeek(w)->getDay(d)->getYear()
                << ":" << getWeek(w)->getDay(d)->getShift(n)->getHours()
                << " hours worked" << std::endl;
            }
            d++;
        }
        w++;
    }
    std::cout << "Summary of working year complete." << std::endl;
}

void printMonth(int n){
    if(n==JANUARY){
        std::cout << "January ";
    } else if(n==FEBRUARY){
        std::cout << "February ";
    } else if(n==MARCH){
        std::cout << "March ";
    } else if(n==APRIL){
        std::cout << "April ";
    } else if(n==MAY){
        std::cout << "May ";
    } else if(n==JUNE){
        std::cout << "June ";
    } else if(n==JULY){
        std::cout << "July ";
    } else if(n==AUGUST){
        std::cout << "August ";
    } else if(n==SEPTEMBER){
        std::cout << "September ";
    } else if(n==OCTOBER){
        std::cout << "October ";
    } else if(n==NOVEMBER){
        std::cout << "November ";
    } else {
        std::cout << "December ";
    }
}