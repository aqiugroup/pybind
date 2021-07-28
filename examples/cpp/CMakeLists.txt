# add all example files
file(GLOB EXAMPLE_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

# get example names by remove extension
foreach(EXPFILE ${EXAMPLE_SRCS})
  get_filename_component(EXMP ${EXPFILE} NAME_WE)
  list(APPEND EXAMPLE_LIST ${EXMP})
endforeach()


# add all unit example targets
foreach(EXMP ${EXAMPLE_LIST})
  add_executable(${EXMP} "${EXMP}.cpp")

  target_link_libraries(${EXMP} ${PROJECT_NAME})
endforeach()

