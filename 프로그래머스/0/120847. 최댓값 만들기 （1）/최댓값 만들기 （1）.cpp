#include <string>
#include <vector>

using namespace std;

int solution(vector<int> numbers) 
{
    int answer = 0;
    
    for(size_t i = 0; i < numbers.size(); ++i)
    {
        for(size_t j = i + 1; j < numbers.size(); ++j)
        {
            int temp = numbers[i] * numbers[j];
            answer = answer > temp ? answer : temp;
        }
    }
    
    return answer;
}