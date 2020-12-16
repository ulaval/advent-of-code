#include "../utils.h" 
using namespace std;

int main()
{
    std::ifstream inFile("day15.txt");
    if (inFile.is_open())
    {  
        int rounds = 30000000;
        std::string data;
        std::vector<int> values(rounds, -1);
        int i=0;
        int spokenNumber=0;
        while (std::getline(inFile, data))
        { 
            std::vector<string> input=Utils::split(data,',');
            for(i=0;i<input.size()-1;i++)
                values[stoi(input[i])]=i+1;
            spokenNumber = stoi(input.back());
            i++;
        }
        inFile.close();
            
        for(int j=i;j<rounds;j++)
        {
            if(values[spokenNumber]==-1)
            {
                values[spokenNumber]=j;
                spokenNumber=0;
            }else {
                int tmp= spokenNumber;
                spokenNumber = j- values[spokenNumber];
                values[tmp]=j;
            }
        }
       values.clear();
    std::cout<<spokenNumber<<endl; 
    } 
return 0;
}