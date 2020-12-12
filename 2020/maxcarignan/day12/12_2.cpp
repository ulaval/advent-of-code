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
    int waypointX=10;
    int waypointY=1;

    for(auto direction : directions)
    {
        if(direction.first== 'N')
            waypointY += direction.second;
        else if(direction.first== 'S')
            waypointY -= direction.second;
        else if(direction.first== 'E')
            waypointX+=direction.second;
        else if(direction.first== 'W')
            waypointX-=direction.second;
        else if(direction.first== 'L' || direction.first== 'R')
        {
            int tmpx= waypointX;
            int tmpy= waypointY;

            int modifierL = (direction.first== 'L' ) ? -1 : 1;
            int modifierR = (direction.first== 'R' ) ? -1 : 1;

            if(direction.second == 90)
            {                
                waypointX=tmpy*modifierL;
                waypointY=tmpx*modifierR;
            }               
            else if(direction.second == 180)
            {
                waypointX=-tmpx;
                waypointY=-tmpy;
            }
                
            else if(direction.second == 270)
            {
                waypointX=tmpy*modifierR;
                waypointY=tmpx*modifierL;
            }  
        }
        else if(direction.first== 'F')
        {
             initX+= direction.second*waypointX;
             initY+= direction.second*waypointY;
        }
    }
    std::cout<<abs(initX)+abs(initY)<<endl;
  } 
  return 0;
}