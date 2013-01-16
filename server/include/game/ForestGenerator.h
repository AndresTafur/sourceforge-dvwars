#ifndef _FORESTGENERATOR_H_
#define _FORESTGENERATOR_H_

#include <vector>
#include <entity/Tree.h>
#include <boid/Vector2.h>

class ForestGenerator
{
public:

        ForestGenerator();

        std::vector<Tree*> createForest(Vector2 pos, unsigned int width, unsigned int height );

        virtual ~ForestGenerator();

private:

        bool** simulateLife(unsigned int width, unsigned int height);

private:

bool **automataGrid;
};

#endif // _FORESTGENERATOR_H_
