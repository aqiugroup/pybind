# build lib

# --------------------------------------
# source for lib

# core sub-folders for source and headers
set(SAYHI_SUBDIR .)
message(STATUS "Build module: ${SAYHI_SUBDIR}")
message(STATUS "SAYHI_USE_DEBUG module: ${SAYHI_USE_DEBUG}")

# lib source
file(GLOB SAYHI_SRC "${SAYHI_SUBDIR}/*.cpp" "${SAYHI_SUBDIR}/*.h")

# install headers
file(GLOB SUBFOLDER_HEADERS "${SAYHI_SUBDIR}/*.h")
install(FILES ${SUBFOLDER_HEADERS} DESTINATION "include/${PROJECT_NAME}/${SUBDIR}")

# --------------------------------------
# lib
message(STATUS "SAYHI_ADDITIONAL_LIBRARIES : ${SAYHI_ADDITIONAL_LIBRARIES}")
if(SAYHI_BUILD_SHARED_LIB)
    # shared
    message(STATUS "Library: build shared library")
    add_library(${PROJECT_NAME} SHARED ${SAYHI_SRC})
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

    # link to dependency
    target_link_libraries(${PROJECT_NAME} ${SAYHI_ADDITIONAL_LIBRARIES})

    # install lib
    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-export LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib RUNTIME DESTINATION bin)

else()
    # static
    message(STATUS "Library: build static library")
    add_library(${PROJECT_NAME} STATIC ${SAYHI_SRC})
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME} CLEAN_DIRECT_OUTPUT 1)

    # link to dependency
    target_link_libraries(${PROJECT_NAME} ${SAYHI_ADDITIONAL_LIBRARIES})

    # install lib
    install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-export ARCHIVE DESTINATION lib)

endif()


# --------------------------------------
# install lib

# export config file for CMake to search
set(${PROJECT_NAME}_INCLUDE_DIR "include")
set(CMAKE_CONFIG_DEST "lib/cmake/${PROJECT_NAME}")

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/${PROJECT_NAME}-config.cmake.in"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake"
    INSTALL_DESTINATION ${CMAKE_CONFIG_DEST}
    PATH_VARS ${PROJECT_NAME}_INCLUDE_DIR)

# install config
install(EXPORT ${PROJECT_NAME}-export DESTINATION ${CMAKE_CONFIG_DEST} FILE "${PROJECT_NAME}-export.cmake" )
install(FILES "${PROJECT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" DESTINATION ${CMAKE_CONFIG_DEST})
