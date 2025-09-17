#include <bits/stdc++.h>

using namespace std;

int solution(vector<vector<int>> triangle) 
{
    int answer = 0;
    
    vector<int> v = triangle.back();
    int size = triangle.size();
    
    for(int i = size - 2; i >= 0; --i)
    {
        for(int j = 0; j <= i; ++j)
        {
            v[j] = triangle[i][j] + max(v[j], v[j + 1]);
        }
    }
    
    return v[0];
}