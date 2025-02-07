#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include "simple_validator.hpp"

using namespace std;
using validator::DetermineXml;

int main(int argc, char *argv[])
{
    const vector<tuple<string, bool>> test_cases = {
        {"", false},                                                           // Empty string
        {"<>", false},                                                         // No tag
        {"</>", false},                                                        // No tag closing
        {"<Design><Code>hello world</Code></Design>", true},                   // Normal case
        {"<Design><Test/><Code>hello world</Code></Design>", true},            // Self closing tag
        {"<Design><Code>hello world</Code></Design><People>", false},          // No closing tag for "People"
        {"<People><Design><Code>hello world</People></Code></Design>", false}, // "/Code" should come before "/People"
        {"<People age=”1”>hello world</People>", false},                       // There is no closing tag for "People age=”1”" and no opening tag for "/People"
        {"<People age=”1”>hello world</People age=”1”>", true},                // Attribute is coherent
        {"<Design<Code>hello world</Code></Design>", false},                   // Missing bracket 1
        {"<Design><Code>hello world</Code>/Design>", false},                   // Missing bracket 2
        {"<Design><Code>hello< world</Code></Design>", false},                 // Too many brackets 1
        {"<Design><Code>hello </world</Code></Design>", false},                // Too many brackets 2
        {"<Design><Code> hello world </Code><Code> goodnight world </Code></Design>", true}, // repeating tag true
        {"<Design><Code> hello world <Code><Code> goodnight world </Code></Design>", false}, // repeating tag false
        {"<Comment><!-- This is a comment --></Comment>", true}                // Comment tag    
    };

    int failed_count = 0;
    for (auto &test_case : test_cases)
    {
        auto &input = get<0>(test_case);
        auto &expected = get<1>(test_case);

        auto result = DetermineXml(input);
        auto result_str = result ? "Valid" : "Invalid";

        if (result == expected)
        {
            cout << "OK ";
        }
        else
        {
            cout << "NG ";
            failed_count++;
        }
        cout << input << ": " << result_str << endl;
    }

    cout << "Result: " << (test_cases.size() - failed_count) << "/" << test_cases.size() << endl;

    return 0;
}