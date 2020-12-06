#include "../utils.h" 
using namespace std;

bool isPassportValid(const std::vector<std::string>&allFields)
{
    if(allFields.size()==8 ||  (allFields.size()==7 && std::count(allFields.begin(), allFields.end(), "cid")==0))
        return true;
    else
        return false;
}

int main()
{
  std::ifstream inFile("day4.txt");
  if (inFile.is_open())
  {
    std::string data;
    int counter=0;
    std::vector<std::vector<std::string> > allPassports;
    std::vector<std::string> allFields;

    while (std::getline(inFile, data))
    {  
        if(data.size()!=0)
        {
            std::vector<std::string> splitInfos =Utils::split(data,' ');

            for(int i=0;i<splitInfos.size();i++)
            {
                std::string field =Utils::split(splitInfos[i],':')[0];
                allFields.push_back(field);
            }
        }
        else
        {
            allPassports.push_back(allFields);
            allFields.clear();
        }                      
    }
    inFile.close();

    allPassports.push_back(allFields);
    allFields.clear();

    for(int i=0;i<allPassports.size();i++)
        if (isPassportValid(allPassports[i]))
            counter++;

    std::cout<<counter<<endl;

  } 
  return 0;
}