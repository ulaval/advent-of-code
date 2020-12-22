#include "../utils.h" 
using namespace std;

long long evaluateExpression(std::string equation)
{
    std::string tmpEquation = "";
    for (int i = 0; i < equation.length(); i++)
    {
        if (equation[i] == '(')
        {
            int nbParenthesis = 1;
            std::string insideEquation;
            for(int j=i+1;j<equation.length();j++)
            {
                if (equation[j] == '(')
                {
                    nbParenthesis++;
                } else if (equation[j] == ')')
                {
                    nbParenthesis--;
                    if (nbParenthesis == 0)
                    {
                        i=j;
                        break;
                    }
                }
                insideEquation += equation[j];
            }
            tmpEquation += std::to_string(evaluateExpression(insideEquation));
        }
        else
        tmpEquation += equation[i];
    }

    for (int i = tmpEquation.length()-1; i >=0; i--)
    {
        if (tmpEquation[i] == '+')
        {
            return evaluateExpression(tmpEquation.substr(i+1)) + evaluateExpression(tmpEquation.substr(0, i));
        } else if (tmpEquation[i] == '*')
        {
            return evaluateExpression(tmpEquation.substr(i+1)) * evaluateExpression(tmpEquation.substr(0, i));
        }
    }
    return stoll(tmpEquation);
}

int main()
{
    std::ifstream inFile("day18.txt");
    if (inFile.is_open())
    {        
        vector<string> allEquations;
        std::string data;    
        while (std::getline(inFile, data))
        { 
            data.erase(std::remove(data.begin(), data.end(), ' '), data.end());
            allEquations.push_back(data); 
        }
        inFile.close();

        long long total;
        for(int i=0;i<allEquations.size();i++)
            total+=evaluateExpression(allEquations[i]);
        std::cout<<total <<endl;   
    } 
return 0;
}