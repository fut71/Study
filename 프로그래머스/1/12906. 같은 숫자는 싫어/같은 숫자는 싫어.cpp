#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<int> arr) 
{
    vector<int> answer;
    
    int size = arr.size();
    
    answer.emplace_back(arr[0]);
    
    for(int i = 1; i < size; ++i)
    {
        if(arr[i - 1] != arr[i])
        {
            answer.emplace_back(arr[i]);
        }
    }

    // [실행] 버튼을 누르면 출력 값을 볼 수 있습니다.
    cout << "Hello Cpp" << endl;

    return answer;
}