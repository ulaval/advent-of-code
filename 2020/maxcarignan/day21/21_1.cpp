#include "../utils.h" 
#include <regex>
using namespace std;

int main()
{
    std::ifstream inFile("day21.txt");
    if (inFile.is_open())
    {        
        std::string data;    

        std::map<string, vector<string> > allSol;
        vector<string> allIngredients;
        while (std::getline(inFile, data))
        { 
            std::vector<std::string> Complete = Utils::split(data,'(');
            std::vector<std::string> ingredients = Utils::split(Complete[0],' ');

            for(int i=0;i<ingredients.size();i++)
            {
                allIngredients.push_back(ingredients[i]);
            }

            string roughAllergens = Complete[1];
            roughAllergens.erase(std::remove(roughAllergens.begin(), roughAllergens.end(), ' '), roughAllergens.end());
            
            std::vector<std::string> allergensTmp = Utils::split(roughAllergens,',');
            allergensTmp.front().erase(0,8);
            allergensTmp.back().erase(allergensTmp.back().size()-1,1);

            for(int i=0;i<allergensTmp.size();i++)
            {
                if(allSol[allergensTmp[i]].size() ==0)
                {
                    for(int j=0;j<ingredients.size();j++)
                    {
                        allSol[allergensTmp[i]].push_back(ingredients[j]);
                    }
                }  
                else
                {
                    std::vector<std::string> tmp =allSol[allergensTmp[i]];
                    std::vector<std::string> buffer ;
                    for(int j=0;j<ingredients.size();j++)
                    {      
                        if(find (tmp.begin(), tmp.end(), ingredients[j]) != tmp.end())
                            buffer.push_back(ingredients[j]);
                    }
                    allSol[allergensTmp[i]]=buffer;
                }
            }
        }
        inFile.close();


        vector<string> badIngredients;
        for (auto const& x : allSol)
        {   
            for(int i=0;i<x.second.size();i++)
            {
                if(find (badIngredients.begin(), badIngredients.end(), x.second[i]) == badIngredients.end() )
                    badIngredients.push_back(x.second[i]);
            }
        }

        int total;
        for(int i=0;i<allIngredients.size();i++)
        {
            if(find (badIngredients.begin(), badIngredients.end(), allIngredients[i]) == badIngredients.end() )
                total++;
        }
        std::cout<<total <<endl; 
    } 
return 0;
}