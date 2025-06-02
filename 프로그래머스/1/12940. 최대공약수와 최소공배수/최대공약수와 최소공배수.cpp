#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(int n, int m) 
{
    vector<int> answer;
    auto func = [](int a, int b) -> int
    {
        while(b!=0)
        {
            int r = a % b; 
            a = b; 
            b = r;
        } 
        return a;
    };
    
    int temp1 = func(n, m);
    int temp2 = n * m / temp1;
    
    answer = {temp1, temp2};
    
    return answer;
}