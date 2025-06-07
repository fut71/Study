#include <string>
#include <vector>
#include <map>

using namespace std;

vector<int> solution(string s) 
{
    vector<int> answer;
    map<int, int> m;
    for(int i = 'a'; i <= 'z'; ++i)
    {
        m[i] = -1;
    }
    
    for(size_t i = 0; i < s.size(); ++i)
    {
        int num = s[i];
        if(m[num] == -1)
        {
            answer.emplace_back(-1);
            m[num] = i;
        }
        else
        {
            answer.emplace_back(i - m[num]);
            m[num] = i;
        }
    }
    
    
    return answer;
}