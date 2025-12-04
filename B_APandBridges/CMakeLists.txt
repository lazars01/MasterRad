# B_APandBridges/CMakeLists.txt

# Ne pozivamo project() ovde — top-level već postavlja C++ standard i ostalo.

# -- Opciona upozorenja (možeš isključiti sa -DSTRONGAP_BRIDGES_WARNINGS=OFF)
option(B_AP_BRIDGES_WARNINGS "Enable extra warnings for StrongAPandBridges targets" ON)
function(_enable_warnings tgt)
  if(B_AP_BRIDGES_WARNINGS)
    if(MSVC)
      target_compile_options(${tgt} PRIVATE /W4 /permissive-)
    else()
      target_compile_options(${tgt} PRIVATE -Wall -Wextra -Wpedantic)
    endif()
  endif()
endfunction()

# ----- Biblioteka sa algoritmom (iz src/), headeri su u include/
add_library(b_ap_bridges_lib
            source/BiconnectedComponents.cpp 
            source/BBridges.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../StrongAPandBridges/source/StrongBridges.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../StrongAPandBridges/source/LengauerTarjanEdgeDominators.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../StrongAPandBridges/source/LengauerTarjanVertexDominators.cpp
            source/BAP.cpp
            ${CMAKE_CURRENT_SOURCE_DIR}/../StrongAPandBridges/source/StrongAP.cpp)

# Omogući javni include za potrošače biblioteke (app, testovi, itd.)
target_include_directories(b_ap_bridges_lib
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/../StrongAPandBridges/include
)

_enable_warnings(b_ap_bridges_lib)

# (Opcija) Lepše grupisanje u Visual Studio Solution Explorer-u
set_property(TARGET b_ap_bridges_lib PROPERTY FOLDER "B_APandBridges")

# ----- Aplikacija (main) koja linkuje biblioteku
add_executable(b_ap_bridges_app
    source/main.cpp
)

target_link_libraries(b_ap_bridges_app
    PRIVATE b_ap_bridges_lib
)

_enable_warnings(b_ap_bridges_app)
set_property(TARGET b_ap_bridges_app PROPERTY FOLDER "B_APandBridges")

# (Opciono) Ako želiš da app bude defaultni “launch” target u VS Code CMake Tools:
# set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT b_ap_bridges_app)
