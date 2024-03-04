  auto comp = [&arr](const vector<int>& a, const vector<int>& b) {
            return arr[a[0]][a[1]] < arr[b[0]][b[1]];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(comp)> heap(comp);