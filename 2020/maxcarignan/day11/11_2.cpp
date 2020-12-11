#include <bits/stdc++.h>
using namespace std;

int main()
{
    std::ifstream inFile("day11.txt");
    if (inFile.is_open())
    {
        std::vector<string> seats;
        std::string data;
        while (std::getline(inFile, data))
        { 
            data.insert(0,".");
            data.insert(data.size(),".");

            seats.push_back(data);
        }
        inFile.close();

        std::string Emptyrow;

        for(int i=0;i<seats[0].size();i++)
        Emptyrow.push_back('.');
        seats.insert(seats.begin(),Emptyrow);
        seats.insert(seats.end(),Emptyrow);

        std::vector<string> seatsBuffer(seats);

        int globalCounter=1;
        while(true)
        {
            for(int i=1;i<seats.size()-1;i++)
            {
                for(int j=1;j<seats[i].size()-1;j++)
                {
                    if(seats[i][j] != '.')
                    {
                        int numberOcc=0;

                        //upper left
                        int minUL=min(i-1,j-1);
                        for(int UL =1; UL<=minUL;UL++)
                        {
                            if(seats[i-UL][j-UL] == '#' )
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i-UL][j-UL] == 'L')
                                break;
                        }

                        //upper

                        for(int UP =1; UP<=i-1;UP++)
                        {
                            if(seats[i-UP][j] == '#' )
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i-UP][j] == 'L')
                                break;
                        }

                        // upper right
                        int minUR=min(i-1,int(seats[i].size()-j));
                        for(int UR =1; UR<=minUR;UR++)
                        {
                            if(seats[i-UR][j+UR] == '#' )
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i-UR][j+UR] == 'L')
                                break;
                        }

                        //left
                        for(int LE =1; LE<=j-1;LE++)
                        {
                            if(seats[i][j-LE] == '#' )
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i][j-LE] == 'L')
                                break;
                        }

                        //right
                        for(int RI =1; RI<=seats[i].size()-j;RI++)
                        {
                            if(seats[i][j+RI] == '#')
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i][j+RI] == 'L')
                                break;
                        }
                
                        //lower left
                        int minLL=min(int(seats.size()-i),j-1);
                        for(int LL =1; LL<=minLL;LL++)
                        {
                            if(seats[i+LL][j-LL] == '#')
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i+LL][j-LL] == 'L')
                                break;
                        }

                        //lower
                        for(int LO =1; LO<=seats.size()-i;LO++)
                        {
                            if(seats[i+LO][j] == '#')
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i+LO][j] == 'L')
                                break;
                        }

                        //lower right
                        int minLR=min(int(seats.size()-i),int(seats[i].size()-j));
                        for(int LR =1; LR<=minLR;LR++)
                        {
                            if(seats[i+LR][j+LR] == '#')
                            {
                                numberOcc++;
                                break;
                            }else if(seats[i+LR][j+LR] == 'L')
                                break;
                        }

                        if(seats[i][j] == 'L' && numberOcc ==0)
                            seatsBuffer[i][j] = '#';
                        else if(seats[i][j] == '#' && numberOcc >=5)
                            seatsBuffer[i][j] = 'L';
                    }
                }
            }
            seats = seatsBuffer;

            int counter=0;
            for(int i=0;i<seats.size();i++)
                counter += std::count(seats[i].begin(),seats[i].end(), '#');

            if(counter== globalCounter)
                break;
            else
                globalCounter=counter;
        }
        std::cout<<globalCounter<<std::endl;
    } 
    return 0;
}