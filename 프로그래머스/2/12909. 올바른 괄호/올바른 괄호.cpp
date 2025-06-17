#include<string>
#include <iostream>
#include <stack>

using namespace std;

bool solution(string s)
{
    bool answer = true;
    stack<char> temp;
    int num = 0;
    
    for(auto c : s)
    {
        if(c == '(')
        {
            ++num;
        }
        else
        {
            --num;
        }
        
        if(num < 0)
        {
            return false;
        }
    }
    
    
    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;
    
    if(num != 0)
    {
        return false;
    }

    return answer;
}