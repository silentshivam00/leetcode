class Solution {
public:

    void topoBFS(int n , vector<int> &ans , unordered_map<int , vector<int>> &adjList){

        queue<int> q;
        unordered_map<int , int> indegree;

        //indegree map ready kro
        for(int src =0; src<n; src++){
            for(auto nbr : adjList[src]){
                indegree[nbr]++;
            }
        }

        //check for indegree 0 and push in q
        for(int i=0; i<n; i++){
            if(indegree[i] == 0){
                q.push(i);
            }
        }

        //main logic
        while(!q.empty()){
            int front = q.front();
            ans.push_back(front);
            q.pop();

            for(auto nbr : adjList[front]){
                indegree[nbr]--;
                if(indegree[nbr] == 0){
                    q.push(nbr);
                }
            }
        }

    }

    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;

        unordered_map<int , vector<int>> adjList;
        for(auto i : prerequisites){
            int u = i[1];
            int v = i[0];

            adjList[u].push_back(v);
        }
        // unordered_map<int , bool> visited;
        vector<int> ans; 

        topoBFS(n ,  ans , adjList);

        if(ans.size() == n) //cycle is not present h 
            return ans;
        else{
            vector<int> temp;
            return temp;
        }
    }
};