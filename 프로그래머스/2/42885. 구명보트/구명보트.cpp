#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 투 포인터 알고리즘 활용
int solution(vector<int> people, int limit) 
{
    int answer = 0;
    
    int left = 0;
    int right = people.size() - 1;
    
    sort(people.begin(), people.end());
    
    while(left <= right)
    {
        ++answer;
        
        if(people[left] + people[right] <= limit)
        {
            ++left;
        }
        --right;
    }
    
    
    return answer;
}