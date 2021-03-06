#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

// Given an array of non-negative integers, you are initially positioned at the first index of the array.
// Each element in the array represents your maximum jump length at that position.
// Your goal is to reach the last index in the minimum number of jumps.
// For example:
// Given array A = [2,3,1,1,4]
// The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, 
// then 3 steps to the last index.
// You can assume that you can always reach the last index.
// Time complexity: O(n^2)
static bool isValidIndex(size_t index, size_t size)
{
    return index < size;
}
struct Position
{
    size_t index = 0;
    int val = 0;

    Position() = default;
    Position(const std::pair<size_t, int>& p) : index(p.first), val(p.second)
    { }
    bool operator== (const Position& rhs) const
    {
        return index == rhs.index && val == rhs.val;
    }
};
struct PositionHash
{
    int operator()(const Position& key) const
    {
        return static_cast<int>(std::hash<size_t>()(key.index)) ^ std::hash<int>()(key.val);
    }
};

vector<Position> MinJumps(const vector<int>& input)
{
    if (input.size() <= 1)
    {
        return {};
    }

    vector<Position> path;  // has the final result path
    Position start({0, input[0]});
    Position end({input.size() - 1, input[input.size() - 1]});

    queue<Position> q;
    unordered_map<Position, Position, PositionHash> lookup;
    bool foundPath = false;

    // do a bfs
    q.push(start);
    lookup[start] = start;

    while (!q.empty())
    {
        Position parent = q.front();
        q.pop();
        if (parent == end)
        {
            foundPath = true;
            break;
        }
        size_t currIndex = parent.index;
        for (size_t i = 1; i <= parent.val; ++i)
        {
            if (!isValidIndex(currIndex + i, input.size())) 
            { 
                // no point continuing further, subsequent values are only higher
                break;
            }

            Position pos({currIndex + i, input[currIndex + i]});
            // do not add if the position was seen prior
            if (lookup.find(pos) == lookup.cend())
            {
                q.push(pos);
                lookup[pos] = parent;
            }
        }
    }
    if (foundPath)
    {
        path.push_back(end);
        Position parent = end;
        // construct the path backwards from the destination to source
        while (lookup.find(parent) != lookup.cend())
        {
            if (lookup[parent] == parent)
            {
                break;
            }
            parent = lookup[parent];
            path.push_back(parent);
        }
        reverse(path.begin(), path.end());
    }
    return path;
}

int main()
{
    vector<vector<int>> inputs = 
    {
        {2, 3, 1, 1, 4},
        {1, 3, 5, 8, 9, 2, 6, 7, 6, 8, 9},
    };

    cout << "Minimum jumps for the following inputs: " << endl;
    for (const auto& input : inputs)
    {
        for (auto i : input)
        {
            cout << i << " ";
        }
        cout << endl;
        vector<Position> path = MinJumps(input);
        if (!path.empty())
        {
            for (size_t i = 0; i < path.size(); ++i)
            {
                if (i == 0)
                {
                    cout << "output format: (<index>, <array value at that index>)" << endl;
                }
                cout << "(" << path[i].index << ", " << path[i].val << ")";
                if (i != path.size() - 1)
                {
                    cout << " -> ";
                }
            }
            cout << ", total number of moves: ";
            path.size() > 0 ? cout << path.size() - 1 << endl : cout << "0" << endl;
        }
        else
        {
            cout << "No path found." << endl;
        }
    }
    return 0;
}