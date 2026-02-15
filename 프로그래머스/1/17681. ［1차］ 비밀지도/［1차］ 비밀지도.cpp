#include <string>
#include <vector> 

using namespace std;

vector<string> solution(int n, vector<int> arr1, vector<int> arr2) 
{
    vector<string> answer;
    
    for(int i = 0; i < n; ++i)
    {
        vector<int> a(n, 0);
        int num = 1 << (n - 1);
        for(int j = 0; j < n; ++j)
        {
            if(arr1[i] >= num)
            {
                arr1[i] -= num;
                ++a[j];
            }
            if(arr2[i] >= num)
            {
                arr2[i] -= num;
                ++a[j];
            }
            num /= 2;
        }
        string temp;
        for(auto ar : a)
        {
            if(ar > 0)
            {
                temp += "#";
            }
            else
            {
                temp += " ";
            }
        }
        answer.push_back(temp);
    }
    return answer;
}