#ifndef _CONFIGREADER_H_
#define _CONFIGREADER_H_

#include <stdio.h>
#include <string>
#include <vector>

#include <libxml/parser.h>
#include <libxml/xpath.h>

/**
 * Reads configuration files
 */
class ConfigReader
{
public:

        ConfigReader();

        ConfigReader(std::string configFile);

        void openFile(std::string configFile);

        /**
         * Obtains a list of atributes.
         * @param exp XPATH expression.
         * @return List of matching atributes.
         **/
        std::vector<std::string> getAttributes(std::string exp);

        /**
         * Obtains an atribute.
         * @param exp XPATH expression.
         * @return matching atribute.
         **/

        std::string getAttribute(std::string exp);

        virtual ~ConfigReader();

protected:

        /**
         * Used to get a object based on a string id.
         * @param xpath id.
         */
        xmlXPathObjectPtr getSet (xmlChar *xpath);

private:
  xmlDocPtr     mDoc;
  std::string 	mFile;
};

#endif // _CONFIGREADER_H_
