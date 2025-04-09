#include <string>
#include <vector>
#include <sstream>
#include <climits>

using namespace std;

string solution(string s) 
{
    string answer = "";    
    std::istringstream iss(s);
    string token = "";
    int min_val = INT_MAX;
    int max_val = INT_MIN;
    
    // 공백을 기준으로 문자열 파싱
    while (iss >> token) 
    {
        int temp = stoi(token);
        if (temp < min_val)
        {
            min_val = temp;
        }
        if (temp > max_val) 
        {
            max_val = temp;
        }
    }
    
    answer += to_string(min_val);
    answer += " ";
    answer += to_string(max_val);
    
    return answer;
}