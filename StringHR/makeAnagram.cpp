int amount(char x, string a)
{
    int q = 0;
    for(int i = 0; i < a.size(); i++)
        if (a[i] == x)
            q++;
    return q;
}

int makeAnagram(string a, string b) {
    int count = 0;
    vector<char> str;
    int i;
    for(i = 0; i<a.size(); i++)
    {
        if (find(str.begin(), str.end(), a[i]) == str.end())
        {
            str.push_back(a[i]);
            count += abs(amount(a[i],a)-amount(a[i],b));
        }
    }
    for (i = 0; i < b.size(); i++)
    {
        if (find(str.begin(), str.end(), b[i]) == str.end())
        {
            str.push_back(b[i]);
            count += abs(amount(b[i],a)-amount(b[i],b));
        }
    }
    return count;
}