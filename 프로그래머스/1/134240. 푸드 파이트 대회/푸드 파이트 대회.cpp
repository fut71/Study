#include <string>
#include <vector>

using namespace std;

string solution(vector<int> food) 
{
    string answer = "0";
    for(size_t i = food.size() - 1; i >= 1; --i)
    {
        int num = food[i] / 2;
        if(num > 0)
        {   
            for(int j = 0; j < num; ++j)
            {                
                answer = to_string(i) + answer;
                answer += to_string(i);
            }
        }
    }
    
    return answer;
}