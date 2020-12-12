#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

int main()
{
  std::ifstream inFile("day10.txt");
  if (inFile.is_open())
  {
   std::vector<int> adapters;
    std::string data;
    while (std::getline(inFile, data))
    { 
       adapters.push_back(stoi(data));
    }
    inFile.close();


    int best=0;
    int diff1=0;
    int diff3=0;
    std::sort(adapters.begin(),adapters.end());
    adapters.push_back(adapters[adapters.size()-1]+3);

     if(adapters[0]==1)
        diff1++;

    if(adapters[0]==3)
        diff3++;

    for(int i=0;i<adapters.size()-1;i++)
    {
        if(adapters[i+1]-adapters[i]==1)
            diff1++;

        if(adapters[i+1]-adapters[i]==3)
            diff3++; 
    }

  std::cout<<diff1*diff3<<std::endl;

 } 
  return 0;
}