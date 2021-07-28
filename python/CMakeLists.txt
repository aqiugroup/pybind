
# cloned dependency: pybind11
# add path and search for python installed
add_subdirectory(pybind11)


# --------------------------------------
# wrap sayhi

# add all unit test files
file(GLOB SAYHI_WRAPPER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "sayhi_wrapper/*.cpp")

# wrapper lib
set(SAYHI_WRAPPER_TARGET_NAME "_sayhi_py_wrapper")

# add wrapper source
add_library(${SAYHI_WRAPPER_TARGET_NAME} MODULE ${SAYHI_WRAPPER_SRCS})

target_link_libraries(${SAYHI_WRAPPER_TARGET_NAME} ${PROJECT_NAME} 
    ${SAYHI_ADDITIONAL_LIBRARIES} pybind11::module)

# module naming and location
set_target_properties(${SAYHI_WRAPPER_TARGET_NAME} PROPERTIES 
    PREFIX "${PYTHON_MODULE_PREFIX}"
    SUFFIX "${PYTHON_MODULE_EXTENSION}" 
    OUTPUT_NAME ${SAYHI_WRAPPER_TARGET_NAME})

# for export setup.py
set(SAYHI_WRAPPER_FILE_NAME "${PYTHON_MODULE_PREFIX}${SAYHI_WRAPPER_TARGET_NAME}${PYTHON_MODULE_EXTENSION}")


# --------------------------------------
# install wrapper and python source

# custom target
add_custom_target(python_package ALL)
# depends on wrappers
add_dependencies(python_package ${SAYHI_WRAPPER_TARGET_NAME} ${SOPHUS_WRAPPER_TARGET_NAME})

# copy built wrapper to package by custom target
# TODO: this is to source location and have to be ignored by gitignore, better solution??
add_custom_command(TARGET python_package POST_BUILD COMMAND ${CMAKE_COMMAND} -E 
    copy $<TARGET_FILE:${SAYHI_WRAPPER_TARGET_NAME}> "${CMAKE_CURRENT_SOURCE_DIR}/sayhi")

# copy project lib when shared
if(SAYHI_BUILD_SHARED_LIB)
  add_custom_command(TARGET python_package POST_BUILD COMMAND ${CMAKE_COMMAND} -E 
      copy $<TARGET_FILE:${PROJECT_NAME}> "${CMAKE_CURRENT_SOURCE_DIR}/sayhi")
endif()

# path to export setup.py
set(SAYHI_WRAPPER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/sayhi")

# generate setup.py for distutils
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in" "${PROJECT_BINARY_DIR}/setup.py")

# install by python `python setup.py install`
install(CODE "execute_process(COMMAND ${PYTHON_EXECUTABLE} setup.py install)")

