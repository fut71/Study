#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string s) 
{
    string answer = "";
    int idx = 0;
    
    for(char c : s)
    {
        if(c == ' ')
        {
            answer += c;
            idx = 0;
        }
        else
        {
            if(idx % 2 == 0)
            {
                answer +=toupper(c);
            }
            else
            {
                answer += tolower(c);
            }
            ++idx;
        }
    }
    
    return answer;
}