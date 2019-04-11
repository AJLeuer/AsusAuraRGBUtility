cmake_minimum_required(VERSION 3.6.2)
project(asus_addressable_rgb)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_executable(AsusAuraUtility IO/AuraDevice.cpp IO/AuraDevice.hpp main.cpp Utilities/HardwareUtility.cpp Utilities/HardwareUtility.h Utilities/Utility.hpp IO/HIDDeviceInterface.cpp IO/HIDDeviceInterface.h)



include_directories("hidapi-0.7.0/hidapi/")
include_directories(${HIDAPI_INCLUDE_DIRS})
include_directories("./Libraries/Frozen/include")


find_package(HIDAPI REQUIRED)
set(LIBS ${LIBS} ${HIDAPI_LIBRARIES})

target_link_libraries(AsusAuraUtility ${LIBS})
link_directories("./Libraries/HIDAPI/Binaries/Debug" debug)
link_directories("./Libraries/HIDAPI/Binaries/Release" optimized)

configure_file("./Libraries/HIDAPI/Binaries/Debug/hidapi.dll" ${PROJECT_BINARY_DIR} COPYONLY)


if (CMAKE_BUILD_TYPE EQUAL "DEBUG")
    configure_file("./hidapi/Debug/hidapi.dll" ${PROJECT_BINARY_DIR} COPYONLY)
elseif(CMAKE_BUILD_TYPE EQUAL "RELEASE")
    configure_file("./hidapi/Release/hidapi.dll" ${PROJECT_BINARY_DIR} COPYONLY)
endif (CMAKE_BUILD_TYPE EQUAL "DEBUG")



