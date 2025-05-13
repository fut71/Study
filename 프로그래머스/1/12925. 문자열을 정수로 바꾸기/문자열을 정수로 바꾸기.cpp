#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(string s) 
{
    int answer = 0;
    
    int size = s.size();
    
    int num = 1;
    cout<<answer<<endl;
    for(int i = size - 1; i > 0; --i)
    {
        answer += (s[i] - '0') * num;
        num *= 10;
    }
    
    if(s[0] == '-')
    {
        answer *= (-1);
    }
    else if(s[0] == '+')
    {
        
    }
    else
    {
        answer += (s[0] - '0') * num;
    }
    
    return answer;
}