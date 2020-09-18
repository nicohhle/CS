#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <climits>
#include <vector>
#include <set>
#include <stack>
#include <functional>
#include <utility>

using namespace std;

// priority queue to find min path
// vector for vertices, array to store edges
// q to build graph
// stack to output

#ifndef JUG_H
#define JUG_H

class Vertex 
{
  public:
    list<pair<Vertex*, int> > edges;
    int distance;
    string name;
    Vertex* prev;
    
    int a, b;
    
    Vertex() { 
        distance = INT_MAX; 
        a = -1; b = -1; // there is no existing vertex
        name = ""; }
    Vertex(int x, int y) { 
        a = x; b = y;
        distance = INT_MAX;
        name = ""; }
};

class Jug 
{
    public:
        Jug(int,int,int,int,int,int,int,int,int);
        ~Jug();

        //solve is used to check input and find the solution if one exists
        //returns -1 if invalid inputs. solution set to empty string.
        //returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
        //returns 1 if solution is found and stores solution steps in solution string.
        int solve(string &solution);
    
    private:
        vector< vector<Vertex *> > graph;
        int costs[6];
        bool valid = true;
        
        int end, capA, capB;
        
        void buildGraph();
};

struct LessThanDistance : public binary_function<Vertex *, Vertex*, bool> 
{
    bool operator() (Vertex *lhs, Vertex *rhs) 
    {
        return (lhs->distance > rhs->distance);
    }
};

#endif