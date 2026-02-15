#include <string>
#include <vector>
#include <set>

using namespace std;

vector<int> solution(int k, vector<int> score) 
{
    vector<int> answer;    
    multiset<int> ms;
    
    for(auto a : score)
    {
        ms.insert(a);
        if(ms.size() > k)
        {
            ms.erase(ms.begin());
        }
        answer.push_back(*ms.begin());
        
    }
    
    return answer;
}