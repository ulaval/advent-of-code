#include "../utils.h" 
using namespace std;

//https://www.geeksforgeeks.org/program-decimal-binary-conversion/?ref=lbp
string decimalToBinary(long long n) 
{ 
    //finding the binary form of the number and  
    //coneverting it to string.  
    string s = bitset<64> (n).to_string(); 
      
    //Finding the first occurance of "1" 
    //to strip off the leading zeroes. 
    const auto loc1 = s.find('1'); 
      
    if(loc1 != string::npos) 
        return s.substr(loc1); 
      
    return "0"; 
} 

// https://www.geeksforgeeks.org/program-binary-decimal-conversion/
long long binaryToDecimal(string n)
{
    string num = n;
    long long dec_value = 0;
 
    // Initializing base value to 1, i.e 2^0
    long base = 1;
 
    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
 
    return dec_value;
}

void possibleAdresses(std::vector<string>&vec,std::string mask)
{
    std::string tmpMask=mask;
    std::size_t found = tmpMask.find_last_of("X");
    if(found != string::npos)
    {
        tmpMask[found] = '0';
        possibleAdresses(vec,tmpMask);

        tmpMask[found] = '1';
        possibleAdresses(vec,tmpMask);

    }else
        vec.push_back(tmpMask);   
}

int main()
{
  std::ifstream inFile("day14.txt");
  if (inFile.is_open())
  {
    std::string mask;
    std::string data;
    std::map<long  long,long long> result;

    while (std::getline(inFile, data))
    { 
      if (data.find("mask")!=std::string::npos)
        mask =  data.substr (7);
      else
      {
            int mem=stoi(data.substr (data.find("[")+1,data.find("]")-data.find("[")-1));
            std::vector<std::string> input=Utils::split(data,' ');
            string val = decimalToBinary(mem);
            val.insert (0, 36-val.size(), '0');

            for(int k=0;k<mask.size();k++)
                if(mask[k] != '0')
                    val[k] = mask[k];

            std::vector<string> allAdresses;
            possibleAdresses(allAdresses, val);

            for(int h=0;h<allAdresses.size();h++)
                result[binaryToDecimal(allAdresses[h])]= stoll(input[2]);
      }      
    }
    inFile.close();

    long long total=0;
    for(auto elem : result)
      total +=elem.second ;

    std::cout<<total;
  } 
  return 0;
}