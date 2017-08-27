/**
* @file InputParser.cpp
* @brief Implementation of the InputParser class
* @author Ben Frazier
* @date 08/14/2017 */
#include <math.h>

#include "InputParser.h"
namespace CEM
{
  /**
   * \brief Standard Constructor
   *
   */
  InputParser::InputParser():
    fileLoaded_(false) 
  {
 
  }

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
  
   /**
   * \brief Get the Grid Definition Itnerface
   *
   */
  std::shared_ptr<GridDefinitionInterface> InputParser::getGridDefinition()
  {
     if (fileLoaded_)
       return shared_from_this();
     else throw std::runtime_error("InputParser::getGridDefinition()....Input File Not Loaded.");
  }

   /**
   * \brief Get the Source Control Itnerface
   *
   */
  std::shared_ptr<SourceDefinitionInterface> InputParser::getSourceDefinition()
  {
     if (fileLoaded_)
       return shared_from_this();
     else throw std::runtime_error("InputParserYAML::getSourceDefinition()....Input File Not Loaded.");
  }
  
  void InputParser::ReadGridInfo()
  {

    YAML::Node currentNode = FindYAMLSection("Grid Control", basenode_);

    std::cout<<"ok ... " << std::endl;
    
    gridSpecificationType_ = GetYAMLInput<std::string>("Specification", currentNode);
    gridNumDimensions_ = GetYAMLInput<int>("Number of Dimensions", currentNode);
    gridZLength_ = GetYAMLInput<double>("Z Length in meters", currentNode);
    gridZStep_ = GetYAMLInput<double>("Z Spatial Step in meters", currentNode);

    YAML::Node dNode = FindYAMLSection("Dielectric Constant",currentNode);
    ReadDielectricInfo(dNode);

    vectorZLength_ = round(gridZLength_/gridZStep_);
    
  }

  void InputParser::ReadTemporalDomainInfo()
  {
    YAML::Node timenode = FindYAMLSection("Simulation Temporal Domain",basenode_);

    startTime_ = GetYAMLInput<double>("Start Time", timenode);
    stopTime_ = GetYAMLInput<double>("Stop Time", timenode);
    timeStep_ = GetYAMLInput<double>("Time Step in Seconds",timenode);
  }
  
  void InputParser::ReadSpatialDomainInfo()
  {
    YAML::Node spacenode = FindYAMLSection("Simulation Spatial Domain",basenode_);

    computationType_ = GetYAMLInput<std::string>("Computation Type", spacenode);
    absorbingBoundaryCondition_ = GetYAMLInput<std::string>("Absorbing Boundary Condition", spacenode);
  }

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

  void InputParser::ReadInputSourceInfo()
  {
    YAML::Node sourceNode = FindYAMLSection("Source Info",basenode_);
     
     sourceType_ = GetYAMLInput<std::string>("Type",sourceNode);
     sourceAmplitude_ = GetYAMLInput<double>("Amplitude",sourceNode);
     sourceDelay_ = GetYAMLInput<double>("Delay in Seconds",sourceNode);
     pulseWidth_ = GetYAMLInput<double>("Pulse Width in Seconds",sourceNode);
     spatialIndex_ = GetYAMLInput<double>("Spatial Index",sourceNode);
     sourceFrequency_ = GetYAMLInput<double>("Frequency",sourceNode);  
  }

  void InputParser::ReadDataLoggingInfo()
  {
    YAML::Node dataNode = FindYAMLSection("Data Logging Info",basenode_);
     
    outputFileName_ =  GetYAMLInput<std::string>("Output File Name",dataNode);
    outputRate_ = GetYAMLInput<double>("Output Log Time in Seconds",dataNode);
  }

  /**
   * \brief read the input file
   *
   * This function reads the configuration into the input structure 
   * @param fileName Name of the file to read*/
  void InputParser::ReadInputFile(std::string fileName)
  {
    inputFileName_ = fileName;
    basenode_ = OpenYAMLFile(fileName);
    ReadGridInfo();
    ReadInputSourceInfo();
    ReadDataLoggingInfo();
    ReadSpatialDomainInfo();
    ReadTemporalDomainInfo();

    fileLoaded_ = true;
  }

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

  template<typename T> T GetYAMLInput(std::string inputString, YAML::Node basenode)
  {
    YAML::Node node = basenode[inputString];

    if (node.IsNull())
    {
      std::string eString = "YAMLReaderFunctions::GetInput ... Can not find " + inputString;
      throw std::runtime_error(eString);
    }

    std::cout<<"input string: " << inputString << std::endl;
    T output = node.as<T>();

    std::cout<<"input string: " << inputString << " result: " << output << std::endl;

    return output;
  }
  
}//end namespace CEM

