#include "SquadBuilder.h"

unsigned int SquadBuilder::mSquadId = 2;

SquadBuilder::SquadBuilder()
{

}


    Squad* SquadBuilder::createSquad(std::string type)
    {
       ConfigReader  cfgReader;
       unsigned int  speed, units, time, cost;
       std::string   mesh, exp;
       Squad        *retSquad = NULL;

                try
                {
                        cfgReader.openFile("GameObjects.xml");
                        type  = "/descendant::squad[@name='"+type;

                        exp   = type+"']/child::property[@name='speed']";
                        speed = atoi(cfgReader.getAttribute(exp).c_str());

                        exp   = type+"']/child::property[@name='units']";
                        units = atoi(cfgReader.getAttribute(exp).c_str());

                        exp   = type+"']/child::property[@name='buildTime']";
                        time  = atoi(cfgReader.getAttribute(exp).c_str());

                        exp   = type+"']/child::property[@name='cost']";
                        cost  = atoi(cfgReader.getAttribute(exp).c_str());

                        exp   = type+"']/child::property[@name='mesh']";
                        mesh  = cfgReader.getAttribute(exp);


                        retSquad = new Squad(units, speed, mSquadId++);
                        retSquad->setMesh( mesh );
                        retSquad->setTime(time);
                        retSquad->setCost( (cost==0)?1:cost );

                }
                catch( std::string ex )
                {
                    fprintf(stderr,"Error: %s\n", ex.c_str());
                }

        return retSquad;
    }



SquadBuilder::~SquadBuilder()
{
    //dtor
}
