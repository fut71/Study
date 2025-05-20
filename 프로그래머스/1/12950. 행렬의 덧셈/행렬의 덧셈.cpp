#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) 
{
    vector<vector<int>> answer;
    
    int size = arr1.size();
    int size2 = arr1[0].size();
    for(int i = 0; i < size; ++i)
    {
        for(int j = 0; j < size2; ++j)
        {            
            arr1[i][j] += arr2[i][j];
        }            
    }
    
    return arr1;
}