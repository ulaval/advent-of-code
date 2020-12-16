#include "utils.h" 
using namespace std;

int main()
{
    std::ifstream inFile("day16.txt");
    if (inFile.is_open())
    {  
        std::string data;
        int section =1;
        int total=0;
        std::vector<int>allFieldsValues;  
       
        while (std::getline(inFile, data))
        { 
            if(data.size()!=0 && section ==1)
            {
                std::vector<int> fieldValues;
                auto position = data.find_first_of ("1234567890");
                auto dash = data.find ("-", position);
                int first_number =stoi(data.substr (position, dash -position));

                auto space = data.find (" ", dash);
                int second_number =stoi(data.substr (dash+1, space-dash));

                for(int i=first_number;i<=second_number;i++)
                    allFieldsValues.push_back(i);

                position = data.find_first_of ("1234567890",space);
                dash = data.find ("-", position);
                int third_number =stoi(data.substr (position, dash -position));

                space = data.find (" ", dash);
                int fourth_number =stoi(data.substr (dash+1, space-dash));

                for(int i=third_number;i<=fourth_number;i++)
                    allFieldsValues.push_back(i);

            }
            else if(data.size()!=0 && section ==2){}
            else if(data.size()!=0 && section ==3)
            {
                if(data.find("ticket") == string::npos)
                {
                    std::vector<std::string> input=Utils::split(data,',');
                  
                    for(int i=0;i<input.size();i++)
                    {
                        auto it = std::find (allFieldsValues.begin(), allFieldsValues.end(), stoi(input[i]));
                        if (it == allFieldsValues.end())
                        {
                            total+=stoi(input[i]);
                        }                                      
                    }
                }
            }
            else
            {
                section++;
            }     
        }
        inFile.close();
        std::cout<<total <<endl;    
    } 
return 0;
}