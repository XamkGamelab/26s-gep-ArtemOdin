#vendor/CMakeLists.txt

include(FetchContent)

set(FETCHCONTENT_QUIET OFF CACHE BOOL "Enale FetchContent logging")

FetchContent_Declare(
   SDL3
   GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
   GIT_TAG release-3.4.16 #fa2c02bb6e21974a89ea9824bc53c9932abe5f9c
   GIT_SHALLOW ON
   GIT_PROGRESS ON

)

FetchContent_MakeAvailable(SDL3)