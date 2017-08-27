/**
* @file InputParser_YAML.h
* @brief Header File for the InputParserYAML class
* @author Ben Frazier
* @date 08/14/2017 */

#ifndef InputParser_YAML_H
#define InputParser_YAML_H

#include "yaml-cpp/yaml.h"
#include "CEMCommon.h"

#include <fstream>
using namespace YAML;
namespace CEM
{
  template<typename T>
  class InputParserYAML 
  {
  public:
    InputParserYAML();


    bool OpenFile(std::string fileName);
    bool FindSection(std::string inputString);
    T GetInput(std::string inputString);

  
  private:
    YAML::Node node_; /*!<YAML node to traverse through the file*/

  };
}

#endif
