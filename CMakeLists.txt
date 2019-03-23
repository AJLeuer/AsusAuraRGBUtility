cmake_minimum_required(VERSION 3.13)
project(asus_addressable_rgb)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_RELEASE  "/O2")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_executable(hof_link HIDDevices.cpp GalaxHOFGraphicsCard.cpp)
add_executable(hid_test HIDDevices.cpp HIDDevices.hpp AuraDevice.cpp AuraDevice.hpp main.cpp GalaxHOFGraphicsCard.cpp GalaxHOFGraphicsCard.hpp)



include_directories("hidapi-0.7.0/hidapi/")
include_directories(${HIDAPI_INCLUDE_DIRS})
include_directories("./Libraries/Frozen/include")


find_package(HIDAPI REQUIRED)
set(LIBS ${LIBS} ${HIDAPI_LIBRARIES})

target_link_libraries(hof_link ${LIBS})
target_link_libraries(hid_test ${LIBS})
link_directories("./hidapi/Debug" debug)
link_directories("./hidapi/Release" optimized)

configure_file("./hidapi/Debug/hidapi.dll" ${PROJECT_BINARY_DIR} COPYONLY)

if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    configure_file("./hidapi/Debug/hidapi.dll" ${PROJECT_BINARY_DIR} COPYONLY)
elseif(CMAKE_BUILD_TYPE EQUAL "DEBUG")
    configure_file("./hidapi/Release/hidapi.dll" ${PROJECT_BINARY_DIR} COPYONLY)
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")



