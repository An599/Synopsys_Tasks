int minimumSwaps(std::vector<int> arr) {
    int n = arr.size();
    int swaps = 0;
    
    std::vector<bool> visited(n, false);
    
    for (int i = 0; i < n; ++i) {
        if (visited[i] || arr[i] == i + 1) {
            continue;
        }
        
        int cycle_length = 0;
        int x = i;
        
        while (!visited[x]) {
            visited[x] = true;
            x = arr[x] - 1; // Go to the index where arr[x] should be
            ++cycle_length;
        }
        
        if (cycle_length > 0) {
            swaps += (cycle_length - 1);
        }
    }
    
    return swaps;
}