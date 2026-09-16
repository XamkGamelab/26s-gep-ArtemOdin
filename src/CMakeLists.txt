# src/CMakeLists.txt

# Streamline the build config by using the "GEP" as the target
add_executable(GEP "game.cpp" "main.cpp")

target_compile_features(GEP PRIVATE cxx_std_23)

target_link_libraries(GEP PRIVATE SDL3::SDL3)