#include <bits/stdc++.h>

using namespace std;

int solution(vector<vector<string>> clothes) 
{
    int answer = 1;
    
    unordered_map<string, int> count;
    
    for(auto& c : clothes)
    {
        ++count[c[1]];
    }
    
    for(auto& [kind, num] : count)
    {
        answer *= (num + 1);
    }
    
    answer -= 1;
    
    return answer;
}