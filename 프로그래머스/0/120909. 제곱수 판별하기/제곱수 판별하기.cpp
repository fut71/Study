#include <string>
#include <vector>

using namespace std;

int solution(int n) 
{
    int answer = 0;
    
    for(int i = 1; i <= 1000000; ++i)
    {
        if(i * i == n)
        {
            return 1;
        }
        else if(i * i > n)
        {
            return 2;
        }
    }
    
    return 2;
}