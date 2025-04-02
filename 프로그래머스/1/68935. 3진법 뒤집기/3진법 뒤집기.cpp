#include <string>
#include <vector>
#include <math.h>

using namespace std;

int solution(int n) 
{
    int answer = 0;
    vector<int> temp;
    
    while (n > 0)
    {
        temp.push_back(n % 3);
        n /= 3;
    }
    
    for (int i = 0; i < temp.size(); ++i)
    {
        answer += temp[i] * pow(3, temp.size() - 1 - i);
    }
    
    return answer;
}