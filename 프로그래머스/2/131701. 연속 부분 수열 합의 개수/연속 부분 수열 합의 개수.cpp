#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

int solution(vector<int> elements) 
{
    int answer = 0;
    vector<int> e(elements);
    e.insert(e.end(), elements.begin(), elements.end());
    unordered_set<int> s;
    
    for(size_t i = 0; i < elements.size(); ++i)
    {
        int sum = 0;        
        for(size_t j = 0; j < elements.size(); ++j)
        {
            sum += e[i + j];
            s.insert(sum);
        }
    }
    
    return s.size();
}