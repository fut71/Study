#include <string>
#include <vector>

using namespace std;

bool solution(string s) 
{
    bool answer = true;
    
    int size = s.size();
    
    if(size == 4 || size == 6)
    {
        for(int i = 0; i < size; ++i)
        {
            if(s[i] >= '0' && s[i] <= '9')
            {
                answer = true;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return answer;
}