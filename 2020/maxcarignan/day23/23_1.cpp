#include <bits/stdc++.h>
using namespace std;

struct Cup{
    int val;
    Cup* next;

};
int main()
{
    std::ifstream inFile("day23.txt");
    if (inFile.is_open())
    {        
        std::string data;    
        Cup *currentCup;
        Cup *FirstCup;
        int nbCups=9;
        int nbRounds=100;
        std::vector<Cup> cups(nbCups+1);
        
        while (std::getline(inFile, data)){ }
        inFile.close();

        cups[data[0]-'0'].val = data[0]- '0';
        currentCup =&cups[data[0]-'0'];
        FirstCup = currentCup;

        for(int i=1;i<nbCups-1;i++)
        {
            int datai= 0;
            if(i<data.size())
                datai=data[i]- '0';
            else
                datai=i+1;
                
            cups[datai].val = datai;             
            currentCup->next = &cups[datai];   
            currentCup =&cups[datai];                              
        }

        cups[data.back()- '0'].val=data.back()- '0';               
        cups[data.back()- '0'].next = FirstCup;
        currentCup->next = &cups[data.back()- '0'];          
     
        currentCup = FirstCup;

        for(int i=0;i<nbRounds;i++)
        {
            Cup* First = currentCup->next;
            Cup* Second = First->next;
            Cup* Third = Second->next;
            
            int destination = currentCup->val;
            destination = 1 + ((nbCups + destination - 2) % nbCups);
            while (destination == First->val || destination == Second->val || destination == Third->val || destination <1 || destination >nbCups)
            {
                destination = 1 + ((nbCups + destination - 2) % nbCups);
            }
            
            currentCup->next = Third->next;          
            Cup * destinationCup = &cups[destination];
            Cup* beforeCup = destinationCup->next;
            destinationCup->next = First;       
            Third->next = beforeCup;
        
            currentCup = currentCup->next;            
        }

        currentCup = FirstCup;
        for(int i=0;i<cups.size()-1;i++)
        {
            std::cout<<currentCup->val;
            currentCup= currentCup->next;
        } 
    } 
return 0;
}