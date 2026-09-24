# src/CMakeLists.txt

# Streamline the build config by using the "GEP" as the target
add_executable(GEP game.cpp main.cpp input/input_system.cpp)

target_compile_features(GEP PRIVATE cxx_std_23)

target_link_libraries(GEP PRIVATE 
   SDL3::SDL3
   SDL3_image::SDL3_image
)

set(ASSETS_INPUT_DIRECTORY 
"${CMAKE_SOURCE_DIR}/assets" 
CACHE STRING "Input directory of in-game assets")

add_custom_target(CopyAssets
     COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different 
         ${ASSETS_INPUT_DIRECTORY} $<TARGET_FILE_DIR:GEP>/assets)

add_dependencies(GEP CopyAssets)