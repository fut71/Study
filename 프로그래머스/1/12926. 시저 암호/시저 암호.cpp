#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string s, int n) 
{
    string answer = "";
    for(char c : s)
    {
        if(isalpha(c))
        {
            char base = isupper(c) ? 'A' : 'a';
            answer += (c - base + n) % 26 + base;
        }
        else
        {
            answer += c;
        }
    }
    return answer;
}