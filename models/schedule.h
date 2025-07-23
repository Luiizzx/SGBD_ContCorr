#include "./operation.h"
#include <vector>
using namespace std;

class Schedule{
  public:
    vector<Operation> operations;

    void flush(vector<Operation> operationsList){
      for(int i = operationsList.size(); i > 0; i--){
        operationsList.pop_back();
      }
    }

    void insertOperation(string operationText){
      Operation newOperation;
      Object newObject;
      Transaction newTransaction;
      newOperation.type = operationText[0];
    }
};