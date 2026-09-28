#include <bits/stdc++.h>
using namespace std;

class solution {
private:
    int n;
    int cooldown;
    int max_completed;
    
    // taskList will store vectors of format: {id, taskId, deadline}
    vector<vector<int>> taskList; 

    void solve(int mask, int current_time, int completed, vector<int>& last_time, vector<int>& last_idx) {
        if (completed > max_completed) {
            max_completed = completed;
        }
        
        int remaining = n - __builtin_popcount(mask);
        if (completed + remaining <= max_completed) {
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (!(mask & (1 << i))) {
                int tid = taskList[i][1]; // taskId is at index 1
                
                if (i < last_idx[tid]) continue;

                int next_time = current_time;
                if (last_time[tid] != -1) {
                    next_time = max(next_time, last_time[tid] + cooldown);
                }
                
                if (next_time <= taskList[i][2]) { // deadline is at index 2
                    int prev_last_time = last_time[tid];
                    int prev_last_idx = last_idx[tid];

                    last_time[tid] = next_time;
                    last_idx[tid] = i;

                    solve(mask | (1 << i), next_time + 1, completed + 1, last_time, last_idx);

                    last_time[tid] = prev_last_time;
                    last_idx[tid] = prev_last_idx;
                }
            }
        }
    }

public:
    int maximumTasksCompleted(int numTasks, vector<vector<int>>& tasks, int cooldownInput) {
        n = numTasks;
        cooldown = cooldownInput;
        max_completed = 0;
        taskList.clear();

        for (int i = 0; i < n; ++i) {
            taskList.push_back({i, tasks[i][0], tasks[i][1]});
        }

        sort(taskList.begin(), taskList.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[2] != b[2])
                return a[2] < b[2];
            return a[1] < b[1];
        });

        unordered_map<int, int> id_map;
        int mapped_id = 0;
        for (int i = 0; i < n; ++i) {
            if (id_map.find(taskList[i][1]) == id_map.end()) {
                id_map[taskList[i][1]] = mapped_id++;
            }
            taskList[i][1] = id_map[taskList[i][1]];
        }

        vector<int> last_time(mapped_id, -1);
        vector<int> last_idx(mapped_id, -1);

        solve(0, 0, 0, last_time, last_idx);

        return max_completed;
    }
};