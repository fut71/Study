#include <string>
#include <vector>

using namespace std;

long long solution(int n) 
{
    long long answer = 0;
    
    vector<long long> v(n + 2);
    
    v[1] = 1;
    if(n >= 2)
    {
        v[2] = 2;
    }
    
    for(int i = 3; i <= n; ++i)
    {
        v[i] = (v[i - 1] + v[i - 2]) % 1234567;
    }
    
    answer = v[n] % 1234567;
    
    return answer;
}