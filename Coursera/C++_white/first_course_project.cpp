#include <iostream>
#include <exception>
#include <string>
#include <map>
#include <list>
#include <vector>
#include <sstream>
#include <iomanip>
#include <algorithm>
#define MONTH 1
#define DAY 2
class Date {
private:
    int year, month, day;

    void convertStringToDate(std::string date){
        int codeException = 0;
        std::vector<int> data;
        std::string temp = "";
        for(int i = 0; i < date.size(); ++i){
            if(date[i] == '-'){
                if(i == 0 and date[i+1] != '-'){
                    temp = temp + '-';
                } else if (date[i-1]=='-' and (date[i+1]>='0' and date[i+1] <= '9') and i-1 != 0){
                    temp = temp + '-';
                } else if ((date[i-1] == '-' and date[i+1] == '-') or (i == 0 and date[i+1] == '-')){
                    throwException(codeException, date);
                } else {
                    codeException++;
                    data.push_back(std::stoi(temp));
                    temp = "";
                }
            } else if(date[i] >='0' and date[i] <= '9'){
                temp = temp + date[i];
                if (i == date.size()-1){
                    data.push_back(std::stoi(temp));
                }
            }
        }
        if(data.size()==3){
        year = data[0];
        month = data[1];
        day = data[2];
        } else {
            throwException(0,date);
        }
    }
    void throwException(int codeException, std::string date, int month = 0, int day = 0){
        std::string temp;
        switch (codeException) {
            case 0:
                temp = "Wrong date format: " + date;
                throw std::runtime_error(temp);
            case 1:
                temp = "Month value is invalid: " + std::to_string(month);
                throw std::runtime_error(temp);
            case 2:
                temp = "Day value is invalid: " + std::to_string(day);
                throw std::runtime_error(temp);
        }
    }
public:
    friend bool operator< (const Date& lhs,const Date& rhs);

    friend bool operator== (const Date& lhs,const Date& rhs);

    friend bool operator!= (const Date& lhs, const Date& rhs);

    Date(){
        year = 0, month = 0, day = 0;
    }

    Date(std::string date){
        convertStringToDate(date);
        if(month > 12 or month < 1){
            throwException(MONTH, date, month);
        } else if (day > 31 or day < 1){
            throwException(DAY, date,0,day);
        }
    }

    int GetYear() const {
        return year;
    }

    int GetMonth() const {
        return month;
    }

    int GetDay() const {
        return day;
    }
};


bool operator != (const Date& lhs, const Date& rhs){
int thisDays = lhs.year*365 + lhs.month*31 + lhs.day, otherDays = rhs.year*365 + rhs.month*31 + rhs.day;
return thisDays != otherDays;
}

bool operator< (const Date& lhs, const Date& rhs){
    int thisDays = lhs.year*365+lhs.month*31+lhs.day, otherDays = rhs.year*365+rhs.month*31+rhs.day;
    return thisDays < otherDays;
}
class Database{
public:

    void Add(Date date, std::string event){
        if(!(event == "" or event == " ")){
            if(data.find(date) == data.end()){
                data[date] = {};
                data[date].push_back(event);
            } else {
                if(!isEvent(date, event) and event != "")
                    data[date].push_back(event);
            }
        }
    }

    void DeleteEvent(Date date, std::string event){
        if(!(data.find(date) == data.end()) and isEvent(date, event)){
            data[date].remove(event);
            std::cout << "Deleted successfully" << std::endl;
        } else {
            std::cout << "Event not found" << std::endl;
        }
    }
    void DeleteData(Date date){
        int countEvents = 0;
        if(!(data.find(date) == data.end())){
            countEvents = data[date].size();
            data.erase(date);
        }
        std::cout << "Deleted " << countEvents << " events"<<std::endl;
    }
    void FindEventsByDate(Date date){
        if(!(data.find(date) == data.end())){
            data[date].sort();
            for(auto event: data[date]){
                std::cout << event << std::endl;
            }
        }
    }
    void Print() const {
        for(auto it = data.begin(); it != data.end(); ++it){
            auto events = it->second;
            events.sort();
            for(auto event: events){
                std::cout << std::setfill('0');
                std::cout << std::setw(4) << it->first.GetYear() << '-' << std::setw(2) << it->first.GetMonth()
                          << '-' << std::setw(2) << it->first.GetDay() << " " << event << std::endl;
            }
        }
    }

private:
    bool isEvent(Date date, std::string event){
        for(auto i: data[date]){
            if(i == event)
                return true;
        }
        return false;
    }
    std::map<Date, std::list<std::string>> data;
};

int main(){
    Database db;
    std::string commandAndData = "", command= "", date = "", event = "";
    try {
    while (getline(std::cin, commandAndData)) {
        std::stringstream ss(commandAndData);
        ss>>command>>date>>event;
        if(command == "Add"){
            db.Add(Date(date), event);
        } else if (command == "Find"){
            db.FindEventsByDate(Date(date));
        } else if (command == "Del") {
            if (event.empty()){
                db.DeleteData(Date(date));
            } else {
                db.DeleteEvent(Date(date),event);
            }
        } else if(command == "Print"){
            db.Print();
        } else if (command==""){
        }else {
            std::cout<<"Unknown command: "<<command<<std::endl;
        }
        commandAndData = "", command= "", date = "", event = "";
    }
    }
    catch (std::exception& ex){
        std::cout << ex.what();
    }
    return 0;
}