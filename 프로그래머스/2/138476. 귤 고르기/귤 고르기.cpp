#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

using namespace std;

int solution(int k, vector<int> tangerine) 
{
    int answer = 0;
    unordered_map<int, int> m;
    for(int size : tangerine)
    {
        ++m[size];
    }
    
    vector<int> counts;
    for(const auto& [size, count] : m)
    {
        counts.push_back(count);
    }
    
    sort(counts.begin(), counts.end(), greater<int>());
    
    for(int count : counts)
    {
        k -= count;
        ++answer;
        
        if(k <= 0)
        {
            break;
        }
    }
    
    return answer;
}