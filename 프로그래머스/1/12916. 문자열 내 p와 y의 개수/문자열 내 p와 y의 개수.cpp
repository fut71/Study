#include <string>
#include <iostream>
using namespace std;

bool solution(string s)
{
    bool answer = true;
    int numP = 0;
    int numY = 0;
    for(auto& str : s)
    {
        if(str == 'p' || str == 'P')
        {
            ++numP;
        }
        else if(str == 'y' || str == 'Y')
        {
            ++numY;
        }
    }
    return numP == numY;

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;

    return answer;
}