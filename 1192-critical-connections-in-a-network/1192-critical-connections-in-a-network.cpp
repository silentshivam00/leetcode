class Solution {
public:

    void countBridges(int src , vector<int> &tin , vector<int> &low , unordered_map<int , bool> &visited , int parent, unordered_map<int , vector<int>> &adjList , int timer , vector<vector<int>> &ans){

        timer++;
        visited[src] = true;
        tin[src] = timer;
        low[src] = timer;

        //nbr pr traveel pe krt h 
        for(auto nbr : adjList[src]){

            //kyunki undirected graph h 
            //to nbr parent bhi ho skta
            if(nbr == parent) continue;

            else if(!visited[nbr]){
                // normal traversal kro and check for bridge
                countBridges(nbr , tin , low , visited , src , adjList , timer , ans);
                //ye mai bhul jata hoon
                low[src] = min(low[src] , low[nbr]);

                //ab mai wapas aaya hoon check for bridge
                if(low[nbr] > tin[src]){
                    //bridge exist
                    vector<int> temp;
                    temp.push_back(src);
                    temp.push_back(nbr);
                    ans.push_back(temp);
                }
            }
            else{
                //already visited and not parent
                // low time ko update krdo if possible
                low[src] = min(low[src] , low[nbr]);
            }
        }
    }

    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        int timer = 0;
        int src = 0;
        int parent = -1;
        vector<int> tin(n);
        vector<int> low(n);
        unordered_map<int , bool> visited;
        vector<vector<int>> ans;

        unordered_map<int , vector<int>> adjList;

        for(auto i : connections){
            int u = i[0];
            int v = i[1];

            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        countBridges(src , tin , low , visited , parent , adjList , timer , ans);

        return ans;
    }
};