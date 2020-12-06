#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::vector<int>numbers;  
    std::fstream myfile("day1.txt", std::ios_base::in);
    int value = 0;

    while (myfile >> value)
    {
        numbers.push_back(value);
    } 
    myfile.close();

    int first,second,third=0;

    for(int i=0;i<numbers.size();i++)
    {
        for(int j=i+1;j<numbers.size();j++)
        {
            for(int k=j+1;k<numbers.size();k++)
            {
                if (numbers[i]+numbers[j]+numbers[k] == 2020)
                {  
                    first=numbers[i];
                    second=numbers[j];
                    third=numbers[k];
                    goto endloop;
                }
            }
        }
    }
    
endloop:
    std::cout<<first*second*third<<endl;;

  return 0;
}