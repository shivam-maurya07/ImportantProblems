#include <vector>
#include <climits>

using namespace std;

// Sized for 2 * 10^5 constraints as per the problem description
vector<int> seg(4 * 200005); 

// Build the segment tree to store the INDEX of the minimum value
void build(int idx, int low, int high, vector<int> &arr){
    if(low == high){
        seg[idx] = low; 
        return;
    }
    
    int mid = low + (high - low) / 2;
    build(2 * idx + 1, low, mid, arr);
    build(2 * idx + 2, mid + 1, high, arr);

    int left_idx = seg[2 * idx + 1];
    int right_idx = seg[2 * idx + 2];
    
    // Store the index that points to the smaller value
    seg[idx] = (arr[left_idx] < arr[right_idx]) ? left_idx : right_idx; 
}

// Query the segment tree for the INDEX of the minimum value in range [l, r]
int query(int idx, int low, int high, int l, int r, vector<int> &arr){
    if(r < low || high < l) return -1; // no overlap

    if(l <= low && high <= r) return seg[idx]; // complete overlap

    int mid = low + (high - low) / 2;

    int left = query(2 * idx + 1, low, mid, l, r, arr);
    int right = query(2 * idx + 2, mid + 1, high, l, r, arr);

    // Handle partial overlaps where one side is out of bounds
    if (left == -1) return right;
    if (right == -1) return left;

    // Return the index that points to the smaller value
    return (arr[left] < arr[right]) ? left : right;
}

// Update the segment tree after shifting elements
void update(int idx, int low, int high, int i, vector<int> &arr){
    if(low == high){
        seg[idx] = low;
        return;
    }

    int mid = low + (high - low) / 2;

    if(i <= mid) update(2 * idx + 1, low, mid, i, arr);
    else update(2 * idx + 2, mid + 1, high, i, arr);

    int left_idx = seg[2 * idx + 1];
    int right_idx = seg[2 * idx + 2];
    
    seg[idx] = (arr[left_idx] < arr[right_idx]) ? left_idx : right_idx;
}

vector<int> getRefinedEntries(vector<int> entries) {
    int n = entries.size();
    if (n <= 1) return entries;
    
    // Build tree starting at root index 0
    build(0, 0, n - 1, entries);
    
    int S = 0; // The target index we want to place the smallest available element in
    
    while (S < n) {
        // Find the index of the minimum element in the remaining suffix [S, n-1]
        int K = query(0, 0, n - 1, S, n - 1, entries);

        if (K == S) {
            // The minimum is already in the best possible place
            S += 1;
        } else {
            int val_K = entries[K];
            
            // Shift elements right to make room, updating the segment tree
            for (int i = K; i > S; --i) {
                entries[i] = entries[i - 1];
                update(0, 0, n - 1, i, entries);
            }
            
            // Place the minimum element at position S
            entries[S] = val_K;
            update(0, 0, n - 1, S, entries);
            
            // Elements shifted are permanently locked. Fast-forward S to K.
            S = K;
        }
    }

    return entries;
}