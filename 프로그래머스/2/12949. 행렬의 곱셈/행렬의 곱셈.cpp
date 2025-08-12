#include <string>
#include <vector>

using namespace std;

vector<vector<int>> solution(vector<vector<int>> arr1, vector<vector<int>> arr2) 
{
    int size1 = arr1.size();
    int size2 = arr2[0].size();
    int len = arr1[0].size();
    vector<vector<int>> answer(size1, vector<int>(size2, 0));

    for(int i = 0; i < size1; ++i)
    {
        for(int j = 0; j < size2; ++j)
        {
            for(int k = 0; k < len; ++k)
            {
                answer[i][j] += arr1[i][k] * arr2[k][j];
            }
        }
    }
    
    return answer;
}