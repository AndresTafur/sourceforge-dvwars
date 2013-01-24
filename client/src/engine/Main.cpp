#include "Main.h"


int main(int argc, char **argv)
{
    MainApplication app;

    try
    {
        app.startApplication();
        fprintf(stderr,"All components released, expecting libboost exit");
    }
    catch( Ogre::Exception& e )
    {
            std::cerr << "An exception has occured: " << e.getFullDescription();
    }
    return 0;
}
