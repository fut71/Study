#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

vector<int> solution(int n, vector<string> words) 
{
    vector<int> answer = {0, 0};
    
    unordered_set<string> m;
    
    for(size_t i = 0; i < words.size(); ++i)
    {
        const string& temp = words[i];
        if(m.find(temp) != m.end())
        {
            answer[0] = (i % n) + 1;
            answer[1] = (i / n) + 1;
            break;
        }
        else if(i >= 1 && temp.front() != words[i - 1].back())
        {
            answer[0] = (i % n) + 1;
            answer[1] = (i / n) + 1;
            break;            
        }    
        m.insert(temp);
    }
    
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다. 
    cout << answer[0] << answer[1] << endl;

    return answer;
}