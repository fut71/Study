#include <bits/stdc++.h>

using namespace std;

bool solution(vector<string> phone_book) 
{
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());
    
    for(size_t i = 0; i < phone_book.size() - 1; ++i)
    {
        const string& a = phone_book[i];
        const string& b = phone_book[i + 1];
        if(b.rfind(a, 0) == 0)
        {
            return false;
        }
    }
    
    return answer;
}