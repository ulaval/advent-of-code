#include "utils.h" 
using namespace std;

struct bag
{
    std::string name;
    std::vector<std::pair<std::string,int> > canContain;
};

void findbags(const std::vector<bag>&allBags, std::vector<string>&allPossibleBags, std::string toFind)
{
    for(int i=0;i<allBags.size();++i)
    {
        for(int j=0;j<allBags[i].canContain.size();j++ )
        {
            if(allBags[i].canContain[j].first == toFind)
            {
                std::string bagToFind=allBags[i].name;
                std::vector<string>::iterator it = std::find(allPossibleBags.begin(),allPossibleBags.end(), bagToFind);
                if(it == allPossibleBags.end())
                {
                    allPossibleBags.push_back(bagToFind);
                    findbags(allBags, allPossibleBags, bagToFind);  
                }                               
            }
        }      
    }
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
 
    std::vector<string> allPossibleBags;
    std::string toFind= "shiny gold";

    findbags(allBags, allPossibleBags, toFind);
    std::cout<<allPossibleBags.size()<<endl;

    } 
  return 0;
}