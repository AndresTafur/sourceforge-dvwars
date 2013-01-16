#include "ForestGenerator.h"
#include "entity/Tree.h"

#include <stdlib.h>
#include <stdio.h>

ForestGenerator::ForestGenerator()
{

}



        std::vector<Tree*> ForestGenerator::createForest(Vector2 pos, unsigned int width, unsigned int height)
        {
            bool **grid;
            std::vector<Tree*> resTrees;

                        grid = simulateLife(width, height);
                        srand(time(NULL));

                        for(unsigned int i=0; i < width; i++ )
                            for(unsigned int j=0; j < width; j++ )
                                if(  grid[i][j] )
                                   resTrees.push_back( new Tree( (i+pos.mXcoord)*5+ rand()%20, (j+pos.mYcoord)*5+ rand()%20 ));



                        for(unsigned int i=0; i < width; i++)
                            delete grid[i];
                        delete grid;

                  return resTrees;
        }


        bool** ForestGenerator::simulateLife(unsigned int width, unsigned int height)
        {
            bool **grid;
            bool tmp[width][height];
            size_t total;
            unsigned int pX, pY;


                    srand ( time(NULL) );

                    total = rand() % 10 + 2;
                    grid  = new bool*[width];

                    for(unsigned int i=0; i < width; i++)
                          grid[i] = new bool[height];

                    for(size_t p = 0; p < width*height/8; p++ )
                    {
                            pX = rand() % width;
                            pY = rand() % height;
                            grid[ pX ][ pY ] = true;
                    }



                    for(size_t pass = 0; pass < total; pass++ )
                    {
                        for(unsigned int i=0; i < width; i++)
                            for(unsigned int j=0; j < height;j++)
                                tmp[i][j] = grid[i][j];


                        /* ACTUALIZACION DE CELULAS**/
                        for(unsigned int i=0; i < width; i++)
                            for( unsigned int j=0; j < height; j++)
                            {
                                int vec = 0;

                                for(int p=-1; p < 2; p++)
                                    if( i+p >= 0 && i+p < width)
                                for( int q=-1; q < 2; q++)
                                  if( j+q >= 0 && j+q < height)
                                  {
                                       if( p == 0 && q == 0)
                                             continue;

                                       if( grid[i+p][j+q] != 0 )
                                                vec++;
                                   }

                                    /* Nuevo estado **/
                                    if(grid[i][j] != 0)
                                    {
                                        if( !( vec > 5 || vec < 1)  )
                                            tmp[i][j] = grid[i][j];
                                    }
                                    else
                                        tmp[i][j] = vec == 3;
                            }

                            for(unsigned int i=0; i < width; i++)
                                for(unsigned int j=0; j < height; j++)
                                    grid[i][j] = tmp[i][j];

                    }

                return grid;
       }



ForestGenerator::~ForestGenerator()
{
    //dtor
}
