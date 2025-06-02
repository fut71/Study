#include <string>
#include <vector>

using namespace std;

int solution(string t, string p) 
{
    int answer = 0;
    int size = p.size();
    for(size_t i = 0; i <= t.size() - p.size(); ++i)
    {
        string temp = t.substr(i, size);
        if(stoll(temp) <= stoll(p))
        {
            ++answer;
        }
    }
    
    
    return answer;
}