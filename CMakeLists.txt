cmake_minimum_required(VERSION 3.29)

set(VCPKG_TARGET_TRIPLET x64-mingw-dynamic)

project(NewerCppFeatures)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



set(Boost_NO_WARN_NEW_VERSIONS 1)
set(Boost_USE_STATIC_LIBS OFF)
add_definitions(-DBOOST_LOG_DYN_LINK=1)

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(NewerCppFeatures main.cpp)
target_link_libraries(NewerCppFeatures PRIVATE Boost::boost)
target_link_libraries(NewerCppFeatures PRIVATE OpenSSL::SSL OpenSSL::Crypto)
target_include_directories(NewerCppFeatures INTERFACE C:/Users/rgawlik/vcpkg/packages/boost-multiprecision_x64-mingw-dynamic/include/boost/multiprecision) # for recognizing include files

add_executable(main_coroutines main_coroutines.cpp)
