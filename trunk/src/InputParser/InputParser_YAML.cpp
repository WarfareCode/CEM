/**
* @file InputParser_YAML.cpp
* @brief Implementation of the InputParserYAML class
* @author Ben Frazier
* @date 08/14/2017 */
#include <math.h>

#include "InputParser_YAML.h"

namespace CEM
{
  /**
   * \brief Standard Constructor
   *
   */
  template<typename T> InputParserYAML<T>::InputParserYAML()
  {
 
  }

 template<typename T> bool InputParserYAML<T>::OpenFile(std::string fileName)
  {
    node_ = YAML::LoadFile(FILE::FindInputFile(fileName));

    if (node_.IsNull())
      throw std::runtime_error("InputParserYAML::ReadInputFile ... Basenode is Null");

    return true;
  }
  
template<typename T> bool InputParserYAML<T>::FindSection(std::string inputString)
  {
    node_ = node_[inputString];
    
     if (node_.IsNull())
       {
	 std::string eString = "InputParserYAML::FindSection ... Can not find " + inputString;
         throw std::runtime_error(eString);
       }
     
     return true;
  }

  
  template<typename T> T InputParserYAML<T>::GetInput(std::string inputString)
  {
    node_ = node_[inputString];

    if (node_.IsNull())
    {
      std::string eString = "InputParserYAML::GetInput ... Can not find " + inputString;
      throw std::runtime_error(eString);
    }

    T output;

    node_ >> output;

    return output;
  }

  
}//end namespace CEM

