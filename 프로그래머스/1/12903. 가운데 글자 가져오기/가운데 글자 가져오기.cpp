#include <string>
#include <vector>
#include <iostream>

using namespace std;

string solution(string s) 
{
    string answer = "";
    
    int size = s.size();
    int temp = size / 2;
    
    if(size % 2 == 0)
    {
        answer += s[temp - 1];
    }
    
    answer += s[temp];
        
    return answer;
}