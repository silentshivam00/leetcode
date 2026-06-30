class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
        
        unordered_map<int , vector<int>> adjList;
        for(auto e : edges){
            int u = e[0];
            int v = e[1];

            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        unordered_map<int , bool> visited;
        queue<int>q;

        q.push(source);
        visited[source] = true;
        visited[destination] = false;

        while(!q.empty()){
            int front = q.front();
            q.pop();

            for(auto nbr : adjList[front]){
                if(!visited[nbr]){
                    q.push(nbr);
                    visited[nbr] = true;
                }
            }
        }

        if(source == destination) return true;

        if(visited[destination] == true){
            return true;
        }
        else{
            return false;
        }
    }
};