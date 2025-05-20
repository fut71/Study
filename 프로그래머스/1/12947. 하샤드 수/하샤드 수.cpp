#include <string>
#include <vector>

using namespace std;

bool solution(int x) 
{
    bool answer = true;
    
    int num = x;
    int sum = 0;
    
    while(num > 0)
    {
        sum += (num % 10);
        num /= 10;
    }
    
    if(x % sum == 0)
    {
        return true;
    }
    
    return false;
}