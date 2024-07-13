class Solution {
public:
    vector<int> survivedRobotsHealths(vector<int>& positions, vector<int>& healths, string directions) {
        int length = positions.size();
        vector<pair<int,vector<int>>> temp_storage(length);
        vector<int> healthh(length);
        for(int i =0;i<length;i++){
            temp_storage[i] = {positions[i],{i,healths[i],directions[i]}};
            healthh[i]=healths[i];
        }
        sort(temp_storage.begin(),temp_storage.end());
        

        stack<pair<int,vector<int>>>mov_right_stk;
        vector<bool> survived(length,true);
        for(int i =0;i<length;i++){
            if (temp_storage[i].second[2]=='R'){
                mov_right_stk.push(temp_storage[i]);
            }
            else{
                if(mov_right_stk.empty()){
                    continue;
                }
                pair<int,vector<int>> curr_top = mov_right_stk.top();
                pair<int,vector<int>> curr_left = temp_storage[i];
                //pop
                mov_right_stk.pop();
                // compare
                //if survive then push back
                // if not survive update survived list
                if (curr_top.second[1]==curr_left.second[1]){
                    survived[curr_top.second[0]]=false;
                    survived[curr_left.second[0]]=false;
                    continue;
                }
                else if (curr_top.second[1]>curr_left.second[1]){
                    healthh[curr_top.second[0]]--;
                    survived[curr_left.second[0]]=false;
                    curr_top.second[1]--;
                    mov_right_stk.push(curr_top);
                }
                else{
                    survived[curr_top.second[0]]=false;
                    healthh[curr_left.second[0]]--;
                    temp_storage[i].second[1] = healthh[curr_left.second[0]];
                    i--;
                }
            }
        }
        vector<int> sol;
        for(int i=0;i<length;i++){
            if(survived[i]){
                sol.push_back(healthh[i]);
            } 
        }
        return sol;
    }
};
