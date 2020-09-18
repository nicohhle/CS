// #define // printLine cout << endl << __LINE__ << endl;
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include "Graph.h"

using namespace std;

Graph::Graph() {
}

Graph::Graph(ifstream &infile) {
    unsigned v = 0;
    unsigned e = 0;
    
    infile >> v;
    infile >> e;
    
    string str = "";
    
    for (unsigned i = 0; i < v; ++i) {
        vertices.push_back(Vertex());
        infile >> str;
        
        vertices.at(i).label = str;
    }
    
    string start = "";
    string end = "";
    int weight = 0;
    
    for (unsigned i = 0; i < e; ++i) {
        infile >> start;
        infile >> end;
        infile >> weight;
        
        // making a pair:
        //      makePair(1, 2) where
        //          1 - where the thing is relative to the start vector
        //          2 - data to be stored (weight)
        
        unsigned loc = 0;
        // unsigned cost = 0;
        
        for (unsigned j = 0; j < vertices.size(); ++j) {
            if (vertices.at(j).label == end) {
                loc = j;
                break;
            }
        }
        
        for (unsigned k = 0; k < vertices.size(); ++k) {
            if (vertices.at(k).label == start) {
                vertices.at(k).neighbors.push_back(make_pair(loc, weight));
            }
        }
    }
    
}

Graph::~Graph() {
    
}

void Graph::output_graph(const string &s, Graph &g) {
    ofstream outfile;
    outfile.open(s.c_str());
    
    if (!outfile.is_open()) {
        cout << "Error opening file" << endl;
        return;
    }
    
    output_graph(outfile, g);
    outfile.close();
}

void Graph::output_graph(ofstream &out, Graph &g) {
    out << "digraph g1 {\n";
    out << "node[fontname = \"Arial\"];\n";
    
    // printLine
    for (size_t i = vertices.size() - 1; i >= 0; --i) {
        // cout << i << endl;
        // cout << vertices.at(i).label << endl;
        if (!(vertices.at(i).prev)) {
            break;
        }
        // printLine
    
        out << vertices.at(i).prev->label << to_string(vertices.at(i).prev->distance) << " -> "
            << vertices.at(i).label << to_string(vertices.at(i).distance) << '\n';
    }
    
    out << "}\n";
}

string Graph::to_string(int i) {
    stringstream ss;
    ss << i;
    return ss.str();
}

void Graph::bfs() {
    // printLine
    queue<Vertex> discovered;
    
    // printLine
    vertices.at(0).color = "GRAY";
    vertices.at(0).distance = 0;
    vertices.at(0).prev = 0;
    
    // printLine
    discovered.push(vertices.at(0));
    
    while (!discovered.empty()) {
        // printLine
        Vertex *u = new Vertex();
        
        // printLine
        *u = discovered.front();
        discovered.pop();
        
        // printLine
        list<pair<int, int> > :: iterator it;
        for (it = u->neighbors.begin(); it != u->neighbors.end(); ++it) {
            // printLine
            
            // cout << vertices.at(it->first).label << endl;
            // cout << vertices.at(it->first).color << endl;
            // cout << it->first << endl;
            
            if (vertices.at(it->first).color == "WHITE") {
                // printLine
                vertices.at(it->first).color = "GRAY";
                vertices.at(it->first).distance = u->distance + 1;
                vertices.at(it->first).prev = u;
                // printLine
                cout << vertices.at(it->first).prev->label << endl;
                discovered.push(vertices.at(it->first));
                
            }
        }
        
        // printLine
        u->color = "BLACK";
    }
    // cout << vertices.at(0).label << endl;
}