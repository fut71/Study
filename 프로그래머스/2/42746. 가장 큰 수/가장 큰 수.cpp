#include <bits/stdc++.h>

using namespace std;

string solution(vector<int> numbers) 
{
    string answer = "";
    
    vector<string> s;
    for(auto& n : numbers)
    {
        s.push_back(to_string(n));
    }
    
    sort(s.begin(), s.end(), [](const string& a, const string& b){
        return a + b > b + a;
    });
    
    if(s.front() == "0")
    {
        return "0";
    }
    
    for(auto& a : s)
    {
        answer += a;
    }
    
    return answer;
}