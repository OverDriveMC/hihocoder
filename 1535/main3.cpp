
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

void calc(vector<int> &vtr, int &ret){
    int n = (int)vtr.size(), res = 0;
    vector<bool> flags(n, 0);
    for(int i = 0;i < n; ++ i){
        if(flags[i]) continue;
        int cnt = 0, t = vtr[i];
        flags[i] = 1;
        while(!flags[t]){
            flags[t] = 1;
            t = vtr[t];
            ++ cnt;
        }
        res += cnt;
    }
    ret = min(ret, res);
}

int main()
{
    freopen("1.txt","r",stdin);
    int N, res;
    string s, t;
    cin >> N;
    for(int n = 0;n < N; ++ n){
        res = 99999;
        cin >> s >> t;
        unordered_map<int, set<int>> udmp;
        for(int i = 0; i < t.size(); ++ i)
            udmp[t[i]].insert(i);
        vector<int> nums(s.size());
        for(int i = 0;i < s.size(); ++ i){
            nums[i] = *udmp[s[i]].begin();
            udmp[s[i]].erase(udmp[s[i]].begin());
        }
        cout<<s<<"   "<<t<<endl;
        for(int i=0;i<nums.size();i++){
            cout<<"i:"<<i<<"  "<<nums[i]<<endl;
        }
        vector<vector<int>> vtr(4);
        for(int i = 0;i < s.size(); ++ i){
            if(s[i] == 'm') vtr[0].push_back(i);
            if(s[i] == 's') vtr[1].push_back(i);
            if(s[i] == 'f') vtr[2].push_back(i);
            if(s[i] == 't') vtr[3].push_back(i);
        }
        for(int i = 1; i < 16; ++ i){ //这边可以再优化，暂时来不及写了
            bool flag = false;
            vector<int> tmp(nums.begin(), nums.end());
            for(int j = 0;j < 4; ++ j){
                if(((i >> j) & 1) && vtr[j].size() == 2){
                    swap(tmp[vtr[j][0]], tmp[vtr[j][1]]);
                    flag = true;
                }
            }
            if(flag)
                calc(tmp, res);
        }
        calc(nums, res);
        cout << res << endl;
    }
}
