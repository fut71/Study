#include <string>
#include <vector>

using namespace std;

vector<int> solution(vector<int> answers) 
{
    vector<int> answer;
    vector<int> temp(3);
    
    vector<int> s1 = {1, 2, 3, 4, 5};
    vector<int> s2 = {2, 1, 2, 3, 2, 4, 2, 5};
    vector<int> s3 = {3, 3, 1, 1, 2, 2, 4, 4, 5, 5};
    
    for(size_t i = 0; i < answers.size(); ++i)
    {
        if(answers[i] == s1[i % s1.size()])
        {
            ++temp[0];
        }
        if(answers[i] == s2[i % s2.size()])
        {
            ++temp[1];
        }
        if(answers[i] == s3[i % s3.size()])
        {
            ++temp[2];
        }
    }
    
    // 비교
    for (int i = 0; i < 3; ++i) 
    {
        if (temp[i] == max(temp[0], max(temp[1], temp[2]))) 
        {
            answer.push_back(i + 1);
        }
    }
    
    return answer;
}