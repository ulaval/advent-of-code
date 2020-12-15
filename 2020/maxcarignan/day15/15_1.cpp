#include "../utils.h" 
using namespace std;

int main()
{
    std::ifstream inFile("day15.txt");
    if (inFile.is_open())
    {  
        std::string data;
        std::map<int,std::pair<int, int> > values;
        while (std::getline(inFile, data))
        { 
        std::vector<string> input=Utils::split(data,',');
        for (int i=0; i< input.size(); i++)   
            values[stoi(input[i])]= std::make_pair(i,-1);
        }
        inFile.close();
    
        int counter = 16;
        int rounds = 2020;

        for (int i=values.size();i<rounds;i++)
        {
            auto it = values.find(counter);
            if (it != values.end()) 
            {
                int index= it->second.second;
                int newValue=0;
                if(index>= 0)
                    newValue=it->second.first-it->second.second;

                it= values.find(newValue);
            
                if(it==values.end())
                    values[newValue] = std::make_pair(i,-1);          
                else {
                    values[newValue].second = values[newValue].first;
                    values[newValue].first=i;
                }
                counter = newValue;
            }
        }
    std::cout<<counter<<endl; 
    } 
return 0;
}