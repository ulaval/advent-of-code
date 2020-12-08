#include "../utils.h" 
using namespace std;

int runCode(std::vector<std::pair<std::string, std::string> >&instructions)
{
    int accumulator=0;
    std::vector<int> usedOp;
    bool exitLoop=false;
    int  currentOP=0;

    while(!exitLoop)
    {
        if(instructions[currentOP].first == "nop")
        {
            if (find(usedOp.begin(), usedOp.end(), currentOP) != usedOp.end())
              exitLoop=true;
            else
            {
              usedOp.push_back(currentOP);
              currentOP++;
            }       
        }
        else if(instructions[currentOP].first == "acc")
        { 
            if (find(usedOp.begin(), usedOp.end(), currentOP) != usedOp.end())
              exitLoop=true;
            else
            {
              usedOp.push_back(currentOP);
              
              if(instructions[currentOP].second[0] == '+')
                  accumulator = accumulator+ stoi(instructions[currentOP].second.substr(1));
              else
                  accumulator = accumulator- stoi(instructions[currentOP].second.substr(1));
              currentOP++;             
            }    
        }
        else if(instructions[currentOP].first == "jmp")
        {
            if (find(usedOp.begin(), usedOp.end(), currentOP) != usedOp.end())
              exitLoop=true;
            else
            {
              usedOp.push_back(currentOP);

              if(instructions[currentOP].second[0] == '+')
                  currentOP = currentOP+ stoi(instructions[currentOP].second.substr(1));
              else
                  currentOP = currentOP- stoi(instructions[currentOP].second.substr(1));
            }
        }


    }

  return accumulator;
}

int main()
{
  std::vector<std::pair<std::string, std::string> > instructions;
  std::ifstream inFile("day8.txt");
  if (inFile.is_open())
  {
    std::string data;
    while (std::getline(inFile, data))
    { 
      std::vector<std::string>  separate=Utils::split(data, ' ');
      instructions.push_back(std::make_pair(separate[0],separate[1]));
    }
    inFile.close();

    std::cout<<runCode(instructions)<<std::endl;
  } 
  return 0;
}