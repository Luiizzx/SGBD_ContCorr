#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Schedule{
  public:
    string name;
    string status;
    string operations;

    string buildScheduleText(char current, int operationCount){
      this->name = "E_" + string(1,current);

      if(this->status == "Rollback"){
        cout << this->name + "-" + this->status + "-" + to_string(operationCount) << "\n";
        return this->name + "-" + this->status + "-" + to_string(operationCount);
      }

      cout << this->name + "-" + this->status << "\n";
      return this->name + "-" + this->status;
    }
};