#include <iostream>
#include <string>
#include "simple_validator.hpp"

using namespace std;
using namespace validator;

int main(int argc, char *argv[])
{
    string input;
    if (argc > 0)
    {
        input = string(argv[1]);
    }

    cout << (DetermineXml(input) ? "Valid" : "Invalid") << endl;

    cout << "Hello world" << endl;
    return 0;
}