#include "propertyidgenerator.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cmath>
using namespace std;

string generatePropertyID(const string& propertyType, const string& ownerName,double price, double area) 
{
    string typeCode = propertyType.substr(0, 3);
    for (auto &c : typeCode) c = toupper(c);

    string ownerCode = ownerName.substr(0, 3);
    for (auto &c : ownerCode) c = toupper(c);

    long long numericCode = static_cast<long long>(price + area);

    auto now = chrono::system_clock::now();
    auto seconds = chrono::duration_cast<chrono::seconds>(now.time_since_epoch()).count();

    stringstream ss;
    ss << typeCode << "_" << ownerCode << "_" << numericCode << "_" << seconds;

    return ss.str();
}
