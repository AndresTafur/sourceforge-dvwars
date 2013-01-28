/*
 *  Copyright (C) 2011-2013 Jorge A. Tafur Q. (jatafurq).
 *
 *  This file is part of Da Vinci Wars project.
 *
 *  Da Vinci Wars is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Da Vinci Wars is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.  If not, see <http://www.gnu.org/licenses/>.
 */

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
