#include <string>
#include <vector>

using namespace std;

string solution(vector<string> seoul) 
{
    string answer = "";
    int num = 0;
    int size = seoul.size();
    
    for(int i = 0; i < size; ++i)
    {
        if(seoul[i] == "Kim")
        {
            num = i;
        }
    }
    
    answer += "김서방은 ";
    answer += to_string(num);
    answer += "에 있다";
    
    return answer;
}