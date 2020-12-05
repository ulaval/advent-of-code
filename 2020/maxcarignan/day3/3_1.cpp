#include "../utils.h" 
using namespace std;

int main()
{
  std::ifstream inFile("day3.txt");
  if (inFile.is_open())
  {  
    std::vector<std::string> terrainLines;
    std::string terrainLine;
    while (std::getline(inFile, terrainLine))
    {  
        terrainLines.push_back(terrainLine);               
    }
    inFile.close();

    int currentPos=0;
    int numTrees =0;

    for(int i=1;i<terrainLines.size();i++)
    {
        if(currentPos+3>=terrainLines[0].size())
            currentPos= currentPos+3-terrainLines[0].size();
        else
            currentPos+=3;

        if(terrainLines[i][currentPos]=='#')
            numTrees++;
    }
    std::cout<<numTrees<<endl;
  }
  return 0;
}