#include <bits/stdc++.h>
using namespace std;

int solution(int N, int number) 
{
    if(N == number)
    {
        return 1;
    }
    
    vector<unordered_set<int>> s(9);
    
    for(int i = 1; i <= 8; ++i)
    {
        int temp = 0;
        for(int j = 0; j < i; ++j)
        {
            temp = temp * 10 + N;
        }
        s[i].insert(temp);
        
        for(int k = 1; k < i; ++k)
        {
            const auto& n1 = s[k];
            const auto& n2 = s[i - k];
            for(auto a : n1)
            {
                for(auto b : n2)
                {
                    s[i].insert(a + b);
                    s[i].insert(a * b);
                    s[i].insert(a - b);
                    if(b != 0)
                    {                        
                        s[i].insert(a / b);
                    }
                }
            }
        }
        
        if(s[i].count(number))
        {
            return i;
        }
    }
    
    return -1;
}
