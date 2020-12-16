#include "utils.h" 
using namespace std;

int main()
{
    std::ifstream inFile("day16.txt");
    if (inFile.is_open())
    {  
        std::string data;
        int section =1;
        long long total=1;
        std::vector<std::vector<int> > allFieldsValues;   
        std::vector<std::vector<int> > nearbyTickets;
        std::vector<int> myTicket;
       
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
                    fieldValues.push_back(i);

                position = data.find_first_of ("1234567890",space);
                dash = data.find ("-", position);
                int third_number =stoi(data.substr (position, dash -position));
                
                space = data.find (" ", dash);
                int fourth_number =stoi(data.substr (dash+1, space-dash));

                for(int i=third_number;i<=fourth_number;i++)
                    fieldValues.push_back(i);

                allFieldsValues.push_back(fieldValues);
            }
            else if(data.size()!=0 && section ==2)
            {
                 if(data.find("ticket") == string::npos)
                {
                    std::vector<std::string> input=Utils::split(data,',');
                     for(int i=0;i<input.size();i++)
                        myTicket.push_back(stoi(input[i]));
                }
            }
            else if(data.size()!=0 && section ==3)
            {
                if(data.find("ticket") == string::npos)
                {
                    std::vector<std::string> input=Utils::split(data,',');
                    std::vector<int> goodNearbyTicket;
                    bool goodTicket=true;
                    
                    for(int i=0;i<input.size();i++)
                    {
                        bool goodNumber=false;
                        for(int j=0;j<allFieldsValues.size();j++)
                        {
                                auto it = std::find (allFieldsValues[j].begin(), allFieldsValues[j].end(), stoi(input[i]));
                            if (it != allFieldsValues[j].end())
                            {
                                goodNumber=true;
                                goodNearbyTicket.push_back(stoi(input[i]));
                                break;
                            }     
                        }   
                        if(goodNumber==false)  
                        {
                            goodTicket=false;  
                            break;
                        }                                      
                    }
                    if(goodTicket)
                        nearbyTickets.push_back(goodNearbyTicket);
                }
            }
            else
            {
                section++;
            }     
        }
        inFile.close();

        std::map<int,std::vector<int> >correspondingColumns;
        for(int k=0;k<allFieldsValues.size();k++)
        {     
            for(int j=0;j<nearbyTickets[0].size();j++)
            {     
                bool columnsCorresponds=true;   
                for(int i=0;i<nearbyTickets.size();i++)
                {               
                    auto it = std::find (allFieldsValues[k].begin(), allFieldsValues[k].end(), nearbyTickets[i][j]);
                    if (it == allFieldsValues[k].end())
                    {
                        columnsCorresponds=false;
                        break;
                    }
                } 
                if(columnsCorresponds ==true)
                {
                    correspondingColumns[k].push_back(j);
                }                     
            } 
        }

        std::vector<int> attributeColumns(correspondingColumns.size(),-1);
        int index=1;
        while(index <=correspondingColumns.size())
        {
            for(int i=0;i<correspondingColumns.size();i++)
            {     
                if(correspondingColumns[i].size() ==index)
                {
                    for(int j=0;j<correspondingColumns[i].size();j++)
                    {
                        auto it = std::find (attributeColumns.begin(), attributeColumns.end(), correspondingColumns[i][j]);
                        if (it == attributeColumns.end())
                        {
                            attributeColumns[i] = correspondingColumns[i][j];
                            goto nextAttribute;
                        }
                    }
                }
            }
            nextAttribute:
            index++;
        }  

        for(int i=0;i<6;i++)
        {
            total*= myTicket[attributeColumns[i]];
        }
        std::cout<<total<<endl; 
    }   
return 0;
}