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
    int rightJump=1;
    int downJump=2;
    
    for(int i=downJump;i<terrainLines.size();i=i+downJump)
    {
        if(currentPos+rightJump>=terrainLines[0].size())
            currentPos= currentPos+rightJump-terrainLines[0].size();
        else
            currentPos+=rightJump;

        if(terrainLines[i][currentPos]=='#')
            numTrees++;
    }
    std::cout<<numTrees<<endl;
  }
  return 0;
}