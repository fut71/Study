#include <bits/stdc++.h>
using namespace std;

int solution(vector<int> nums)
{
    std::unordered_set<int> kinds(nums.begin(), nums.end());
    int temp = kinds.size();
    int half = nums.size() / 2;

    return min(temp, half);
}