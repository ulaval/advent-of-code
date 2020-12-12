#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

long long findAllPaths(std::vector<int>&adapters)
{
    long long answer = 0;
    std::map<int,long long> possibleSolutions;
    possibleSolutions[adapters[adapters.size()-1]]=1;

    for(int i= adapters.size()-2;i>=0;i--)
    {
        for(int j=1;j<=3;j++)
        {
            possibleSolutions[adapters[i]]+= possibleSolutions[adapters[i]+j];
        }
    }
    
    for(int k=1;k<=3;k++)
        answer+= possibleSolutions[k];
return answer;
}

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


    std::sort(adapters.begin(),adapters.end());
    adapters.push_back(adapters[adapters.size()-1]+3);

  std::cout<<findAllPaths(adapters)<<std::endl;
  
 } 
  return 0;
}