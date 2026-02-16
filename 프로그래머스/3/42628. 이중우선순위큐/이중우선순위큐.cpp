#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(vector<string> operations) 
{
    vector<int> answer = {0, 0};
    set<int> data;
    for(const auto& s : operations)
    {
        if(s[0] == 'I')
        {
            data.insert(stoi(s.substr(2)));
        }
        else
        {           
            if(data.empty())
            {
                continue;
            }

            if(s == "D 1")
            {
                data.erase(prev(data.end()));
            }
            else
            {
                data.erase(data.begin());
            }
        }
    }
    
    if(!data.empty())
    {
        answer[1] = (*data.begin());
        answer[0] = (*data.rbegin());
    }
    return answer;
}