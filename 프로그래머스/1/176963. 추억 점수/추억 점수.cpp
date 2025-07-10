#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> name, vector<int> yearning, vector<vector<string>> photo) 
{
    vector<int> answer;
    unordered_map<string, int> um;
    for(size_t i = 0; i < name.size(); ++i)
    {
        um[name[i]] = yearning[i];
    }
    
    for(auto& v : photo)
    {
        int temp = 0;
        for(auto s : v)
        {
            temp += um[s];
        }
        answer.emplace_back(temp);
    }
    
    return answer;
}