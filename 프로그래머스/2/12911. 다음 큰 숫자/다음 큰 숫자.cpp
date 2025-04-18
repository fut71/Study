#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(int n)
{
	int answer = 0;
	int count = 0; // n을 2진변환했을 때 1의 갯수
	int origin = n; // n을 저장

	// n을 2진변환하면서 1의 갯수 카운팅
	while(n > 0)
	{
		if(n % 2 == 1)
		{
			++count;
		}
		n /= 2;
	}

	n = origin;

	for(int i = origin + 1; ; ++i)
	{
		int count2 = 0; // 다음 큰 숫자를 2진변환했을 때 1의 갯수
        int temp3 = i;
		while(temp3 > 0)
		{
			if(temp3 % 2 == 1)
			{
				++count2;
			}
			temp3 /= 2;
		}
		if(count2 == count)
		{
			return i;
		}
	}

	return answer;
}