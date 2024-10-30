string isValid(string s) {
    vector<char> nsame;
    vector<int> q;
    
    for(int i = 0; i < s.size(); i++){
        if (find(nsame.begin(),nsame.end(),s[i])==nsame.end()){
            nsame.push_back(s[i]);
            q.push_back(amount(s[i],s));
        }
    }
    int sum = q[0];
    int max = q[0];
    int min = q[0];
    
    for(int i = 1; i < q.size(); i++){
        sum+=q[i];
        if(q[i]>max)
            max =q[i];
        if(q[i]<min)
            min= q[i];
    }
    if ((sum == min*q.size()) || (sum==min*q.size()+1) || (sum == max*q.size()-(max-1)))
        return "YES";
    return "NO";
        