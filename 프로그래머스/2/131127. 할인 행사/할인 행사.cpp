#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<string> want, vector<int> number, vector<string> discount) 
{
    int answer = 0;
    
    unordered_map<string, int> m;
    
    for(size_t i = 0; i < want.size(); ++i)
    {
        m[want[i]] = number[i];
    }
    
    unordered_map<string, int> m1;
    
    for(int i = 0; i < 10; ++i)
    {
        ++m1[discount[i]];
    }
    
    for(size_t i = 0; i + 9 < discount.size(); ++i)
    {
        bool temp = true;
        
        for(auto& s : m)
        {
            if(m1[s.first] < s.second)
            {
                temp = false;
                break;
            }
        }
        
        if(temp)
        {
            ++answer;
        }
        
        --m1[discount[i]];
        if(i + 10 < discount.size())
        {
            ++m1[discount[i + 10]];
        }
    }
    
    return answer;
}