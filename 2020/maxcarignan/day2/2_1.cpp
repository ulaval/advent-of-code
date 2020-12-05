#include "../utils.h" 
using namespace std;

int main()
{ 
  std::ifstream inFile("day2.txt");
  if (inFile.is_open())
  {
    int correctPasswords=0;
    std::string password;
    while (std::getline(inFile, password))
    {  
          std::vector<std::string> splitInfos =Utils::split(password,' ');
          
          size_t minOccurences = stoi(Utils::split(splitInfos[0],'-')[0]);
          size_t maxOccurences = stoi(Utils::split(splitInfos[0],'-')[1]);
          size_t numOccurences = std::count(splitInfos[2].begin(), splitInfos[2].end(), splitInfos[1][0]);
        
        if(numOccurences>= minOccurences && numOccurences <= maxOccurences)
          correctPasswords++;                            
    }
    inFile.close();
    std::cout<<correctPasswords<<endl;
  }
  return 0;
}