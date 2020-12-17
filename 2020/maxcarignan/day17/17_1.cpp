#include "../utils.h" 
using namespace std;

int main()
{
    std::ifstream inFile("day17.txt");
    if (inFile.is_open())
    {        
        int spaceSize=100;
        vector<int> cubesX(spaceSize);
        vector<vector<int> >   cubesXY(spaceSize,cubesX);
        vector<vector<vector<int> > > cubesXYZ(spaceSize, cubesXY);
        
        std::string data;    
        int row=0;
        while (std::getline(inFile, data))
        { 
            for(int i=0;i<data.size();i++)
            {
                int val=0;
                if(data[i]=='#')
                    val=1;
                cubesXYZ[spaceSize/2+i][spaceSize/2+row][spaceSize/2] = val;
            }
                row++;
        }
        inFile.close();

        int numRounds=6;
        int total=0;
        for(int rounds=0;rounds<numRounds;rounds++)
        {
            vector<int> tmpCubesX(spaceSize);
            vector<vector<int> >   tmpCubesXY(spaceSize,tmpCubesX);
            vector<vector<vector<int> > > tmpCubesXYZ(spaceSize, tmpCubesXY);
            total=0;
            for(int currentX=0;currentX<spaceSize;currentX++)
            {
                for(int currentY=0;currentY<spaceSize;currentY++)
                {
                    for(int currentZ=0;currentZ<spaceSize;currentZ++)
                    {
                        int numAdjacents=0;
                        for(int adjX=-1;adjX<=1; adjX++)
                        {
                            for(int adjY=-1;adjY<=1; adjY++)
                            {
                                for(int adjZ=-1;adjZ<=1; adjZ++)
                                {
                                    if((adjX==0 && adjY==0 && adjZ==0 )|| currentX+adjX<0 || currentX+adjX>=spaceSize || currentY+adjY<0 || currentY+adjY>=spaceSize || currentZ+adjZ<0 || currentZ+adjZ>=spaceSize){}
                                    else if(cubesXYZ[currentX+adjX][currentY+adjY][currentZ+adjZ] ==1)
                                        numAdjacents++;
                                }
                            }
                        }   
                      if((cubesXYZ[currentX][currentY][currentZ]==1 && (numAdjacents ==2 || numAdjacents ==3)) || (cubesXYZ[currentX][currentY][currentZ]==0 && numAdjacents==3))
                       { 
                           tmpCubesXYZ[currentX][currentY][currentZ]=1;
                           total++;
                        }
            
                    }
                }
            }
            cubesXYZ=tmpCubesXYZ;
        }
        std::cout<<total <<endl;   
    } 
return 0;
}