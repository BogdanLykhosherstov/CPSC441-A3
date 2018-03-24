// A C / C++ program for Dijkstra's single source shortest
// path algorithm. The program is for adjacency matrix
// representation of the graph.
#include <iostream>
#include <stdio.h>
#include <limits>
#include <string>
#include <map>
using namespace std;

// Number of vertices in the graph
#define V 26
int home;
int SHP[26][26];
int SDP[26][26];
int STP[26][26];
int FTP[26][26];
int GOLD[26][26];
string addressbook[26];

// A utility function to find the vertex with minimum distance
// value, from the set of vertices not yet included in shortest
// path tree
int minDistance(int dist[], bool sptSet[])
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] < min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print shortest path from source to j
// using parent array
string & printPath(int parent[], int j, string & path, char src)
{
    // Base Case : If j is source
    if (parent[j]==-1){
        return path+=src;
    }

    path = path+(char)(j+65);
    printPath(parent, parent[j], path, src);

}
int calculate(int array[26][26], string path){

  int result = 0;
  //Calculate cumilitive property(Dist, Time, Gold, Trolls)
  for(int i=1;i<path.length();i++){
    int newpath = ((int)path[i])-65;
    int previouspath = ((int)path[i-1])-65;
    result+=array[newpath][previouspath];
  }

  return result;
}



void printLayout(int dist[], int n, int parent[])
{
  int src = home;
  string path = "";
  double avgHops=0;
  double avgDist=0;
  double avgTime=0;
  double avgGold=0;
  double avgTrolls=0;

  int count=0;
  // printf("Home\t  Distance\tPath");
  printf(" Dwarf\t  Home\t Hops\t Dist\t Time \t Gold\tTrolls\t Path");
  printf("\n -------------------------------------------------------------\n");
  for (int i = 1; i < V; i++)
  {
      if( (dist[i]!=2147483647) && dist[i]>0){
          string returnPath = printPath(parent, i, path, (char)(src+65));
          cout<<" "<<addressbook[i];
          int hops = (returnPath.length())-1;
          printf("\t   %c  \t  %d\t %d\t %d  \t   %d  \t   %d\t ", ((char)(i+65)), hops, calculate(SDP, returnPath), calculate(STP, returnPath), calculate(GOLD, returnPath), calculate(FTP, returnPath));
          cout<<returnPath<<endl;
          count++;
          //adding up the totals

          avgHops+=hops;
          avgDist+=calculate(SDP, returnPath);
          avgTime+=calculate(STP,returnPath);
          avgGold+=calculate(GOLD, returnPath);
          avgTrolls+=calculate(FTP, returnPath);
          //making path zero at the end

          path = "";




      }

  }
  avgDist = avgDist / count;
  avgTime = avgTime / count;
  avgGold = avgGold / count;
  avgHops = avgHops / count;
  avgTrolls = avgTrolls / count;
  printf(" -------------------------------------------------------------\n");
  printf(" AVERAGE\t %.2f  %.2f   %.2f    %.2f   %.2f\n", avgHops, avgDist, avgTime, avgGold, avgTrolls);
}
// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int graph[V][V], int src)
{
    int dist[V];  // The output array. dist[i] will hold
                  // the shortest distance from src to i

    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    bool sptSet[V];

    // Parent array to store shortest path tree
    int parent[V];

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
    {
        parent[i] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = false;
    }

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V-1; count++)
    {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++){

            // Update dist[v] only if is not in sptSet, there is
            // an edge from u to v, and total weight of path from
            // src to v through u is smaller than current value of
            // dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
            {
                parent[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // print the constructed distance array
    printLayout(dist, V, parent);
}

// driver program to test above function
int main()
{
    char map_name[16];
    char address_name[16];
    printf("Enter the name of the map: \n");
    scanf("%s", &map_name);
    printf("Enter the name of the address book: \n");
    scanf("%s", &address_name);
    string bilbo = "Bilbo";
    char name[100];
    char name_char;
    int flag;

    char source, dest;
    int distance, traveltime, coin, trolls;
    FILE *fp;
    FILE *fc;
    fp = fopen(map_name, "r");
    //Declare the matrix being 26 at maximum size foreach letter of Alphabet
    SHP[26][26] = { 0 };
    SDP[26][26] = { 0 };
    STP[26][26] = { 0 };
    FTP[26][26] = { 0 };
    GOLD[26][26] = { 0 };

    fc = fopen(address_name, "r");
    while(fscanf(fc, "%s %c\n", name, &name_char)!=EOF){
      if(bilbo.compare(string(name))==0){
        home = ((int)name_char)-65;
      }
      addressbook[((int)name_char)-65]= string(name);
    }
    fclose(fc);
    while(fscanf(fp, "%c %c %d %d %d %d\n", &source, &dest, &distance, &traveltime, &coin, &trolls)!=EOF){
        SHP[((int)source)-65][((int)dest)-65] = 1;
        SHP[((int)dest)-65][((int)source)-65] = 1;

        SDP[((int)source)-65][((int)dest)-65] = distance;
        SDP[((int)dest)-65][((int)source)-65] = distance;

        STP[((int)source)-65][((int)dest)-65] = traveltime;
        STP[((int)dest)-65][((int)source)-65] = traveltime;

        FTP[((int)source)-65][((int)dest)-65] = trolls;
        FTP[((int)dest)-65][((int)source)-65] = trolls;

        GOLD[((int)source)-65][((int)dest)-65] = coin;
        GOLD[((int)dest)-65][((int)source)-65] = coin;
    }

    fclose(fp);
    //populating address book


    //takes in C(2) as src
    while(flag!=-1){
      printf("\n Enter:\n ----------------\n 0 for SHP\n 1 for SDP\n 2 for STP\n 3 for FTP.\n ----------------\n Enter -1 to exit: \n");
      scanf("%d", &flag);
      if(flag==0){
        dijkstra(SHP, home);
      }
      else if(flag==1){
        dijkstra(SDP, home);
      }
      else if(flag==2){
        dijkstra(STP, home);
      }
      else if(flag==3){
        dijkstra(FTP, home);
      }
      else if(flag!=-1){
        printf("\n Incorrect choice, please try again. \n");
      }
    }

    return 0;
}
