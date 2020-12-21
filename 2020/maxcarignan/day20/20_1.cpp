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

        long long total=1;
        for(int i=0;i<foundTiles.size();i++)
        {
            if((foundTiles[i].PosX == maxX && foundTiles[i].PosY == maxY) || (foundTiles[i].PosX == maxX && foundTiles[i].PosY == minY) || (foundTiles[i].PosX == minX && foundTiles[i].PosY == maxY) || (foundTiles[i].PosX == minX && foundTiles[i].PosY == minY))
            total *= foundTiles[i].number;
        }
        std::cout<<total<<endl; 
    } 
return 0;
}