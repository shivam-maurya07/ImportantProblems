#include <vector>
#include <queue>

using namespace std;

int maximizeTransactions(vector<int> transaction) {
    long long balance = 0;
    int accepted_count = 0;
    
    // Min-heap to keep track of the negative transactions we have processed
    priority_queue<int, vector<int>, greater<int>> min_heap;

    for (int i = 0; i < transaction.size(); ++i) {
        int current_tx = transaction[i];
        
        // Tentatively accept the transaction
        balance += current_tx;
        accepted_count++;

        // If it's a withdrawal, track it in the heap
        if (current_tx < 0) {
            min_heap.push(current_tx);
        }

        // If balance drops below zero, undo the largest withdrawal made so far
        if (balance < 0) {
            if (!min_heap.empty()) {
                int most_negative = min_heap.top();
                min_heap.pop();
                
                // Subtracting a negative number adds its absolute value back to the balance
                balance -= most_negative;
                accepted_count--;
            }
        }
    }

    return accepted_count;
}