#include <string>
#include <vector>

using namespace std;

// 1. 주어진 hp를 1, 3, 5이 공격력을 가진 개미들의 합으로 맞춰야한다.
// 2. 개미들의 수는 최소한이어야한다.
// 3. 그리디 알고리즘을 이용하여, 큰 공격력을 가진 개미부터 계산한다.
// 4. 시간 복잡도: O(1)

int solution(int hp) 
{
    // 장군, 병정, 일개미의 수
    int a = 0, b = 0, c = 0;    
    
    // 1. 장군개미의 수를 먼저 구한다.
    a = hp / 5;
    hp %= 5;
    
    // 2. 병정개미의 수를 구한다.
    b = hp / 3;
    hp %= 3;
    
    // 3. 마지막으로 일개미의 수를 구한다.
    c = hp;
    
    return a + b + c;
}