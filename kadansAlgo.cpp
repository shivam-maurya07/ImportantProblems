#include<bits/stdc++.h>
using namespace std;

vector<int> maxSubArray(vector<int>& nums) {
    int currSum = 0;
    int maxSum = INT_MIN;

    int start = 0, end = 0, tempStart = 0;

    for (int i = 0; i < nums.size(); i++) {
        currSum += nums[i];

        if (currSum > maxSum) {
            maxSum = currSum;
            start = tempStart;
            end = i;
        }

        if (currSum < 0) {
            currSum = 0;
            tempStart = i + 1;
        }
    }

    return {maxSum, start, end};
}
