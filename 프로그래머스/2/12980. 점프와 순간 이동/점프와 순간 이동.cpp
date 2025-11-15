#include <iostream>
using namespace std;

int solution(int n)
{
    int ans = 0;        
    
    while(n > 0)
    {
        ans += (n & 1);
        n >>= 1;
    }
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.

    return ans;
}