# cmake_minimum_required(VERSION 3.8)
# set(PROJECT_NAME Neutrino-Pulse-Generator)

# set(SOURCE_DIR src)

# set(INCLUDES_DIR include)

# set()

# set(SOURCE ${SOURCE_DIR}/main.cc)

# set(CMAKE_CXX_STANDARD 17)

# projec(${PROJECT_NAME} VERSION 1.0)

# add_executable(${PROJECT_NAME} ${SOURCE})
# foreach(LIBRARY ${INLCLUDES_DIR})
#     add_subdirectory("${INCLUDES_DIR}/${LIBRARY}")
    
# endforeach(LIBRARY)

# target_link_libraries((${PROJECT_NAME}))


cmake_minimum_required(VERSION 3.8)

# Set the project name and version
set(PROJECT_NAME Neutrino-Pulse-Generator)
project(${PROJECT_NAME} VERSION 1.0)

# Set directories
set(SOURCE_DIR src)
set(INCLUDES_DIR include)

# Set the source files
set(SOURCE 
    ${SOURCE_DIR}/main.cc 
    ${SOURCE_DIR}/lut.cc 
    ${SOURCE_DIR}/mmc.cc
    ${SOURCE_DIR}/utils.cc
    ${SOURCE_DIR}/squid.cc 
    ${SOURCE_DIR}/channel.cc
    ${SOURCE_DIR}/pixel.cc)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(${PROJECT_NAME} ${SOURCE})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDES_DIR})

# Install executable to the 'bin' directory
#install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Install header files to the 'include' directory
install(DIRECTORY ${INCLUDES_DIR}/ DESTINATION include)

# Install license file
install(FILES LICENSE DESTINATION .)