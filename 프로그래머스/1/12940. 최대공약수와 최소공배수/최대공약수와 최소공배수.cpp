#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int n, int m) 
{
    int num1 = min(n, m);
    int num2 = max(n, m);
    
    vector<int> answer = {1, num2};
            
    for(int i = num1; i >= 1; --i)
    {
        if((n % i == 0) && (m % i == 0))
        {
            answer[0] = i;
            break;
        }
    }
    int temp = num2;
    
    while(!((temp % n == 0) && (temp % m == 0)))
    {
        ++temp;
    }
    answer[1] = temp;
    
    return answer;
}