#include <bits/stdc++.h>
using namespace std;

int main()
{
  std::ifstream inFile("day9.txt");
  if (inFile.is_open())
  {
    std::vector<long long> allNumbers;
    std::string data;
    while (std::getline(inFile, data))
    { 
        allNumbers.push_back(stoll(data));
    }
    inFile.close();

    int preamble=25;
    int counter=0;

    for(int i=preamble;i<allNumbers.size();i++)
    {
        for(int j=counter;j<=preamble+counter;j++)
        {
            for(int k=counter+1;k<=preamble+counter;k++)
            {
                if(allNumbers[j]+allNumbers[k] == allNumbers[i])
                {
                    goto endLoops;
                }
            }
        }
        break;

        endLoops:
            counter++;
    }

  long long answer = allNumbers[preamble+counter];
  std::cout<<answer<<std::endl;
 } 
  return 0;
}