#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::ifstream inFile("day22.txt");
    if (inFile.is_open())
    {        
        std::string data;    
        std::vector<int> player1;
        std::vector<int> player2;
        int player=1;
        while (std::getline(inFile, data))
        { 
            if(data.size())
            {
                size_t pos = data.find ('Player');
                if(pos == string::npos)
                {
                    if(player ==1)
                        player1.push_back(stoi(data));
                    else
                        player2.push_back(stoi(data));                   
                }                        
             }
             else
                 player++;
        }
        inFile.close();

      while (player1.size() >0 && player2.size() >0)
      {
          int p1Card =  player1[0];
          int p2Card =  player2[0];
          player1.erase(player1.begin());
          player2.erase(player2.begin());
          
          if(p1Card>p2Card)
          {
              player1.push_back(p1Card);
              player1.push_back(p2Card);
          }
          else
          {
              player2.push_back(p2Card);
              player2.push_back(p1Card);
          }

      }

      long long score=0;
      if(player1.size() >0)
      {
          int counter= player1.size();
          for(int i=0;i<player1.size();i++)
          {
              score += (player1[i]*counter);
              counter--;
          }
      }
      else
      {
            int counter= player2.size();
            for(int i=0;i<player2.size();i++)
            {
                score += (player2[i]*counter);
                counter--;
            }
      }
      std::cout<<score<<endl;   
    } 
return 0;
}