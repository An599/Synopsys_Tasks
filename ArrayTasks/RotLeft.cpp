vector<int> rotLeft(vector<int> a, int d) {
    for (int i = 0; i < d % a.size(); ++i)
        for (int j = 0; j < a.size() - 1; ++j)
            swap(a[j], a[j+1]);
    return a;
}