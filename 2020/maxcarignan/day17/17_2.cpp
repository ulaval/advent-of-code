#include "../utils.h" 
using namespace std;

int main()
{
    std::ifstream inFile("day17.txt");
    if (inFile.is_open())
    {      
        int spaceSize=50;
        vector<int> cubesX(spaceSize);
        vector<vector<int> >   cubesXY(spaceSize,cubesX);
        vector<vector<vector<int> > > cubesXYZ(spaceSize, cubesXY);
        vector<vector<vector<vector<int> > > > cubesXYZW(spaceSize, cubesXYZ);
        
        std::string data;        
        int row=0;
        while (std::getline(inFile, data))
        { 
            for(int i=0;i<data.size();i++)
            {
                int val=0;
                if(data[i]=='#')
                    val=1;
                cubesXYZW[spaceSize/2+i][spaceSize/2+row][spaceSize/2][spaceSize/2] = val;
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
            vector<vector<vector<vector<int> > > > tmpCubesXYZW(spaceSize, tmpCubesXYZ);
            total=0;
            for(int currentX=0;currentX<spaceSize;currentX++)
            {
                for(int currentY=0;currentY<spaceSize;currentY++)
                {
                    for(int currentZ=0;currentZ<spaceSize;currentZ++)
                    {
                        for(int currentW=0;currentW<spaceSize;currentW++)
                        {
                            int numAdjacents=0;
                            for(int adjX=-1;adjX<=1; adjX++)
                            {
                                for(int adjY=-1;adjY<=1; adjY++)
                                {
                                    for(int adjZ=-1;adjZ<=1; adjZ++)
                                    {
                                        for(int adjW=-1;adjW<=1; adjW++)
                                        {
                                            if((adjX==0 && adjY==0 && adjZ==0 && adjW==0 )|| currentX+adjX<0 || currentX+adjX>=spaceSize || currentY+adjY<0 || currentY+adjY>=spaceSize || currentZ+adjZ<0 || currentZ+adjZ>=spaceSize || currentW+adjW<0 || currentW+adjW>=spaceSize){}
                                            else if(cubesXYZW[currentX+adjX][currentY+adjY][currentZ+adjZ][currentW+adjW] ==1)
                                                numAdjacents++;
                                        }    
                                    }
                                }
                            }   
                            if((cubesXYZW[currentX][currentY][currentZ][currentW]==1 && (numAdjacents ==2 || numAdjacents ==3)) || (cubesXYZW[currentX][currentY][currentZ][currentW]==0 && numAdjacents==3))
                            { 
                                tmpCubesXYZW[currentX][currentY][currentZ][currentW]=1;
                                total++;
                            }
                        }
                    }
                }
            }
            cubesXYZW=tmpCubesXYZW;
        }
        std::cout<<total <<endl;   
    } 
return 0;
}