//#define printLine cout << endl << __LINE__ << endl;
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

#include "Jug.h"

using namespace std;

// ------------------------ Data Structures ----------------------------------------------------------------

// Priority Queue - find min path
// Vector - store vertices
// Array - edges
// Set - cloud
// ---------------------------------------------------------------------------------------------------------
// ------------------------ ALL Variables ----------------------------------------------------------------

// public (Vertex):
// int capA, capB -- capacities of Jugs A and B
// int end -- (N) our goal of min cost 

// private (Jug):
// int cA, cB -- capacities of Jugs A and B
// int cfA, cfB -- cost to fill Jugs A and B
// int ceA, ceB -- cost to empty Jugs A and B
// int cpAB -- cost to pour A to B
// int cpBA -- cost to pour B to A
// ---------------------------------------------------------------------------------------------------------
// ------------------------ ALL Variables ----------------------------------------------------------------


// ---------------------------------------------------------------------------------------------------------
// ------------------------ CONSTRUCTORS ----------------------------------------------------------------

Jug::Jug(int cA,int cB,int N,int cfA,int cfB,int ceA,int ceB,int cpAB,int cpBA) 
{
    //invalid input will return -1 in solve
    // vertify that capacity and goal are valid
    if (!((0 < cA && cA <= cB) && (N <= cB && cB <= 1000))) 
    {
        valid = false;
    }
    //verify that cost is positive 
    else if (!(cfA > 0 && cfB > 0 && ceA > 0 && ceB > 0 && cpAB > 0 && cpBA > 0)) 
    {
        valid = false;
    }
    else if (valid) 
    {
        //set everything to what it's supposed to be
        capA = cA; capB = cB; end = N;
        costs[0] = cfA;
        costs[1] = cfB;
        costs[2] = ceA;
        costs[3] = ceB;
        costs[4] = cpAB;
        costs[5] = cpBA;
        
        //building the graph
        //resize columns and rows to look like table drawn in class
        graph.resize(cA + 1, vector<Vertex*>(cB + 1));
        
        for (unsigned i = 0; i < graph.size(); ++i)
        {
            for (unsigned j = 0; j < graph.at(i).size(); ++j)
            {
                // building a vector of vectors of Vertex pointers
                graph.at(i).at(j) = 0;
            }
        }
        buildGraph();
    }
}

Jug::~Jug() 
{
    if (!graph.empty()) 
    {
        for (int i = 0; i < capA; ++i) 
        {
            for (int j = 0; j < capB; ++j) 
            {
                delete graph.at(i).at(j);
            }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------
// ------------------------ SOLVE FUNCTION ----------------------------------------------------------------
//solve is used to check input and find the solution if one exists
//returns -1 if invalid inputs. solution set to empty string.
//returns 0 if inputs are valid but a solution does not exist. solution set to empty string.
//returns 1 if solution is found and stores solution steps in solution string.
int Jug::solve(string &solution)
{
    if (!valid)
    {
        solution = "";
        return -1;
    }
    
    if (!(graph.empty()))
    {
        if (solution != "")
        {
            solution += "\n\n";
            //printLine
            }
            //Dijkstra's Algorithm
            graph.at(0).at(0)->distance = 0;
            
            Vertex *start = graph.at(0).at(0);
            Vertex *goal = 0;
            
            //use LessThanDistance to order them
            priority_queue<Vertex*, vector<Vertex*>, LessThanDistance> vertices;
            
            vertices.push(start);
            
            //printLine
            while (!(vertices.empty()))
            {
                Vertex *u = vertices.top();
                vertices.pop();
                
                if (u->a == 0 && u->b == end) 
                {
                    goal = u;
                    break;
                }
                //printLine
                //relaxation step
                if (!(u->edges.empty()))
                {
                    for (auto it = u->edges.begin(); it != u->edges.end(); ++it) 
                    {
                        if (it->first->distance > u->distance + it->second) 
                        {
                            it->first->distance = u->distance + it->second;
                            it->first->prev = u;
                            
                            vertices.push(it->first);
                        }
                    }
                }
            }
            //printLine
            if (goal) 
            {
                Vertex *print = goal;
                stack<string> path;
                int total = 0;
                while (goal != graph.at(0).at(0)) 
                {
                
                for (list<pair<Vertex*, int> > :: iterator i = goal->prev->edges.begin(); i != goal->prev->edges.end(); ++i)
                    {
                       if (i->first == goal) 
                        {
                            total += i->second;
                            break;
                        }
                    }
                    //printLine
                    goal = goal->prev;
                }
                
                while (print->prev) 
                {
                    //push name onto stack then go backwards
                    path.push(print->name);
                    print = print->prev;
                }    
                
                //until the stack is empty, add to solution and pop top
                while (!(path.empty()))     
                {    
                    solution += path.top();
                    path.pop();
                }

                stringstream ss;
                string s;
                ss << total;
                ss >> s;
                solution += "success " + s;
                //printLine
                
                return 1;
            }
            else 
            {
                solution = "";
                return 0;
            }
            //printLine
    }
    //printLine
    solution = "";
    return -1;
}

// ---------------------------------------------------------------------------------------------------------
// ------------------------ BUILD GRAPH ----------------------------------------------------------------

void Jug::buildGraph()
{
    //initialize the first vertex
    graph.at(0).at(0) = new Vertex(0, 0);
    //make queue to find min path
    //will hold discovered vertices
    queue<Vertex*> q;
    q.push(graph.at(0).at(0));
    
    while (!(q.empty())) 
    {
        Vertex *curr = q.front();
        q.pop();
        
        //filling A
        //A is not at capacity
        if (curr->a < capA)
        { 
            // check if vertex exists
            if (!graph.at(capA).at(curr->b))
            {
                // create new vertex there, push onto queue, give it a name
                graph.at(capA).at(curr->b) = new Vertex(capA, curr->b);
                q.push(graph.at(capA).at(curr->b));
                graph.at(capA).at(curr->b)->name = "fill A\n";
            }
            
            pair<Vertex *, int> neighbor(graph.at(capA).at(curr->b), costs[0]);
            curr->edges.push_back(neighbor);
        }
    
        //filling B
        //B is not at capacity
        if (curr->b < capB) 
        {
            //follow same process as A
            if (!(graph.at(curr->a).at(capB)))
            {
                graph.at(curr->a).at(capB) = new Vertex(curr->a, capB);
                q.push(graph.at(curr->a).at(capB));
                graph.at(curr->a).at(capB)->name = "fill B\n";
            }
            
            pair <Vertex*, int> neighbor(graph.at(curr->a).at(capB), costs[1]);
            curr->edges.push_back(neighbor);
        }
    
        //empty A
        //A is not empty
        if (curr->a > 0) 
        {
            if (!(graph.at(0).at(curr->b))) 
            {
                graph.at(0).at(curr->b) = new Vertex(0, curr->b);
                q.push(graph.at(0).at(curr->b));
                graph.at(0).at(curr->b)->name = "empty A\n";
            }
            
            pair<Vertex*, int> neighbor (graph.at(0).at(curr->b), costs[2]);
            curr->edges.push_back(neighbor);
        }
    
        //empty B
        //B is not empty
        if (curr->b > 0)
        {
            if (!(graph.at(curr->a).at(0)))
            {
                graph.at(curr->a).at(0) = new Vertex(curr->a, 0);
                q.push(graph.at(curr->a).at(0));
                graph.at(curr->a).at(0)->name = "empty B\n";
            }
            
            pair<Vertex *, int> neighbor (graph.at(curr->a).at(0), costs[3]);
            curr->edges.push_back(neighbor);
        }
    
        //pouring A to B
        //A is not empty and B is not at capacity
        if (curr->a > 0 && curr->b < capB) {
            //nothing should be changed YET
            int newA = curr->a;
            int newB = curr->b;
            
            //new variables must still fulfill conditions
            //then slowly empty
            while (newA > 0 && newB < capB)
            {
                newA--;
                newB++;
            }
            
            //check if vertex still exists 
            if (!(graph.at(newA).at(newB))) 
            {
                graph.at(newA).at(newB) = new Vertex(newA, newB);
                q.push(graph.at(newA).at(newB));
                // graph.at(newA).at(newB)->name = "pour A B\n";
            }
            graph.at(newA).at(newB)->name = "pour A B\n";
            pair<Vertex*, int> neighbor (graph.at(newA).at(newB), costs[4]);
            curr->edges.push_back(neighbor);
        }
    
        //pouring B to A
        //B is not empty and A is not at capacity
        if (curr->a < capA && curr->b > 0) 
        {
            //same process as pouring A to B
            int newA = curr->a;
            int newB = curr->b;
            
            while (newA < capA && newB > 0) 
            {
                newA++;
                newB--;
            }
            
            if (!(graph.at(newA).at(newB)))
            {
                graph.at(newA).at(newB) = new Vertex(newA, newB);
                q.push(graph.at(newA).at(newB));
                graph.at(newA).at(newB)->name = "pour B A\n";
            }
            
            pair<Vertex*, int> neighbor (graph.at(newA).at(newB), costs[5]);
            curr->edges.push_back(neighbor);
        }
    }
}

// ---------------------------------------------------------------------------------------------------------