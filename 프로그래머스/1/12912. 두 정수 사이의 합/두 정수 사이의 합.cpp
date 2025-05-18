#include <string>
#include <vector>

using namespace std;

long long solution(int a, int b) 
{
    long long answer = 0;
    
    if(a == b)
    {
        return a;
    }
    
    int t1 = min(a, b);
    int t2 = max(a, b); 
    
    for(int i = t1; i <= t2; ++i)
    {
        answer += i;
    }
    
    return answer;
}