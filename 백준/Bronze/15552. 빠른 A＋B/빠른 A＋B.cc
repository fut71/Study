#include <iostream>
using namespace std;

int main()
{
    int n,a,b;
    cin.tie(NULL);
    cout.tie(NULL);
    ios::sync_with_stdio(false);
    cin>>n;
    while(n)
    {
        cin>>a>>b;
        cout<<a+b<<"\n";
        n--;
    }
    
    return 0;
}