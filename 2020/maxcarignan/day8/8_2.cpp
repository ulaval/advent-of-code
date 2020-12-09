#include "../utils.h" 
using namespace std;

int runCode(std::vector<std::pair<std::string, std::string> >&instructions)
{
    int accumulator=0;
    std::vector<int> usedOp;
    int currentOP=0;

    for(int i=0;i<instructions.size();i++)
    {
        if(instructions[i].first == "jmp" || instructions[i].first == "nop")
        {
            instructions[i].first = (instructions[i].first == "jmp") ? "nop" : "jmp";

            while(true)
            {
                if (find(usedOp.begin(), usedOp.end(), currentOP) != usedOp.end() || currentOP>= instructions.size())
                    break;
                else
                    usedOp.push_back(currentOP);

                if(instructions[currentOP].first == "nop")
                {
                    currentOP++;    
                }
                else if(instructions[currentOP].first == "acc")
                { 
                    int valueAcc = stoi(instructions[currentOP].second.substr(1));
                    accumulator += (instructions[currentOP].second[0] == '+') ? valueAcc  : -valueAcc;
                    currentOP++;             
                }
                else if(instructions[currentOP].first == "jmp")
                {
                    int valueJmp = stoi(instructions[currentOP].second.substr(1));
                    currentOP += (instructions[currentOP].second[0] == '+') ? valueJmp  : -valueJmp;
                }
            }

            instructions[i].first = (instructions[i].first == "jmp") ? "nop" : "jmp";            
        }
        if(currentOP>= instructions.size())
           break;

        currentOP=0;
        accumulator=0;
        usedOp.clear();
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