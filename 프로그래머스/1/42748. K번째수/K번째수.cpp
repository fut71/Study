#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> solution(vector<int> array, vector<vector<int>> commands) 
{
    vector<int> answer;
    
    for(auto& v : commands)
    {
        int first = v[0];
        int second = v[1];
        int num = v[2];
        vector<int> temp(array.begin() + first -1, array.begin() + second);
        sort(temp.begin(), temp.end());
        answer.emplace_back(temp[num - 1]);
    }
    
    return answer;
}