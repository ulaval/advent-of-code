#include "../utils.h" 
using namespace std;

bool isPassportValid(const std::map<std::string,std::string>&allFields)
{   
    bool isValid=true;
    if(allFields.size()==8 ||  (allFields.size()==7 && allFields.count("cid")==0))
    {   
        for ( std::map<std::string, std::string>::const_iterator it = allFields.begin(); it != allFields.end(); it++ )
        {
            std::string field=it->first;
            std::string fieldValue=it->second;

            if(field == "byr")
            {
                if(stoi(fieldValue)<1920 || stoi(fieldValue)>2002)
                    isValid=false;                  
            }else if(field == "iyr")
            {
                if(stoi(fieldValue)<2010 || stoi(fieldValue)>2020)
                    isValid=false;
            }else if(field == "eyr")
            {
                if(stoi(fieldValue)<2020 || stoi(fieldValue)>2030)
                    isValid=false;
            }else if(field == "hgt")
            {
                std::size_t foundCM = fieldValue.find("cm");
                std::size_t foundIN = fieldValue.find("in");
                if(foundCM == std::string::npos && foundIN == std::string::npos)
                {
                    isValid=false;
                }
                else if(foundCM != std::string::npos)
                {
                    int height= stoi(fieldValue.substr (0,foundCM));
                    if(height<150  || height>193)
                        isValid=false;
                }else
                {
                        int height= stoi(fieldValue.substr (0,foundIN));
                    if(height< 59|| height>76)
                        isValid=false;
                }
            }else if(field == "hcl")
            {
                if(fieldValue[0] != '#')
                    isValid=false;
                else
                {
                    std::string croppedFieldValue = fieldValue.substr(1);
                    if(croppedFieldValue.size()!=6)
                        isValid=false;
                    else
                    {
                        char hairColorList[]={'0','1','2','3','4','5','6','7','8','9','a','b','c','d','e','f'};   
                        for(int j=0;j<croppedFieldValue.size();j++)
                        {
                           if (std::find(std::begin(hairColorList), std::end(hairColorList), croppedFieldValue[j]) == std::end(hairColorList))
                               {
                                    isValid=false;
                                    break;
                               }
                        }
                    }                        
                }
            }else if(field == "ecl")
            {
                std::string eyeList[]={"amb", "blu", "brn", "gry", "grn", "hzl", "oth"};           

                if (std::find(std::begin(eyeList), std::end(eyeList), fieldValue) == std::end(eyeList))
                    isValid=false;
            }else if(field == "pid")
            {
                if(fieldValue.size() !=9) 
                    isValid=false;  
            }
        }
    }else
        isValid=false;
    
    return isValid;
}


int main()
{
  std::ifstream inFile("day4.txt");
  if (inFile.is_open())
  {
    std::string data;
    int counter=0;
    std::vector<std::map<std::string,std::string> > allPassports;
    std::map<std::string,std::string> allFields;

    while (std::getline(inFile, data))
    {  
        if(data.size()!=0)
        {
            std::vector<std::string> splitInfos =Utils::split(data,' ');

            for(int i=0;i<splitInfos.size();i++)
            {
                allFields[Utils::split(splitInfos[i],':')[0]] = Utils::split(splitInfos[i],':')[1];
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