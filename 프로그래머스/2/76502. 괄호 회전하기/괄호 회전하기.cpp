#include <string>
#include <vector>

using namespace std;

int solution(string s) 
{
    int answer = 0;
    
    auto isOpen = [](char c)
    {
        return c == '(' || c == '{' || c == '[';
    };
    
    auto isMatch = [](char open, char close)
    {
        return (open == '(' && close == ')') ||
            (open == '{' && close == '}') ||
            (open == '[' && close == ']');
    };
    
    for(size_t i = 0; i < s.size(); ++i)
    {
        vector<char> stack;    
        bool temp = true;
        
        for(size_t j = 0; j < s.size(); ++j)
        {
            char c = s[(i + j) % s.size()];
            if(isOpen(c))
            {
                stack.push_back(c);
            }
            else
            {
                if(stack.empty())
                {
                    temp = false;
                    break;
                }
                char top = stack.back();
                stack.pop_back();
                if(!isMatch(top, c))
                {
                    temp = false;
                    break;
                }
            }
        }
        if(temp && stack.empty())
        {
            ++answer;
        }
    }
    
    return answer;
}