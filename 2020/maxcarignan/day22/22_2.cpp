#include <bits/stdc++.h>
using namespace std;

string recursiveCombat(std::vector<int>&player1, std::vector<int>&player2)
{
    vector<vector<int> >previousRounds;
    string winner;
    while (player1.size() >0 && player2.size() >0)
    {
        vector <int> currentRound;
        for (int i=0; i<player1.size(); i++) 
            currentRound.push_back(player1[i]); 

        currentRound.push_back(-1); 
        currentRound.insert( currentRound.end(), player2.begin(), player2.end());

        for(int i=0;i<previousRounds.size();i++)
        {
            if(previousRounds[i] == currentRound)
                return "Player1";
        }
        previousRounds.push_back(currentRound);

        int p1Card =  player1[0];
        int p2Card =  player2[0];
        player1.erase(player1.begin());
        player2.erase(player2.begin());
       
        if (player1.size() >= p1Card && player2.size() >= p2Card) 
        {
            vector<int> subgame1, subgame2;
            for (int i=0; i<p1Card; i++) 
                subgame1.push_back(player1[i]); 
            for (int j=0; j<p2Card; j++) 
                subgame2.push_back(player2[j]); 

            winner = recursiveCombat(subgame1, subgame2);
        } 
        else 
        {
            if(p1Card>p2Card)
                winner = "Player1";
            else 
                winner = "Player2";
        }

        if(winner == "Player1")
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
    return winner;
}

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

        string combatWinner =recursiveCombat(player1,player2);

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