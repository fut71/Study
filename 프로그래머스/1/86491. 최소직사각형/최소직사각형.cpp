#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> sizes) 
{
    int answer = 0;
    
    int col = 0;
    int row = 0;
    
    for(size_t i = 0; i < sizes.size(); ++i)
    {
        sort(sizes[i].begin(), sizes[i].end());
        
        row > sizes[i][0] ?  : row = sizes[i][0];
        col > sizes[i][1] ?  : col = sizes[i][1];
    }
    
    answer = col * row;
    
    return answer;
}