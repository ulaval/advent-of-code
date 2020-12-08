#include "../utils.h" 
using namespace std;

struct bag
{
    std::string name;
    std::vector<std::pair<std::string,int> > canContain;
};

int calculatebags(const std::vector<bag>&allBags, std::string&toFind)
{
    int counter=0;
    for(int i=0;i<allBags.size();++i)
    {
        if(allBags[i].name == toFind)
        {
            if(allBags[i].canContain.size()==0)
                return 0;
            else
            {
                for(int j=0;j<allBags[i].canContain.size();j++)
                {
                    int num= allBags[i].canContain[j].second;
                    counter+=num;
                    std::string bagToFind=allBags[i].canContain[j].first;
                    counter+=(num*calculatebags(allBags, bagToFind));
                }
            }           
        }       
    }
    return counter;
}


int main()
{
    std::ifstream inFile("day7.txt");
    if (inFile.is_open())
    {
       std::vector<bag> allBags;
        std::string data;
        while (std::getline(inFile, data))
        { 
            bag thisBag;
            std::string bagDelimiter=" bags contain ";
            std::size_t pos = data.find(bagDelimiter); 

            thisBag.name=data.substr (0, pos);

            std::string content = data.substr (pos+bagDelimiter.size());

            if(content.find("no other bags.")  == std::string::npos)
            {
                std::string bagListDelimiter="bag";
                  while(content.size())
                    {                        
                        std::size_t posBag = content.find(bagListDelimiter);  
                        int num= content[0]-'0';
                        std::string bagName = content.substr (2,posBag-bagListDelimiter.size());

                        std::size_t commaDelimiter = content.find_first_of(",."); 
                        if(commaDelimiter == content.size()-1)
                            content.clear();
                        else
                            content=content.substr (commaDelimiter+2);
                      
                        thisBag.canContain.push_back(std::make_pair(bagName,num));
                    }          
            }
            allBags.push_back(thisBag);
        }
        inFile.close();
 
    std::string toFind= "shiny gold";
    int val =calculatebags(allBags, toFind);

    std::cout<<val<<endl;
    } 
    return 0;
}