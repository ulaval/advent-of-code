#include <bits/stdc++.h>
using namespace std;

int getNumberYes(const std::vector<std::string>&allAnswers)
{
    int numberYes=0;
    for(int i=0;i<allAnswers[0].size();i++)
    {
        int counter=0;
        for(int j=0;j<allAnswers.size();j++)
            if(std::count(allAnswers[j].begin(), allAnswers[j].end(), allAnswers[0][i])>0)
                counter++;

        if(counter== allAnswers.size())
            numberYes++;
    }
    return numberYes;
}


int main()
{
    std::ifstream inFile("day6.txt");
    if (inFile.is_open())
    {
        int numberYes=0;
        std::vector<string> groupAnswers;
        std::string data;
        while (std::getline(inFile, data))
        {        
            if(data.size()!=0)
            { 
                groupAnswers.push_back(data);
            }
            else
            {
                numberYes+=getNumberYes(groupAnswers);
                groupAnswers.clear();
            }      
        }
        inFile.close();

        numberYes+=getNumberYes(groupAnswers);

        std::cout<<numberYes<<endl;
    } 
  return 0;
}