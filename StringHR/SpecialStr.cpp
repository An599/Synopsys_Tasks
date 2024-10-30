long substrCount(int n, string s) {   
    long amount = 0;   
    int left;   
    int right;   
       
    int i;   
    int j;   
       
    for (i = 0; i < n; ++i)   
    {   
        left = 0;   
        right = 0;   
        j = i;   
        while (j < n && s[i] == s[j++])   
            ++left;   
        while (j < n && s[i] == s[j++] && right < left)   
            ++right; 
        if (left == right) 
            ++amount;   
        amount += left;   
    }   
    return amount;  
}