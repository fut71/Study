#include <string>
#include <vector>

using namespace std;

vector<int> solution(string s) 
{
    vector<int> answer = {0, 0};
    // answer[0]: 변환 횟수, answer[1]: 제거된 0의 개수
    
    while(s != "1")
    {
        int numofones = 0;  // 1의 개수
        
        // 문자열을 순회하며 0제거, 1의 개수 카운팅
        for(char c : s)
        {
            if(c == '0')
            {
                ++(answer[1]);
            }
            else
            {
                ++numofones;
            }
        }
        
        s = ""; // 문자열 초기화
        
        // 문자열의 길이를 2진수 문자열로 변환
        while(numofones > 0)
        {
            s = char((numofones % 2) + '0') + s;
            numofones /= 2;
        }
        
        ++(answer[0]);
    }
    
    return answer;
}