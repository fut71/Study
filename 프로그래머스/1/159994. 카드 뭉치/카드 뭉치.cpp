#include <string>
#include <vector>

using namespace std;

string solution(vector<string> cards1, vector<string> cards2, vector<string> goal) 
{
    string answer = "";
    
    vector<int> idx = {0, 0};
    
    for(auto& a : goal)
    {
        if(idx[0]<cards1.size() && a == cards1[idx[0]])
        {
            ++idx[0];
        }
        else if(idx[1]<cards2.size() && a == cards2[idx[1]])
        {
            ++idx[1];
        }
        else
        {
            answer = "No";
            return answer;
        }
    }
    answer = "Yes";
    
    return answer;
}