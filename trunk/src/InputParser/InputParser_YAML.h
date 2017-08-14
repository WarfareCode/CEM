/**
* @file InputParser.h
* @brief Header File for the InputParserYAML class *
* @author Ben Frazier*
* @date 08/14/2017 */

#ifndef InputParser_YAML_H
#define InputParser_YAML_H

#include "InputParserInterface.h"
#include "yaml-cpp/yaml.h"
#include "InputStruct.h"

#include <fstream>
using namespace YAML;

class InputParserYAML: public InputParserInterface
{
	public:
	InputParserYAML();
	
	virtual InputParserError ReadInputFile(std::string fileName);
	virtual InputParserError GetInputStruct(InputStruct &input);

        InputParserError ReadInputFile();
	
        std::string GetFileName(){return input_.fileName_;};
        InputStruct GetInput(){return input_;};
	

	//Get functions
	std::string getComputationType(){return input_.computationType_;};
	double getStartTime(){return input_.startTime_;};
	double getStopTime(){return input_.stopTime_;};
	std::string getABC(){return input_.absorbingBoundaryCondition_;};

	private:
	YAML::Node basenode_; /*!<YAML basenode to traverse through the file*/
	
	bool fileLoaded_;
	InputStruct input_; /*!< Input structure that the contents of the file will be loaded to */
	InputParserError error_; /*!< Variable for internal error handling */

};

#endif
