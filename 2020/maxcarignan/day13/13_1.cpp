#include "../utils.h" 
using namespace std;

int main()
{
  int start = 0;
  std::vector<std::string> buses;
  std::vector<int> busesInt;
  std::ifstream inFile("day13.txt");
  if (inFile.is_open())
  {
      std::string data;
      std::getline(inFile, data);
      start = stoi(data);  
      std::getline(inFile, data);
      buses =Utils::split(data,',');
      buses.erase(std::remove(buses.begin(), buses.end(), "x"), buses.end());

      for (int i=0; i< buses.size(); i++)
      {
        busesInt.push_back(stoi(buses[i]));
      }
  } 
    inFile.close();

    int shortestTime=1000;
    int answer=0;
    for(int i=0;i<busesInt.size();i++)  
     {
         int val = busesInt[i] - (start%busesInt[i]);
         if(val < shortestTime)
         {
             shortestTime = val;
             answer=busesInt[i]*val;
         }
     } 
    std::cout<<answer<<endl;
  
  return 0;
}