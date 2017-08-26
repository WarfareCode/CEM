#include "CEMCommon.h"
#include "SourceControl.h"
#include "SourceControlInterface.h"
#include "SourceControlFactory.h"

#include <string>
  using std::string;
#include <iostream>
#include <vector>

#include <gmock/gmock.h>
  using ::testing::Eq;
#include <gtest/gtest.h>
  using ::testing::Test;
using ::testing::TestWithParam;

#include "MockSourceDefinitionInterface.h"


namespace CEM
{
namespace SourceControlFactory_Test
{
namespace testing
{
  class SourceFactory_Test : public Test
    {
    protected:
       SourceFactory_Test(){}
       ~SourceFactory_Test(){}

      virtual void SetUp()
      {
	sourceDefinition_ = std::make_shared<MockSourceDefinition>();
	EXPECT_CALL(*sourceDefinition_, getSourceAmplitude()).WillRepeatedly(::testing::Return(1200));
	EXPECT_CALL(*sourceDefinition_, getSourceDelay()).WillRepeatedly(::testing::Return(0));
	EXPECT_CALL(*sourceDefinition_, getPulseWidth()).WillRepeatedly(::testing::Return(10));
	EXPECT_CALL(*sourceDefinition_, getSourceFrequency()).WillRepeatedly(::testing::Return(35e9));
      }
      virtual void TearDown(){}

       std::shared_ptr<MockSourceDefinition> sourceDefinition_;
      
       std::shared_ptr<SourceControlInterface> source_ptr_;
       SourceControlFactory sourceFactory_;
    };

  TEST_F(SourceFactory_Test, create_invalid_pulse)
  {
    	std::string TypeString = "Invalid Pulse Type";
        std::string eString = "SourceControlFactory::createSourceControl ... " + TypeString + " is not a recognized Source Type";
    try
      {
	EXPECT_CALL(*sourceDefinition_, getSourceType()).WillRepeatedly(::testing::Return(TypeString));
	source_ptr_ = sourceFactory_.createSourceControl(sourceDefinition_);
      }
    catch(std::runtime_error error)
      {
	EXPECT_THAT(error.what(), Eq(eString));
      }

  }
  
  TEST_F(SourceFactory_Test, create_gaussian_pulse)
  {
    std::string TypeString = "Gaussian Pulse";
    EXPECT_CALL(*sourceDefinition_, getSourceType()).WillRepeatedly(::testing::Return(TypeString));

    source_ptr_ = sourceFactory_.createSourceControl(sourceDefinition_);

    EXPECT_THAT(source_ptr_->getSourceType(), Eq(TypeString));

  }

  TEST_F(SourceFactory_Test, create_modulated_gaussian_pulse)
  {
    std::string TypeString = "Modulated Gaussian Pulse";
    EXPECT_CALL(*sourceDefinition_, getSourceType()).WillRepeatedly(::testing::Return(TypeString));

    source_ptr_ = sourceFactory_.createSourceControl(sourceDefinition_);

    EXPECT_THAT(source_ptr_->getSourceType(), Eq(TypeString));

  }

  
  TEST_F(SourceFactory_Test, create_square_pulse)
  {
    std::string TypeString = "Square Pulse";
    EXPECT_CALL(*sourceDefinition_, getSourceType()).WillRepeatedly(::testing::Return(TypeString));

    source_ptr_ = sourceFactory_.createSourceControl(sourceDefinition_);

    EXPECT_THAT(source_ptr_->getSourceType(), Eq(TypeString));

  }

  TEST_F(SourceFactory_Test, create_modulated_square_pulse)
  {
    std::string TypeString = "Modulated Square Pulse";
    EXPECT_CALL(*sourceDefinition_, getSourceType()).WillRepeatedly(::testing::Return(TypeString));

    source_ptr_ = sourceFactory_.createSourceControl(sourceDefinition_);

    EXPECT_THAT(source_ptr_->getSourceType(), Eq(TypeString));

  }


} // namespace testing
} // namespace HDF5Reader_Test
} // namespace CEM
