#include <bits/stdc++.h>
using namespace std;

int findPosition(double min, double max, std::string data, char lowerHalf)
{
      int position=0;
        for(int i=0;i< data.size();i++)
        {
            if(data[i]==lowerHalf)
            {
                max= floor((max-min)/2)+min;
            }
            else
            {
                min=ceil((max-min)/2)+min;
            }

            if(i == data.size()-1 && max<=min)
                position=max;
            else  if(i == data.size()-1 && min<max)
                position=min;
        }
    return position;
}

int main()
{
    std::ifstream inFile("day5.txt");
    if (inFile.is_open())
    {
        int highestSeat=0;
        std::string data;
        while (std::getline(inFile, data))
        { 
            int row= findPosition(0, 127, data.substr(0,7),'F');
            int seat= findPosition(0, 7, data.substr(7),'L');

            if(row*8+seat>highestSeat)
                highestSeat =row*8+seat;
        }
        inFile.close();

        std::cout<<highestSeat<<endl;
    } 
  return 0;
}