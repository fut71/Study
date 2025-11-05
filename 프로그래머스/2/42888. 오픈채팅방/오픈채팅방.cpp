#include <string>
#include <vector>
#include <unordered_map>
#include <sstream>
using namespace std;

vector<string> solution(vector<string> record) 
{
    vector<string> answer;
    unordered_map<string, string> name;
    for(const auto& v : record)
    {
        istringstream iss(v);
        string a, b, c;
        if(iss >> a >> b >> c)
        {
            name[b]=c;
        }
        string res = b;
        if(a == "Enter")
        {
            res += "님이 들어왔습니다.";            
            answer.push_back(res);
        }
        else if(a == "Leave")
        {
            res += "님이 나갔습니다.";            
            answer.push_back(res);
        }
    }
    for(auto& v : answer)
    {
        size_t p = v.find("님");
        string uid = v.substr(0, p);
        v.replace(0, p, name[uid]);
    }
    
    
    return answer;
}