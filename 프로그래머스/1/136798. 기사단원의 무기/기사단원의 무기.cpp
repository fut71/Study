#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int number, int limit, int power) 
{
    int answer = 0;
    for(int i = 1; i <= number; ++i)
    {
        int count = 0;
        for(int j = 1; j * j <= i; ++j)
        {         
            if(i % j == 0)
            {
                if(j * j == i)
                {
                    count++;
                }
                else
                {
                    count += 2;
                }
            }
        }
        if(count > limit)
        {
            answer += power;
        }
        else
        {
            answer += count;
        }
    }
    
    
    return answer;
}