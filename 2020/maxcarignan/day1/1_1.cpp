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

    int first,second=0;
    for(int i=0;i<numbers.size();i++)
    {
        for(int j=i+1;j<numbers.size();j++)
        {
            if (numbers[i]+numbers[j] == 2020)
            {  
                first=numbers[i];
                second=numbers[j];
                goto endloop;
            }
        }
    }
    
endloop:
    std::cout<<first*second<<endl;;

  return 0;
}