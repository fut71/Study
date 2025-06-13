#include <string>
#include <vector>
#include <map>

using namespace std;

int solution(string s) 
{
    int answer = 0;
    map<string, string> num = 
    { 
        {"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"}
        , {"four", "4"}, {"five", "5"}, {"six", "6"}, {"seven", "7"}
        , {"eight", "8"}, {"nine", "9"} 
    };
    
    for(auto& m : num)
    {
        size_t pos = 0;
        while ((pos = s.find(m.first, pos)) != string::npos) 
        {
            s.replace(pos, m.first.length(), m.second);
            pos += m.second.length();
        }
    }
    
    return stoi(s);
}