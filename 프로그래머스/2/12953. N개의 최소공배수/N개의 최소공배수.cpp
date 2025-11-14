#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> arr) 
{
    int answer = 0;
    
    sort(arr.begin(), arr.end(), greater<int>());
    
    for(int i = arr[0]; ; ++i)
    {
        bool temp = true;
        for(size_t j = 0; j < arr.size(); ++j)
        {
            if(i % arr[j] != 0)
            {
                temp = false;
                break;
            }
        }
        
        if(temp)
        {
            return i;
        }
    }
    
    return -1;
}