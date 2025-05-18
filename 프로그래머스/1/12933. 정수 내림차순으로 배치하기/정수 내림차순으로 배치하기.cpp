#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

long long solution(long long n) 
{
    long long answer = 0;
    vector<int> temp;
    while(n != 0)
    {        
        temp.emplace_back(n % 10);
        n /= 10;
    }
    sort(temp.begin(), temp.end(), [](int& a, int& b){return a>b;});
    
    for(auto& s : temp)
    {
        answer +=s;
        answer *= 10;
        cout<<s<<", ";
    }
    answer /= 10;
    
    return answer;
}