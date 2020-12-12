#include <bits/stdc++.h>
using namespace std;

int main()
{
  std::ifstream inFile("day12.txt");
  if (inFile.is_open())
  {
    std::vector<std::pair<char,int> > directions;

    std::string data;
    while (std::getline(inFile, data))
    { 
        directions.push_back(std::pair<char,int>(data[0],stoi(data.substr (1))));
    }
    inFile.close();

    int initX=0;
    int initY=0;
    char map[4] = {'E', 'S', 'W', 'N'};

    char orientation='E';

    for(auto direction : directions)
    {
        if(direction.first== 'N')
            initY += direction.second;
        else if(direction.first== 'S')
            initY -= direction.second;
        else if(direction.first== 'E')
            initX += direction.second;
        else if(direction.first== 'W')
            initX -= direction.second;
        else if(direction.first== 'L' || direction.first== 'R')
        {
            int pos = std::distance(map, std::find(map, map + 4, orientation));
            pos = (direction.first== 'L' ) ? pos-direction.second/90 : pos+direction.second/90;
         
            if(pos <0)
                orientation = map[4+pos];
            else if(pos >3)
                orientation = map[pos-4];    
            else
                orientation = map[pos];         
        }
        else if(direction.first== 'F')
        {
            if(orientation == 'E')
                initX+=direction.second ;
            else if(orientation == 'W')
                initX-=direction.second ;
            else if(orientation == 'N')
                initY+=direction.second ;
            else if(orientation == 'S')
                initY-=direction.second ;
        }
    }

    std::cout<<abs(initX)+abs(initY)<<endl;
  } 
  return 0;
}