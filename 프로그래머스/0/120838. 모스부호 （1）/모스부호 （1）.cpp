#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// 1. 입력된 문자열은 모스 부호로 구성되어 있으며, 각 문자 간에는 공백으로 구분된다.
// 2. 각 모스 부호를 알파벳 소문자로 해석해 하나의 문자열로 반환해야 한다.
// 3. 이를 위해 모스 부호와 알파벳을 매핑한 비정렬 맵을 사용한다.
// 4. 시간 복잡도: O(N) — N은 문자열 letter의 길이

unordered_map<string, char> morse = 
{
    {".-", 'a'}, {"-...", 'b'}, {"-.-.", 'c'}, {"-..", 'd'}, {".", 'e'}
    , {"..-.", 'f'}, {"--.", 'g'}, {"....", 'h'}, {"..", 'i'}, {".---", 'j'}
    , {"-.-", 'k'}, {".-..", 'l'}, {"--", 'm'}, {"-.", 'n'}, {"---", 'o'}
    , {".--.", 'p'}, {"--.-", 'q'}, {".-.", 'r'}, {"...", 's'}, {"-", 't'}
    , {"..-", 'u'}, {"...-", 'v'}, {".--", 'w'}, {"-..-", 'x'}, {"-.--", 'y'}
    , {"--..", 'z'}
};

string solution(string letter) 
{
    // 결과 문자열
    string answer = "";
    // 현재 모스 부호 토큰 저장
    string token = "";
    
    // 1. 문자열을 순회하면서 공백 기준으로 모스 부호 단위를 분리한다.
    for(char c : letter)
    {
        if(c != ' ')
        {            
            // 모스 부호 문자 누적
            token += c;
        }
        else
        {
            // 공백을 만나면 토큰을 알파벳으로 변환하여 결과에 추가
            if (!token.empty()) 
            {
                answer += morse[token];
                token.clear();
            }
        }
    }
    
    // 2. 마지막에 남은 토큰이 있다면 변환해서 추가
    if (!token.empty()) 
    {
        answer += morse[token];
    }
    
    return answer;
}