/**
* @file InputParser.cpp
* @brief Implementation of the InputParser class
* @author Ben Frazier
* @date 08/14/2017 */
#include <math.h>

#include "InputParser.h"
namespace CEM
{
   //********************************************************************************************
  /**
   * \brief Standard Constructor
   *
   */
  InputParser::InputParser():
    fileLoaded_(false) 
  {
 
  }

  //********************************************************************************************
  /**
   * \brief Get the Input Data Interface
   *
   */
  std::shared_ptr<InputDataInterface> InputParser::getInputData()
   {
     if (fileLoaded_)
       return shared_from_this();
     else throw std::runtime_error("InputParser::getInputData()....Input File Not Loaded.");
   }

    //********************************************************************************************
  /**
   * \brief Read the Grid Definition
   *
   */
  void InputParser::ReadGridInfo()
  {

    YAML::Node currentNode = FindYAMLSection("Grid Control", basenode_);
    
    gridSpecificationType_ = GetYAMLInput<std::string>("Specification", currentNode);
    gridNumDimensions_ = GetYAMLInput<int>("Number of Dimensions", currentNode);
    gridZLength_ = GetYAMLInput<double>("Z Length in meters", currentNode);
    gridZStep_ = GetYAMLInput<double>("Z Spatial Step in meters", currentNode);

    YAML::Node dNode = FindYAMLSection("Dielectric Constant",currentNode);
    ReadDielectricInfo(dNode);

    vectorZLength_ = round(gridZLength_/gridZStep_);
    
  }

  //********************************************************************************************
  /**
   * \brief Read the time info
   *
   */
  void InputParser::ReadTemporalDomainInfo()
  {
    YAML::Node timenode = FindYAMLSection("Simulation Temporal Domain",basenode_);
 
    timeStep_ = GetYAMLInput<double>("Time Step in Seconds",timenode);
    startTime_ = GetYAMLTimeValue("Start Time", timenode);
    stopTime_ = GetYAMLTimeValue("Stop Time", timenode);

    timeLength_ = std::round((stopTime_ - startTime_)/timeStep_);
    
  }

    //********************************************************************************************
  /**
   * \brief Get a time value in either Samples or Seconds
   * @param input String to read the field from
   * @param node Node that identifies the section
   */
  double InputParser::GetYAMLTimeValue(std::string input, YAML::Node node)
  {
    double outvalue;
    std::string test1 = input + " in Seconds";
    std::string test2 = input + " in Samples";

    bool test = false;
    test = CheckYAMLInput(test1, node);

    if(test)
      outvalue = GetYAMLInput<double>(test1,node);
    else
      {
	if (timeStep_ == 0)
	  throw std::runtime_error ("InputParser::GetTimeValue ... timeStep_ has not been set yet ...");

	outvalue = timeStep_*GetYAMLInput<double>(test2,node);
      }
      
    return outvalue;  
  }

  //********************************************************************************************
  /**
   * \brief Read the space info
   *
   */
  void InputParser::ReadSpatialDomainInfo()
  {
    YAML::Node spacenode = FindYAMLSection("Simulation Spatial Domain",basenode_);

    computationType_ = GetYAMLInput<std::string>("Computation Type", spacenode);
    absorbingBoundaryCondition_ = GetYAMLInput<std::string>("Absorbing Boundary Condition", spacenode);
  }

    //********************************************************************************************
  /**
   * \brief Read the dielectric info
   * @param dNode YAML node that defines the start of the section
   */
  void InputParser::ReadDielectricInfo(YAML::Node dNode)
  {
    dielectricSpecification_ =  GetYAMLInput<std::string>("Specification", dNode);

    if(dielectricSpecification_ == "File")
      {
	dielectricFileName_ = GetYAMLInput<std::string>("File Name", dNode);
	dielectricDatasetName_ = GetYAMLInput<std::string>("Dataset Name",dNode);
      }
    else if (dielectricSpecification_ == "Vector")
      {
      }
    else if (dielectricSpecification_ == "Constant")
     {
       dielectricConstant_ =  GetYAMLInput<double>("Value", dNode);
     }
    
  }

   //********************************************************************************************
  /**
   * \brief Read the source info
   *
   */
  void InputParser::ReadInputSourceInfo()
  {
     YAML::Node sourceNode = FindYAMLSection("Source Info",basenode_);
     bool test = false;
     
     sourceType_ = GetYAMLInput<std::string>("Type",sourceNode);
     sourceAmplitude_ = GetYAMLInput<double>("Amplitude",sourceNode);
     sourceDelay_ = GetYAMLTimeValue("Delay", sourceNode);
     pulseWidth_ = GetYAMLTimeValue("Pulse Width", sourceNode);
     spatialIndex_ = GetYAMLInput<double>("Spatial Index",sourceNode);
     sourceFrequency_ = GetYAMLInput<double>("Frequency",sourceNode);  
  }

    //********************************************************************************************
  /**
   * \brief Get the data logging info
   *
   */
  void InputParser::ReadDataLoggingInfo()
  {
    YAML::Node dataNode = FindYAMLSection("Data Logging Info",basenode_);
    bool test;
    
    outputFileName_ =  GetYAMLInput<std::string>("Output File Name",dataNode);
    outputRate_ = GetYAMLTimeValue("Output Log Time", dataNode);
  }

   //********************************************************************************************
  /**
   * \brief read the input file
   *
   * This function reads the configuration into the input structure 
   * @param fileName Name of the file to read*/
  void InputParser::ReadInputFile(std::string fileName)
  {
    inputFileName_ = fileName;
    basenode_ = OpenYAMLFile(fileName);
    ReadTemporalDomainInfo();
    ReadGridInfo();
    ReadDataLoggingInfo();
    ReadSpatialDomainInfo();
    ReadInputSourceInfo();

    fileLoaded_ = true;
  }

      //********************************************************************************************
  /**
   * \brief Open the YAML file
   * @param fileName name of the file to open
   */
    YAML::Node OpenYAMLFile(std::string fileName)
  {
    YAML::Node node = YAML::LoadFile(FILE::FindInputFile(fileName));

    if (node.IsNull())
      {
	std::string eString = "YAMLReaderFunctions::ReadInputFile ... Can not open " + fileName;
        throw std::runtime_error(fileName);
      }

    return node;
  }

  //********************************************************************************************
  /**
   * \brief Find the section in the YAML file
   * @param inputString String that defines the section
   * @param basenode YAML node to start from
   */
  YAML::Node FindYAMLSection(std::string inputString, YAML::Node basenode)
  {
    YAML::Node node = basenode[inputString];
    
     if (node.IsNull())
       {
	 std::string eString = "YAMLReaderFunctions::FindSection ... Can not find " + inputString;
         throw std::runtime_error(eString);
       }
     
     return node;
  }

    //********************************************************************************************
  /**
   * \brief Get input field from YAML file
   * @param inputString String that defines the field to retrieve
   * @param basenode YAML node to start from
   */
  template<typename T> T GetYAMLInput(std::string inputString, YAML::Node basenode)
  {
    YAML::Node node = basenode[inputString];

    if (!basenode[inputString])
    {
      std::string eString = "YAMLReaderFunctions::GetInput ... Can not find " + inputString;
      throw std::runtime_error(eString);
    }

    T output = node.as<T>();
    return output;
  }

    //********************************************************************************************
  /**
   * \brief Check if a field exists in a YAML file
   * @param inputString String that defines the field to check
   * @param basenode YAML node to start from
   */
  bool  CheckYAMLInput(std::string inputString, YAML::Node basenode)
  {

    if (basenode[inputString].Type() == 2)
      return true;
     else
       return false;
  }
  
}//end namespace CEM

