#include "./object.h"
#include "./transaction.h"
#include <vector>
#include <string>
using namespace std;

class Operation{
  public:
    char type;
    Object object;
    Transaction transaction;

    static vector<Object> resetList(vector<Object> objList);
    static string buildObject();
    static Object readObject(char opType, Object object, Transaction transaction);
    static Object writeObject(char opType, Object object, Transaction transaction);
};