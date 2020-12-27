#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::ifstream inFile("day25.txt");
    if (inFile.is_open())
    {        
        long cardKey;    
        long doorKey;
        std::string data;

        std::getline(inFile, data);
        cardKey = stol(data);
        std::getline(inFile, data);
        doorKey = stol(data);
        inFile.close();

        long loopSize=1;
        long value=1;
        for (long i=0; i<20201227;i++) 
        {
            if (value == cardKey) {
                loopSize=i;
                break;
            }
            else
                value = (value * 7) % 20201227; 
        }

        long encryptionKeyDoor=1;
        for(long i=0;i<loopSize;i++)
        {
            encryptionKeyDoor = (encryptionKeyDoor * doorKey) % 20201227; 
        }

        std::cout<<encryptionKeyDoor<<endl;   

    } 
return 0;
}