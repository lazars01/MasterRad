# StrongAP&Bridges/CMakeLists.txt

# Ne pozivamo project() ovde — top-level već postavlja C++ standard i ostalo.

# -- Opciona upozorenja (možeš isključiti sa -DSTRONGAP_BRIDGES_WARNINGS=OFF)
option(STRONGAP_BRIDGES_WARNINGS "Enable extra warnings for StrongAPandBridges targets" ON)
function(_enable_warnings tgt)
  if(STRONGAP_BRIDGES_WARNINGS)
    if(MSVC)
      target_compile_options(${tgt} PRIVATE /W4 /permissive-)
    else()
      target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
  endif()
endfunction()

# ----- Biblioteka sa algoritmom (iz src/), headeri su u include/
add_library(strongap_bridges_lib
    source/LengauerTarjanVertexDominators.cpp
    source/LengauerTarjanEdgeDominators.cpp 
    source/StrongBridges.cpp 
    source/StrongAP.cpp)

# Omogući javni include za potrošače biblioteke (app, testovi, itd.)
target_include_directories(strongap_bridges_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

_enable_warnings(strongap_bridges_lib)

# (Opcija) Lepše grupisanje u Visual Studio Solution Explorer-u
set_property(TARGET strongap_bridges_lib PROPERTY FOLDER "StrongAPandBridges")

# ----- Aplikacija (main) koja linkuje biblioteku
add_executable(strongap_bridges_app
    source/main.cpp
)

target_link_libraries(strongap_bridges_app
    PRIVATE strongap_bridges_lib
)

_enable_warnings(strongap_bridges_app)
set_property(TARGET strongap_bridges_app PROPERTY FOLDER "StrongAPandBridges")

# (Opciono) Ako želiš da app bude defaultni “launch” target u VS Code CMake Tools:
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT strongap_bridges_app)
