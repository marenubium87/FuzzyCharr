#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using std::for_each;
using std::vector;
using std::list;
using std::cout;
using std::endl;

class Node {
        public:
            int val;
            vector<Node*> neighbors;
            Node() {
                val = 0;
                neighbors = vector<Node*>();
            }
            Node(int _val) {
                val = _val;
                neighbors = vector<Node*>();
            }
            Node(int _val, vector<Node*> _neighbors) {
                val = _val;
                neighbors = _neighbors;
            }
};

//given an adjacency list (of lists) create a graph with nodes,
//assuming node values correspond to their positions in list
//(one-indexed)
void generateGraph(vector<vector<int>> adj, vector<Node*> & graph) {
    //set up all nodes, create dummy variable so vector is one-indexed for now
    graph.push_back(new Node(-1));
    for(int i = 0; i < adj.size(); i++) {
        Node * pTemp = new Node(i+1);
        graph.push_back(pTemp);
    }
    //set up adjacencies
    for(int i = 0; i < adj.size(); i++) {
        for(int j = 0; j < adj[i].size(); j++) {
            graph[i+1]->neighbors.push_back(graph[adj[i][j]]);
        }
        cout << endl;
    }
}

void printGraph(const vector<Node*> & graph) {
    for(int i = 1; i < graph.size(); i++) {
        if(graph[i] == nullptr) {
            return;
        }
        cout << "Node " << graph[i]->val << " at " << &(graph[i]) << 
            " with adjacency to ";
        if(graph[i]->neighbors.size() == 0) {
            cout << "NOTHING";
        }
        else {
            for(int j = 0; j < graph[i]->neighbors.size(); j++) {
                cout << graph[i]->neighbors[j]->val << " ";
            }
        }
        cout << endl;
    }
}

void cloneGraph(Node* orig, vector<Node*> & clone) {

    list<Node *> needToVisit;
    for(int i = 0; i < 101; i++) {
        clone[i] = nullptr;
    }

    //clone orig node
    clone[orig->val] = new Node(orig->val);
    //create neighbors and adjacency
    for(int i = 0; i < orig->neighbors.size(); i++) {
        //if node doesn't exist we have to make and visit it on the orig tree
        if(clone[orig->neighbors[i]->val] == nullptr) {          
            clone[orig->neighbors[i]->val] = new Node(orig->neighbors[i]->val);
            needToVisit.push_back(orig->neighbors[i]);
        }
        //add neighbor to neighbor list for current node
        clone[orig->val]->neighbors.push_back(clone[orig->neighbors[i]->val]);
    }

    Node * pCurrent = nullptr;
    do {
        pCurrent = needToVisit.front();
        needToVisit.pop_front();

        for(int i = 0; i < pCurrent->neighbors.size(); i++) {
            if(clone[pCurrent->neighbors[i]->val] == nullptr) {
                //Make neighbor if they don't exist yet
                clone[pCurrent->neighbors[i]->val] = new Node(pCurrent->neighbors[i]->val);
                //if we create a new node, we need to go visit it on the orig tree
                needToVisit.push_back(pCurrent->neighbors[i]);

            }
            //add neighbor to neighbor list for current node
            clone[pCurrent->val]->neighbors.push_back(clone[pCurrent->neighbors[i]->val]);
        }
    } while(!needToVisit.empty());

}


int main() {

    vector<vector<int>> adjList = {{2, 3}, {1,5}, {1,7}, {5, 6, 7}, {2, 4, 6}, {4,5,7},{3,4,6}};
    vector<Node*> graph = {};
    generateGraph(adjList, graph);
    cout << "orig:" << endl;
    printGraph(graph);
 
    vector<Node*> clone(101);
    cloneGraph(graph[1], clone);
    cout << "clone:" << endl;
    printGraph(clone);


    return 0;
}