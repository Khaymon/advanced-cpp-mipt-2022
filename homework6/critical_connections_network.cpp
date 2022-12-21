#include <vector>
#include <set>
using namespace std;

class Solution {
private:
    using matrix = vector<vector<int>>;

    int findClusterNotCriticalConnections(matrix& graph, vector<int>& node_rank, set<pair<int, int>>& connections,
                                           int current_node, int parent) {
        if (node_rank[current_node] >= 0) {
            return node_rank[current_node];
        } else {
            if (parent == -1) {
                node_rank[current_node] = 0;
            } else {
                node_rank[current_node] = node_rank[parent] + 1;
            }
        }

        int min_node_rank = graph.size();
        for (int next_node: graph[current_node]) {
            if (next_node == parent) {
                continue;
            }

            int next_node_rank = findClusterNotCriticalConnections(graph, node_rank, connections, next_node, current_node);
            if (next_node_rank <= node_rank[current_node]) {
                if (next_node < current_node) {
                    connections.erase({next_node, current_node});
                } else {
                    connections.erase({current_node, next_node});
                }
            }

            min_node_rank = min(min_node_rank, next_node_rank);
        }
        return min_node_rank;
    }

    void findNotCriticalConnections(matrix& graph, set<pair<int, int>>& connections) {
        vector<int> node_rank(graph.size(), -1);

        for (int i = 0; i < graph.size(); ++i) {
            if (node_rank[i] == -1) {
                findClusterNotCriticalConnections(graph, node_rank, connections, i, -1);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, matrix& connections) {
        vector<vector<int>> graph(n);
        set<pair<int, int>> connections_set;

        for (int i = 0; i < connections.size(); ++i) {
            auto connection = connections[i];
            graph[connection[0]].push_back(connection[1]);
            graph[connection[1]].push_back(connection[0]);

            if (connection[0] < connection[1]) {
                connections_set.insert({connection[0], connection[1]});
            } else {
                connections_set.insert({connection[1], connection[0]});
            }
        }

        vector<vector<int>> result;
        findNotCriticalConnections(graph, connections_set);

        for (auto& connection: connections_set) {
            result.push_back({connection.first, connection.second});
        }

        return result;
    }
};