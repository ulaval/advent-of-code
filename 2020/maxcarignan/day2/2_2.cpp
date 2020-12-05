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
      std::vector<std::string> positionsToCheck =Utils::split(splitInfos[0],'-');

      int numOccurences=0;
      for(int i=0;i<positionsToCheck.size();i++) 
        if (splitInfos[2][stoi(positionsToCheck[i])-1] == splitInfos[1][0])
            numOccurences++;
      
      if( numOccurences == 1)
        correctPasswords++;                           
    }
    inFile.close();
    std::cout<<correctPasswords<<endl;
  }
  return 0;
}