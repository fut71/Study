#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    unordered_map<string, int> um;
    
    for(auto& s : participant)
    {
        if(um.find(s) != um.end())
        {
            ++um[s];
        }
        else
        {
             um[s] = 1;
        }
        
    }
    
    for(auto& s : completion)
    {
        if(um.find(s) != um.end())
        {
            --um[s];
        }
    }
    
    for(auto& s : um)
    {
        if(s.second == 1)
        {
           return s.first;
        }
    }
    return answer;
}