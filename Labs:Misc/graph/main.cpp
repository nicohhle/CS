#include <iostream>
#include <cstring>
#include "Graph.h"

using namespace std;

int main(int argc, char* argv[]) {

//   if(argc != 2) {
//     cerr << "Usage error: expected <executable> <input>" << endl;
//     exit(1);
//   }

//   ifstream ifs(argv[1]);
//   if(!ifs) {
//     cerr << "Input file not found." << endl;
//     exit(1);
//   }
  
    ifstream ifs("input1.txt");
    Graph g(ifs);
    ifs.close();
    g.bfs();
    string filename = "output1.dot";
//   strcat(argv[1] , ".dot");
    g.output_graph(filename, g);
  
    string jpgFilename = filename.substr(0, filename.size()-4)+".jpg";
    string command = "dot -Tjpg " + filename + " -o " + jpgFilename;
    system(command.c_str());
//   filename = "input2.txt";
//   g.output_graph(filename, g);
  
  cout << "The End." << endl;
  
  return 0;
}