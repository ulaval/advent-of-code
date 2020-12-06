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
        std::vector<int> takenSeats;
        std::vector<int> availableSeats;
        std::string data;
        while (std::getline(inFile, data))
        { 
            int row= findPosition(0, 127, data.substr(0,7),'F');
            int seat= findPosition(0, 7, data.substr(7),'L');

            takenSeats.push_back(row*8+seat);
        }
        inFile.close();

        std::vector<int>::iterator it;
        for(int i=1;i<=911;i++)
        {
            it = find (takenSeats.begin(), takenSeats.end(), i);
            if (it == takenSeats.end())
            {
                availableSeats.push_back(i);
            }
        }

        for(int j=0;j<availableSeats.size();j++)
            std::cout<<availableSeats[j]<<endl;
    } 
  return 0;
}