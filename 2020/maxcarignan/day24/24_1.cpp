#include <bits/stdc++.h>
using namespace std;

struct hexTile
{
    int x=0;
    int y=0;
    int z=0;
     hexTile(int x, int y, int z, bool white) : x(x) ,y(y),z(z){}
};

vector<string> parseInstructions(string data)
{
    vector<string> tileInstructions;
    int counter=0;

     for (int i = 0; i < data.size(); i++) 
     {
        if(data[i]== 'e')
            tileInstructions.push_back("e");
        else if(data[i]== 'w')
            tileInstructions.push_back("w");
        else if(data[i]== 's' && data[i+1]== 'w')
        {
            tileInstructions.push_back("sw");
            i++;
        }
        else if(data[i]== 's' && data[i+1]== 'e')
        {
            tileInstructions.push_back("se");
            i++;
        }
        else if(data[i]== 'n' && data[i+1]== 'w')
        {
            tileInstructions.push_back("nw");
            i++;
        }          
        else if(data[i]== 'n' && data[i+1]== 'e')
        {
            tileInstructions.push_back("ne");
            i++;
        }
            
     }
    return tileInstructions;
}

hexTile findTileOnFloor(vector<string> instruction)
{
    hexTile tmp(0,0,0,true);
    for(int i=0;i<instruction.size();i++)
    {
        if(instruction[i]== "e")
         {
            tmp.x+=1;
            tmp.y-=1;
         }           
        else if(instruction[i]== "w")
        {
            tmp.x-=1;
            tmp.y+=1;
        }    
        else if(instruction[i]== "sw")
        {
            tmp.x-=1;
            tmp.z+=1;
        }
        else if(instruction[i]== "se")
        {
            tmp.y-=1;
            tmp.z+=1;
        }
        else if(instruction[i]== "nw")
        {
            tmp.y+=1;
            tmp.z-=1;
        }
        else if(instruction[i]== "ne")
        {
            tmp.x+=1;
            tmp.z-=1;
        }
    }
    return tmp;
}

bool operator==(const hexTile& lhs, const hexTile& rhs)
{
  return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

int main()
{
    std::ifstream inFile("day24.txt");
    if (inFile.is_open())
    {        
        std::string data;    
        std::vector<vector<string> > instructions;
        std::vector<hexTile> blackTiles;
       
        while (std::getline(inFile, data))
        { 
           instructions.push_back(parseInstructions(data));
        }
        inFile.close();

        for(int i=0;i<instructions.size();i++)
        {
            hexTile toCheck =findTileOnFloor(instructions[i]);
            auto it=std::find(blackTiles.begin(), blackTiles.end(), toCheck);
            if(it != blackTiles.end())
            {
                blackTiles.erase(it,it+1);
            }
            else
            {
                blackTiles.push_back(toCheck);
            }
        }

     std::cout<<blackTiles.size()<<endl;   
    } 
return 0;
}