#include "ConfigReader.h"


//TODO: VOlver esto un arbol o XPATH?? no lo sabemos
ConfigReader::ConfigReader()
{
        mDoc = NULL;
}

ConfigReader::ConfigReader(std::string configFile)
{
        mDoc = NULL;
        openFile(configFile);
}



        void ConfigReader::openFile(std::string configFile)
        {
            if(  NULL != mDoc )
            {
                xmlFreeDoc(mDoc);
                mDoc = NULL;
            }

            mFile = configFile;
            mDoc  = xmlParseFile(mFile.c_str());

            if( NULL == mDoc )
                throw std::string("Failed to open file: ")+mFile;
        }


        std::vector<std::string> ConfigReader::getAttributes(std::string exp)
        {
          std::vector<std::string> retVal;
          xmlXPathObjectPtr result;
          xmlNodeSetPtr     nodeset;
          xmlChar          *xpath = xmlCharStrdup(exp.c_str());
          xmlChar          *keyword;
          unsigned int      size;


                            result = getSet(xpath);

                            if (result)
                            {
                                    nodeset = result->nodesetval;
                                    size    = (nodeset) ? nodeset->nodeNr : 0;

                                    for(unsigned int iter=0; iter < size; iter++)
                                    {
                                        keyword = xmlNodeListGetString(mDoc, nodeset->nodeTab[iter]->xmlChildrenNode, 1);
                                        retVal.push_back(std::string( (char*)keyword));
                                    }

                                    xmlFree(keyword);
                                    xmlXPathFreeObject (result);
                            }

                return retVal;
        }


        std::string ConfigReader::getAttribute(std::string exp)
        {
          std::string retVal;
          xmlChar *xpath = xmlCharStrdup(exp.c_str());
          xmlNodeSetPtr nodeset;
          xmlXPathObjectPtr result;
          xmlChar *keyword;


                        result = getSet(xpath);

                        if (result)
                        {
                            nodeset = result->nodesetval;
                            keyword = xmlNodeListGetString(mDoc, nodeset->nodeTab[0]->xmlChildrenNode, 1);
                            retVal  = std::string( (char*)keyword  );
                            xmlFree(keyword);
                            xmlXPathFreeObject (result);
                        }

                return retVal;
        }


        xmlXPathObjectPtr ConfigReader::getSet (xmlChar *xpath)
        {
          xmlXPathContextPtr context;
          xmlXPathObjectPtr result = NULL;


                    context = xmlXPathNewContext(mDoc);

                    if (context == NULL)
                        throw std::string("Error in xmlXPathNewContext\n");


                    result = xmlXPathEvalExpression(xpath, context);
                    xmlXPathFreeContext(context);

                    if (result == NULL)
                        throw std::string("Error in xmlXPathEvalExpression\n");


                    if(xmlXPathNodeSetIsEmpty(result->nodesetval))
                    {
                        xmlXPathFreeObject(result);
                        result = NULL;
                    }

                return result;
        }


ConfigReader::~ConfigReader()
{
        if( NULL != mDoc )
        {
            xmlFreeDoc(mDoc);
            xmlCleanupParser();
            mDoc = NULL;
        }
}
