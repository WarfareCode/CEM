add_library(InputParser AbsInputParser.h InputStruct.h InputParser_YAML.h InputParser_YAML.cpp )


add_subdirectory(tests)
add_test(TestInputParser tests/InputParser_Test)

add_custom_command(TARGET InputParser POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                      ${CMAKE_SOURCE_DIR}/src/InputParser/tests/Input_Data
		      $<TARGET_FILE_DIR:InputParser>/Input_Data)

add_custom_command(TARGET InputParser POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
		   ${CMAKE_SOURCE_DIR}/src/InputParser/tests/Input_Data
                   ${BINARY_TEST_DIRECTORY}/Input_Data)
		   
