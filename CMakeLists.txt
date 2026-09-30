cmake_minimum_required(VERSION 3.28.3)

project (

Hyoscine-GL

VERSION 0.1

LANGUAGES C CXX
	)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

find_package(SDL3 QUIET)
if(NOT SDL3_FOUND)
FetchContent_Declare(
	SDL3
	GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
	GIT_TAG origin/main
	OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL3)
endif()


find_package(glm QUIET)

if(NOT glm_FOUND)
FetchContent_Declare(
	glm
	URL https://github.com/g-truc/glm/archive/refs/tags/1.0.3.tar.gz 
		    )

FetchContent_MakeAvailable(glm)
	endif()

	file(GLOB Hysc
		CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Hysc/*)


#Inclusions of 3rd Part Libraries: (Difficult Ones as of now, maybe all in future)
#   {


add_library(glad ${CMAKE_CURRENT_SOURCE_DIR}/OtherVendors/gladAndKHR/glad/gl.c)
target_include_directories(glad PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/OtherVendors/gladAndKHR)

add_library(stb_img INTERFACE)
target_include_directories(stb_img INTERFACE
	${CMAKE_CURRENT_SOURCE_DIR}/OtherVendors/stb_img)
#}


add_library(Codex ${Hysc})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Core
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Hyoscine main.cpp)

target_link_libraries(Codex PUBLIC SDL3
				  glad
				   glm
				 stb_img
		     )

target_link_libraries(Hyoscine PUBLIC Codex )
