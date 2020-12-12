#include <bits/stdc++.h>
using namespace std;

int main()
{
  std::ifstream inFile("day11.txt");
  if (inFile.is_open())
  {
    std::vector<string> seats;
    std::string data;
    while (std::getline(inFile, data))
    { 
      data.insert(0,".");
      data.insert(data.size(),".");

      seats.push_back(data);
    }
    inFile.close();

    std::string Emptyrow;

    for(int i=0;i<seats[0].size();i++)
      Emptyrow.push_back('.');
    seats.insert(seats.begin(),Emptyrow);
    seats.insert(seats.end(),Emptyrow);

    std::vector<string> seatsBuffer(seats);

    int globalCounter=1;
    while(true)
    {
        for(int i=1;i<seats.size()-1;i++)
        {
          for(int j=1;j<seats[i].size()-1;j++)
          {
            int numberOcc=0;

            if(seats[i-1][j-1] == '#')
              numberOcc++;

              if(seats[i-1][j] == '#')
              numberOcc++;

              if(seats[i-1][j+1] == '#')
              numberOcc++;

              if(seats[i][j-1] == '#')
              numberOcc++;

              if(seats[i][j+1] == '#')
              numberOcc++;

              if(seats[i+1][j-1] == '#')
              numberOcc++;

              if(seats[i+1][j] == '#')
              numberOcc++;

              if(seats[i+1][j+1] == '#')
              numberOcc++;

              if(seats[i][j] == 'L' && numberOcc ==0)
                seatsBuffer[i][j] = '#';
              else if(seats[i][j] == '#' && numberOcc >=4)
                seatsBuffer[i][j] = 'L';
          }
        }

      seats = seatsBuffer;
      int counter=0;
      for(int i=0;i<seats.size();i++)
        counter += std::count(seats[i].begin(),seats[i].end(), '#');

      if(counter== globalCounter)
        break;
      else
        globalCounter=counter;  
    }
    std::cout<<globalCounter<<std::endl;
  } 
  return 0;
}