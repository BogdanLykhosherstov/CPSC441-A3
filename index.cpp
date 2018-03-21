#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <limits> // for numeric_limits
#include <stdio.h>
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>

using namespace std;

// typedef int typedef int int;
// typedef double double;;



const double max_weight = numeric_limits<double>::infinity();

struct neighbor {
    int target;
    double weight;
    neighbor(int arg_target, double arg_weight)
        : target(arg_target), weight(arg_weight) { }
};
//myStructureForHobbitPaths


typedef vector<vector<neighbor> > adjacency_list_t;


void DijkstraComputePaths(int source,
                          const adjacency_list_t &adjacency_list,
                          vector<double> &min_distance,
                          vector<int> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    set<pair<double, int> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));

    while (!vertex_queue.empty())
    {
        double dist = vertex_queue.begin()->first;
        int u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());

        // Visit each edge exiting u
	const vector<neighbor> &neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            int v = neighbor_iter->target;
            double weight = neighbor_iter->weight;
            double distance_through_u = dist + weight;
	    if (distance_through_u < min_distance[v]) {
	        vertex_queue.erase(make_pair(min_distance[v], v));

	        min_distance[v] = distance_through_u;
	        previous[v] = u;
	        vertex_queue.insert(make_pair(min_distance[v], v));

	    }

        }
    }
}


list<int> DijkstraGetShortestPathTo(
    int vertex, const vector<int> &previous)
{
    list<int> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}



int main()
{


    //My code
    ifstream inFile("canadamap.txt");
    string s;
    string delimiter = " ";
    // string printout = "";
    //IMPORTANT ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    //FIXED SIZE OF THE ARRAY = 10: POTENTIAL PROBLEM/LIMITATION

    //IMPORTANT ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    //double the size for one direction and another
    int SIZE = 20;
    vector<vector<int>> SHP_Array(SIZE);


    vector<vector<string>> SDP_Array(10);
    vector<vector<string>> STP_Array(10);
    vector<vector<string>> FTP_Array(10);
    int elementNum = 0;
    string testString;
    int rowNum = 0;
    int firstEl;
    int secondEl;
    int thirdEl;

    while(inFile){
        getline(inFile, s);
        cout << s << endl;
        size_t pos = 0;
        string token;
          while ((pos = s.find(delimiter)) != string::npos) {
          token = s.substr(0, pos);
          // cout << token << endl;
          //populate 2d array

          //1 .SHP
          //--Consists of Src, Dest, Link=1
          //Src, Dest are ASCII converted into INT where
          // C = 2
          // E = 4
          // M = 12
          // R = 17
          // S = 18
          // T = 19
          // V = 21
          // W = 22


          //pushing one then the other direction

          if(elementNum == 0 || elementNum == 1 || elementNum == 4){
            //on the last element just put 1 indicating link number
            if (elementNum ==4) {
                thirdEl = 1;
                SHP_Array[rowNum].push_back(1);
                printf("Appended 1 in row: %d, elementNum: %d\n", rowNum, elementNum);
            }
            //pushing src
            else if (elementNum == 0){

                char token_char = token[0];
                int i = token_char - 'A';
                //gotta subtract cuz it gets messed up for some reason
                token_char-= 65;
                firstEl = token_char;
                SHP_Array[rowNum].push_back(token_char);

                cout << "Appended " << token;
                printf(" in row: %d, elementNum: %d\n", rowNum, elementNum);
            }
            //pushing target
            else if(elementNum == 1){
              char token_char = token[0];
              int i = token_char - 'A';
              //gotta subtract cuz it gets messed up for some reason
              token_char-= 65;
              secondEl = token_char;
              SHP_Array[rowNum].push_back(token_char);

              cout << "Appended " << token;
              printf(" in row: %d, elementNum: %d\n", rowNum, elementNum);
            }

          }


          //2. SDP
          //3. STP
          //4. FTP
          s.erase(0, pos + delimiter.length());
          elementNum++;
        }

        // cout << s << endl;
        elementNum = 0;
        //INVERSE PATHS PUSHED TO DUPLICATE ARRAY



        rowNum+=1;
        if(rowNum<SIZE){
          SHP_Array[rowNum].push_back(secondEl);
          SHP_Array[rowNum].push_back(firstEl);
          SHP_Array[rowNum].push_back(thirdEl);
          rowNum+=1;
        }

    }

    inFile.close();
    //reversing direction to make things bidirectional

    //SORT BY LETTERS
    sort(  SHP_Array.begin(),   SHP_Array.end(),
          [](const vector<int>& a, const vector<int>& b) {
              return a[0] < b[0];
    });

    for(int i=0; i<(SHP_Array.size()); i++){
      for(int r=0; r<(SHP_Array[i].size()); r++){
        printf("ELEMENTS %d : %d \n",i,SHP_Array[i][r] );
      }

    }

    //Now adding values to adjacency list
    //1. destination is always C
    //2. 8 different nodes in total
    //3. do this double for loop 2 times: 1 for one direction, 2  for other direction(since bidirect.)
    adjacency_list_t adjacency_list(8);

    int neighb;
    int cost;
    //get first element, change it later
    int srcNode = SHP_Array[0][0];
    int insertlocation = 0;
    int innercount=0;
    //First time around
    for(int i=0; i<(SHP_Array.size()); i++){

        for(int r=0; r<(SHP_Array[i].size()); r++){
          //first entry is home

          if(r == 0){
            //do nothing
            if(SHP_Array[i][r] == srcNode){
                //do nothing
            }
            else{
              insertlocation++;
              srcNode = SHP_Array[i][r];
            }
          }
          //second is neighbor
          else if(r == 1){
            neighb = SHP_Array[i][r];
          }
          //third is cost
          else if(r == 2){
            cost = SHP_Array[i][r];
            adjacency_list[insertlocation].push_back(neighbor(neighb, cost));

            printf("Node: %d, Pushed: neighbor(%d, %d)\n",insertlocation, neighb, cost);
          }


        }
        innercount=0;
    }

    // remember to insert edges both ways for an undirected graph

    //UNCOMMENT WHEN DONE TESTING

    // adjacency_list_t adjacency_list(6);
    // // 0 = a
    // adjacency_list[0].push_back(neighbor(1, 7));
    // adjacency_list[0].push_back(neighbor(2, 9));
    // adjacency_list[0].push_back(neighbor(5, 14));
    // // 1 = b
    // adjacency_list[1].push_back(neighbor(0, 7));
    // adjacency_list[1].push_back(neighbor(2, 10));
    // adjacency_list[1].push_back(neighbor(3, 15));
    // // 2 = c
    // adjacency_list[2].push_back(neighbor(0, 9));
    // adjacency_list[2].push_back(neighbor(1, 10));
    // adjacency_list[2].push_back(neighbor(3, 11));
    // adjacency_list[2].push_back(neighbor(5, 2));
    // // 3 = d
    // adjacency_list[3].push_back(neighbor(1, 15));
    // adjacency_list[3].push_back(neighbor(2, 11));
    // adjacency_list[3].push_back(neighbor(4, 6));
    // // 4 = e
    // adjacency_list[4].push_back(neighbor(3, 6));
    // adjacency_list[4].push_back(neighbor(5, 9));
    // // 5 = f
    // adjacency_list[5].push_back(neighbor(0, 14));
    // adjacency_list[5].push_back(neighbor(2, 2));
    // adjacency_list[5].push_back(neighbor(4, 9));
    //
    vector<double> min_distance;
    vector<int> previous;
    DijkstraComputePaths(2, adjacency_list, min_distance, previous);
    cout << "Distance from C(0) to M(2): " << min_distance[0] << endl;
    list<int> path = DijkstraGetShortestPathTo(0, previous);
    cout << "Path : ";
    copy(path.begin(), path.end(), ostream_iterator<int>(cout, " "));
    cout << endl;

    //UNCOMMENT END


    return 0;
}
