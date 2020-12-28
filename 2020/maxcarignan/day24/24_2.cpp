#include <bits/stdc++.h>
using namespace std;

struct hexTile
{
    int x=0;
    int y=0;
    int z=0;
    std::vector<hexTile *> adjacentTiles;
     hexTile(int x, int y, int z) : x(x) ,y(y),z(z){}
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
    hexTile tmp(0,0,0);
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

void getAdjacentTile(int i, hexTile& tile)
{
        if(i==0)
        {
            tile.x++;
            tile.y--;
        }
        else if(i==1)
        {
            tile.x++;
            tile.z--;
        }
        else if(i==2)
        {
            tile.y++;
            tile.z--;
        }
        else if(i==3)
        {
            tile.x--;
            tile.y++;
        }
        else if(i==4)
        {
            tile.x--;
            tile.z++;
        }
        else if(i==5)
        {
            tile.y--;
            tile.z++;
        }        
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

        for (int round=0;round<100;round++) 
        {
            std::vector<hexTile> newBlackTiles;
            for (int i=0;i<blackTiles.size();i++)
            {
                for (int j=0;j<7;j++) 
                {
                    hexTile adjacent(blackTiles[i].x, blackTiles[i].y, blackTiles[i].z);
                        getAdjacentTile(j,adjacent);

                    int counter = 0;
                    for (int k=0;k<6;k++) 
                    {
                        hexTile adjacentBlack(adjacent.x, adjacent.y, adjacent.z);
                        getAdjacentTile(k,adjacentBlack);

                        if (std::find(blackTiles.begin(), blackTiles.end(), adjacentBlack) != blackTiles.end()) 
                            counter++;
                    }

                    if (std::find(blackTiles.begin(), blackTiles.end(), adjacent) != blackTiles.end() && !(counter == 0 || counter > 2)) 
                        if (std::find(newBlackTiles.begin(), newBlackTiles.end(), adjacent) == newBlackTiles.end())
                            newBlackTiles.push_back(adjacent);

                    if (std::find(blackTiles.begin(), blackTiles.end(), adjacent) == blackTiles.end() && counter == 2) 
                        if (std::find(newBlackTiles.begin(), newBlackTiles.end(), adjacent) == newBlackTiles.end())
                            newBlackTiles.push_back(adjacent);
                }
            }    
            blackTiles.swap(newBlackTiles);
        }

    std::cout<<blackTiles.size()<<endl;   
    } 
return 0;
}