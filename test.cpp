#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <fstream>
#include <limits> // for numeric_limits

#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
using namespace std;

int main(){
  char st[]  = "CERSVWMT";
  for(int i=0; i<(sizeof(st)-1); i++){
    int is = st[i] - 'A';
    printf("%c converted to integer is: %d\n",st[i],is);
  }


  return 0;
}
