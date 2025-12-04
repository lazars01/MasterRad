cmake_minimum_required(VERSION 3.20)

# Naziv i jezik projekta
project(MasterRad LANGUAGES CXX)

# Standard i podešavanja
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Default build type ako nije višekonfigurisani generator (Ninja/Make)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Uključi korisna upozorenja
option(MASTERRAD_WARNINGS "Enable extra warnings" ON)
if(MASTERRAD_WARNINGS)
  if(MSVC)
    add_compile_options(/W4 /permissive-)
  else()
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()
endif()

# Dodaj podprojekat (napomena: ime foldera sadrži '&', zato su navodnici)
add_subdirectory("StrongAPandBridges")
add_subdirectory("B_APandBridges")
add_subdirectory("ST_APandBridges")
