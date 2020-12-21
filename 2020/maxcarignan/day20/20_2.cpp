#include "../utils.h" 
using namespace std;

struct Tile
{
    int number=-1;
    std::vector<std::string> data;
    int PosX=-1;
    int PosY=-1;
};

void flipTileHorizontal(Tile& myTile)
{
    for(int i=0;i<myTile.data.size();i++)
    {
        std::reverse(myTile.data[i].begin(),myTile.data[i].end());
    }
}

void rotateTile(Tile& myTile) 
{
    vector<string> tmp = myTile.data;
    for (int i = 0; i <=9; ++i)
      for (int j = 0; j <=9; ++j)    
        tmp[9-j][i] = myTile.data[i][j];

    myTile.data.swap(tmp);
}

void orderTiles( vector<Tile>&tiles,  vector<Tile> &foundTiles) {
    while( tiles.size()>0)
    {
        for(int i=0;i<tiles.size();i++)
        {
            for(int j=0;j<foundTiles.size();j++)
            {
                if(foundTiles[j].number != -1)
                {
                    for(int nb=0;nb<8;nb++)
                    {
                        string iFront;
                        for(int n=0;n<tiles[i].data.size();n++)
                            iFront.push_back(tiles[i].data[n][0]);

                        string iBack;
                        for(int n=0;n<tiles[i].data.size();n++)
                            iBack.push_back(tiles[i].data[n][9]);

                        string jFront;
                        for(int n=0;n<tiles[i].data.size();n++)
                            jFront.push_back(foundTiles[j].data[n][0]);

                        string jBack;
                        for(int n=0;n<tiles[i].data.size();n++)
                            jBack.push_back(foundTiles[j].data[n][9]);

  
                        if(tiles[i].data[0] ==foundTiles[j].data[9])
                        {
                            Tile tmp;
                            tmp.data= tiles[i].data;
                            tmp.number=tiles[i].number;
                            tmp.PosX=foundTiles[j].PosX;
                            tmp.PosY=foundTiles[j].PosY+1;
                            foundTiles.push_back(tmp);
                            tiles.erase(tiles.begin()+i);
                            goto next;
                        } 
                        else if(tiles[i].data[9] ==foundTiles[j].data[0] )
                        {
                            Tile tmp;
                            tmp.data= tiles[i].data;
                            tmp.number=tiles[i].number;
                            tmp.PosX=foundTiles[j].PosX;
                            tmp.PosY=foundTiles[j].PosY-1;
                            foundTiles.push_back(tmp);
                            tiles.erase(tiles.begin()+i);
                            goto next;
                        }
                        else if(iFront == jBack)
                        {
                            Tile tmp;
                            tmp.data= tiles[i].data;
                            tmp.number=tiles[i].number;
                            tmp.PosX=foundTiles[j].PosX+1;
                            tmp.PosY=foundTiles[j].PosY;
                            foundTiles.push_back(tmp);                                
                            tiles.erase(tiles.begin()+i);
                            goto next;
                        } 
                        else if(iBack == jFront)
                        {
                            Tile tmp;
                            tmp.data= tiles[i].data;
                            tmp.number=tiles[i].number;
                            tmp.PosX=foundTiles[j].PosX-1;
                            tmp.PosY=foundTiles[j].PosY;
                            foundTiles.push_back(tmp);
                            tiles.erase(tiles.begin()+i);
                            goto next;
                        }
                        if(nb ==3)
                            flipTileHorizontal(tiles[i]);
                        else
                            rotateTile(tiles[i]);
                    }
                }              
            }
        }
        next:
       int nb=1;
       nb++;
    }

}

int main()
{
    std::ifstream inFile("day20.txt");
    if (inFile.is_open())
    {        
        vector<Tile> tiles;     
        vector<Tile> foundTiles;

        std::string data;    
        int currentTile=0;
        while (std::getline(inFile, data))
        { 
            if(data.size() != 0 )
            {
                  size_t pos =   data.find ("Tile");
                  if(pos !=  string::npos)
                  {
                      Tile t;
                      t.number =stoi(data.substr(5,4));
                      tiles.push_back(t);
                  }
                  else
                  {
                      tiles[currentTile].data.push_back(data);
                  }
                  
             }      
             else
             {
                 currentTile++;
             }
        }
        inFile.close();
        
        foundTiles.push_back(tiles.back());
        foundTiles[0].PosX=0;
        foundTiles[0].PosY=0;
        tiles.pop_back();
        orderTiles(tiles, foundTiles);

        int minX=50;
        int minY=50;
        int maxX=-50;
        int maxY=-50;
        for(int i=0;i<foundTiles.size();i++)
        {
            if(foundTiles[i].PosX > maxX)
                maxX=foundTiles[i].PosX;
            if(foundTiles[i].PosX < minX)
                minX=foundTiles[i].PosX;
            if(foundTiles[i].PosY > maxY)
                maxY=foundTiles[i].PosY;
            if(foundTiles[i].PosY < minY)
                minY=foundTiles[i].PosY;
        }

         for(int i=0;i<foundTiles.size();i++)
        {
            foundTiles[i].data.erase(foundTiles[i].data.begin());
            foundTiles[i].data.erase(foundTiles[i].data.begin()+8);
           
            for(int j=0;j<foundTiles[i].data.size();j++)
            {
                foundTiles[i].data[j].erase(0,1);
                foundTiles[i].data[j].erase(8);
            }
        }
        vector<string> bigMap(96);  
        int row=0; 
        int found=0; 
        int troublingWaters=0;
            for(int j=minY;j<=maxY;j++)
            {
                for(int i=minX;i<=maxX;i++)
                {
                    for(int k=0;k<foundTiles.size();k++)
                    {
                        if(foundTiles[k].PosX ==i && foundTiles[k].PosY ==j)
                        {
                            for(int g=0;g<foundTiles[k].data.size();g++)
                            {
                                string tmp =foundTiles[k].data[g];
                                bigMap[g+(row*8)].append(tmp);
                                troublingWaters+= std::count(tmp.begin(), tmp.end(), '#');
                            }
                            found++;
                            if(found ==12)
                            {
                                found=0;
                                row++;
                            }
                                
                        }
                    }
                }   
            }
       

    int numberofMonsters=0;
    int nb=0;
    while (numberofMonsters==0)
    {
        for(int j=0;j< bigMap.size()-2;j++)
        {
            for(int i=18;i< bigMap[0].size();i++)
            {
                if(bigMap[j][i]=='#')
                {
                    if( bigMap[j+1][i-18] == '#' && 
                        bigMap[j+1][i-13] == '#' && 
                        bigMap[j+1][i-12] == '#' && 
                        bigMap[j+1][i-7] == '#' && 
                        bigMap[j+1][i-6] == '#' && 
                        bigMap[j+1][i-1] == '#' &&
                        bigMap[j+2][i-17] == '#' &&
                        bigMap[j+2][i-14] == '#' &&
                        bigMap[j+2][i-11] == '#' &&
                        bigMap[j+2][i-8] == '#' &&
                        bigMap[j+2][i-5] == '#' && 
                        bigMap[j+2][i-2] == '#')
                    {
                        numberofMonsters++;
                    }
                }
            }
        }
        
        if(nb ==3 && numberofMonsters ==0)
        {
            for(int i=0;i<bigMap.size();i++)
            {
                std::reverse(bigMap[i].begin(),bigMap[i].end());
            }
        }
        else if(numberofMonsters ==0)
        {
        vector<string> tmp = bigMap;
        for (int i = 0; i <bigMap.size(); ++i)
            for (int j = 0; j <bigMap.size(); ++j)    
                tmp[bigMap.size()-1-j][i] = bigMap[i][j];

            bigMap.swap(tmp);
        }
        nb++;
    }

    std::cout<<troublingWaters-(numberofMonsters*15);
    } 
return 0;
}