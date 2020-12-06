#include <bits/stdc++.h>
using namespace std;


int main()
{
    std::ifstream inFile("day6.txt");
    if (inFile.is_open())
    {
        int numberYes=0;
        std::vector<char> yesAnswers;
        std::string data;
        while (std::getline(inFile, data))
        { 
            if(data.size()!=0)
            {
                for(int i=0;i<data.size();i++)
                {
                    std::vector<char>::iterator it = find (yesAnswers.begin(), yesAnswers.end(), data[i]);
                 
                    if (it == yesAnswers.end())
                        yesAnswers.push_back(data[i]);
                }
            }
            else
            {              
                numberYes += yesAnswers.size(); 
                yesAnswers.clear();
            }      
        }
        inFile.close();
 
        numberYes += yesAnswers.size(); 
        std::cout<<numberYes<<endl;
    } 
  return 0;
}