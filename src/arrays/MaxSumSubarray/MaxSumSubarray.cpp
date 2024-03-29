#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct KadaneResult
{
	int sum = 0;
	int start = 0;
	int len = 0;
	KadaneResult(int _sum, int _start, int _len) : sum(_sum), start(_start), len(_len)
	{}
};

KadaneResult maxSumSubarray(const vector<int>& arr)
{
	int currSum = arr[0], maxSoFar = arr[0];
	int currStart = 0, maxStart = 0;
    int currLen = 1, maxLen = 1;
	for (int i = 1; i < arr.size(); ++i)
	{
		++currLen;
		if (arr[i] > arr[i] + currSum)
		{
			currStart = i;
			currLen = 1;
		}
		currSum = max(arr[i], arr[i] + currSum);

		if (maxSoFar < currSum)
		{
			maxStart = currStart;
			maxLen = currLen;
		}
		maxSoFar = max(maxSoFar, currSum);
	}
	return KadaneResult(maxSoFar, maxStart, maxLen);
}

int main()
{
	vector<vector<int>> inputs = 
	{
		{1},
		{2, -1},
		{-2, 1, 2, -4},
		{-1, 2, -2, 0},
		{0, 0, 0},
		{2, 1, -3, -4, 5},
		{0, 6, 3, 4, 1},
		{2, -2, -1, 4, -5},
		{-3, 3, 1, -9, 8, 0, 3},
		{-3, 3, 1, 0, 3},
		{-2, -3, 4, -1, -2, 1, 5, -3},
        {-2, 1, -3, 4, -1, 2, 1, -5, 4},
        {5, 4, -1, 7, 8}
	};

	cout << "Maximum sum subarray info for the inputs: " << endl;
	for (const auto& arr : inputs)
	{
		for (size_t i = 0; i < arr.size(); ++i)
		{
			if (i == 0) { cout << "{"; }
			cout << arr[i];
			if (i != arr.size() - 1) { cout << ", "; }
			else { cout << "}"; }
		}

		KadaneResult result = maxSumSubarray(arr);
		cout << endl;
		cout << "Sum: " << result.sum << " Start: " << result.start << " Len: " << result.len << endl;
	}

	return 0;
}
