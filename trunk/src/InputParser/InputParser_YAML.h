/**
* @file InputParser.h
* @brief Header File for the InputParserYAML class
* @todo  Consider adding interfaces for the various options from the InputStruct. This may require generating specific InputParsers through a factor for the various types.
* @author Ben Frazier
* @date 08/14/2017 */

#ifndef InputParser_YAML_H
#define InputParser_YAML_H

#include "InputParserInterface.h"
#include "yaml-cpp/yaml.h"
#include "InputData.h"

#include <fstream>
using namespace YAML;
namespace CEM
{
  class InputParserYAML: public InputParserInterface
  {
  public:
    InputParserYAML();

    //define the virtual functions
    virtual InputParserError ReadInputFile(std::string fileName);
    virtual InputData getInputData();
	
    //now define additional support functions
    InputParserError ReadInputFile();
	
  private:
    YAML::Node basenode_; /*!<YAML basenode to traverse through the file*/
	
    bool fileLoaded_;
    InputData input_; /*!< Input structure that the contents of the file will be loaded to */

  };
}

#endif
