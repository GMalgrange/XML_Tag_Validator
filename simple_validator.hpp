#include <string>
#include <stack>

using namespace std;
namespace validator{

bool DetermineXml(const std::string &iXmlString)
{
    if (iXmlString.empty()) 
    {
        return false;
    }
    // We'll push opening tags onto a stack and pop them when we encounter a matching closing tag
    stack<string> aTagStack;
    size_t aXmlPos = 0;

    while (aXmlPos < iXmlString.length()) {
        if (iXmlString[aXmlPos] == '<') {
            size_t aTagEnd = iXmlString.find('>', aXmlPos);
            if (aTagEnd == string::npos) 
            {
                return false; // Missing closing '>'
            }
            string aTag = iXmlString.substr(aXmlPos + 1, aTagEnd - aXmlPos - 1);
            // Increment i to the next character after the closing '>'
            aXmlPos = aTagEnd + 1;
            // Check if the tag is a closing tag
            if(aTag[0] == '/') {
                if (aTagStack.empty() || aTagStack.top() != aTag.substr(1)) 
                {
                    return false; // Closing tag without matching opening tag
                }
                // Pop the matching opening tag from the stack
                aTagStack.pop();
            } else {
                if((aTag[0] == '?') || (aTag[0] == '!') || (aTag[aTag.length() - 1] == '/')) {
                    continue; // Skip processing if it's a processing instruction, a comment or self-closing tag
                }
                // Push the opening tag onto the stack
                aTagStack.push(aTag);
            }
        } else {
            ++aXmlPos; // Increment i
        }
    }

    return aTagStack.empty(); // Return true if all tags matched correctly
}

} // namespace validator
