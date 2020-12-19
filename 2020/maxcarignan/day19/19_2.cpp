#include "../utils.h" 
#include <regex>
using namespace std;

std::string generateRegex(int rule, std::map<int, std::vector<std::string> >& rules)
{
    if(rule == 8)
        return '('+ generateRegex(42, rules) +"+)";
    else if (rule == 11)
    {
         return '(' + generateRegex(42, rules) + generateRegex(31, rules) + '|'
                    + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(31, rules) + generateRegex(31, rules) + '|'
                    + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(31, rules) + generateRegex(31, rules) + generateRegex(31, rules) + '|'
                    + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(31, rules) + generateRegex(31, rules) + generateRegex(31, rules) + generateRegex(31, rules) + '|'
                    + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(42, rules) + generateRegex(31, rules) + generateRegex(31, rules) + generateRegex(31, rules) + generateRegex(31, rules) + generateRegex(31, rules) + ')';
	}
    
    std::string regexPart;
    for(int i=0;i< rules[rule].size();i++)
    {
        std::string currentRule = rules[rule][i];
        size_t position = currentRule.find_first_of ("1234567890");
        if(currentRule != "|" && position != std::string::npos)
            regexPart += generateRegex(std::stoi(currentRule), rules);
        else
            regexPart += currentRule;        
    }
    return '('+ regexPart +')';
}

int main()
{
    std::ifstream inFile("day19.txt");
    if (inFile.is_open())
    {        
        std::map<int,std::vector<std::string> > rules;
        std::string data;    
        std::vector<std::string> toTest;
        int sol=0;
        while (std::getline(inFile, data))
        { 
            if(data.size() != 0 && sol==0)
            {
                size_t pos = data.find (':');
                int  ruleNumber=stoi(data.substr(0,pos)); 
                std::string ruleData = data.substr(pos+2);
                ruleData.erase(std::remove(ruleData.begin(), ruleData.end(), '\"'), ruleData.end());
                std::vector<std::string> ruleDatas = Utils::split(ruleData,' ');
                rules[ruleNumber] = ruleDatas;                                   
             }else if(data.size() != 0 && sol==1)
             {
                toTest.push_back(data);
             }
             else
             {
                 sol++;
             }
        }
        inFile.close();

        std::string regexString= generateRegex(0, rules);

        std::regex probRegex(regexString);
        int total=0;
        for(int i=0;i<toTest.size();i++)
            total+= std::regex_match(toTest[i], probRegex);
      std::cout<<total <<endl;   
    } 
return 0;
}