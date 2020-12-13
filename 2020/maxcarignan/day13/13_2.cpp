#include "../utils.h"
using namespace std;

// J'ai emprunté du code pour le Chinese Reminder Theorem
// Source: https://www.geeksforgeeks.org/chinese-remainder-theorem-set-2-implementation/
long long inv(long long a, long long m) 
{ 
    long long m0 = m, t, q; 
    long long x0 = 0, x1 = 1; 
  
    if (m == 1) 
       return 0; 
  
    // Apply extended Euclid Algorithm 
    while (a > 1) 
    { 
        // q is quotient 
        q = a / m; 
  
        t = m; 
  
        // m is remainder now, process same as 
        // euclid's algo 
        m = a % m, a = t; 
  
        t = x0; 
  
        x0 = x1 - q * x0; 
  
        x1 = t; 
    } 
  
    // Make x1 positive 
    if (x1 < 0) 
       x1 += m0; 
  
    return x1; 
} 

// k is size of num[] and rem[].  Returns the smallest 
// number x such that: 
//  x % num[0] = rem[0], 
//  x % num[1] = rem[1], 
//  .................. 
//  x % num[k-2] = rem[k-1] 
// Assumption: Numbers in num[] are pairwise coprime 
// (gcd for every pair is 1) 
long long findMinX(std::vector<int>&num, std::vector<int>&rem) 
{ 
    // Compute product of all numbers 
    long long prod = 1; 
    for (int i = 0; i < num.size(); i++) 
        prod *= num[i]; 
  
    // Initialize result 
    long long result = 0; 
  
    // Apply above formula 
    for (int i = 0; i < num.size(); i++) 
    { 
        long long pp = prod / num[i]; 
        result += rem[i] * inv(pp, num[i]) * pp; 
    } 
  
    return result % prod; 
} 
 
int main()
{
    std::vector<std::string> buses;
    std::vector<int> busesInt;
    std::vector<int> remainders;
    std::ifstream inFile("day13.txt");
    if (inFile.is_open())
    {
        std::string data;
        std::getline(inFile, data);

        std::getline(inFile, data);
        buses =Utils::split(data,',');

        std::replace (buses.begin(), buses.end(), "x", "0");

        for (int i=0; i< buses.size(); i++)
        {
            if( buses[i] !="0")
            {
                int val = stoi(buses[i]);
                busesInt.push_back(val);
                remainders.push_back((val- i)%val);
            }        
        }
    } 
    inFile.close();

    std::cout << findMinX(busesInt, remainders)<<std::endl;
  return 0;
}