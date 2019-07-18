cmake_minimum_required (VERSION 3.8 FATAL_ERROR)

# Set the project name to be the name of the folder that holds the source code
get_filename_component(PROJECT ${CMAKE_SOURCE_DIR} NAME)
project(PROJECT)

# Aliases
set(ROOT   ${CMAKE_SOURCE_DIR})
set(SRCDIR ${CMAKE_SOURCE_DIR}/src)
set(INCDIR ${CMAKE_SOURCE_DIR}/include)
set(LIBDIR ${CMAKE_SOURCE_DIR}/lib)
set(RESDIR ${CMAKE_SOURCE_DIR}/assets)
set(BINDIR ${CMAKE_BINARY_DIR})


# Find system packages
find_package(OpenGL REQUIRED)
if(NOT MSVC)
	find_package(GLEW REQUIRED)
endif()
 
# Turning off parts of GLFW we do not want to build
set(GLFW_BUILD_EXAMPLES 0)
set(GLFW_BUILD_TESTS 0)
set(GLFW_BUILD_DOCS 0)

# Adding subdirectory, building the glfw library which we will link to later on.
add_subdirectory("${LIBDIR}/glfw/")

# Define executeables by entrypoint
add_executable(${PROJECT} "${SRCDIR}/main.cpp")

set_target_properties( ${PROJECT}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${BINDIR}"
	LIBRARY_OUTPUT_DIRECTORY "${BINDIR}/bin"
	OUTPUT_NAME "OKEII"	# <3
)

# Enlist all source files used (except the ones already reffered to in 'add_executable')
target_sources(${PROJECT}
	  PRIVATE ${LIBDIR}/stb/stb_image_impl.cpp
	  PRIVATE ${INCDIR}/noise/OpenSimplex.cpp
	  
#     PRIVATE ${LIBDIR}/gfx/src/gfx.cpp

      PRIVATE ${SRCDIR}/ShaderProgram.cpp
      PRIVATE ${SRCDIR}/VertexBuffer.cpp
      PRIVATE ${SRCDIR}/VertexArray.cpp
      PRIVATE ${SRCDIR}/IndexBuffer.cpp
      PRIVATE ${SRCDIR}/Transform.cpp
      PRIVATE ${SRCDIR}/Camera.cpp
	  PRIVATE ${SRCDIR}/Texture.cpp
	  PRIVATE ${SRCDIR}/Input.cpp
	  PRIVATE ${SRCDIR}/UtilityFunctions.cpp
	  PRIVATE ${SRCDIR}/ControllableCamera.cpp
	  PRIVATE ${SRCDIR}/components/Component.cpp
	  PRIVATE ${SRCDIR}/components/SpriteRenderer.cpp
	  PRIVATE ${SRCDIR}/components/HelloWorld.cpp
	  PRIVATE ${SRCDIR}/GameObject.cpp

#     PRIVATE ${SRCDIR}/uniformBuffer.cpp
#     PRIVATE ${SRCDIR}/frameBuffer.cpp
)

# Set up directories from which you can #include
target_include_directories( ${PROJECT}
    PRIVATE ${ROOT}/include
    PRIVATE ${SRCDIR}
    PRIVATE ${LIBDIR}
    PRIVATE ${LIBDIR}/GFX/include
    PRIVATE ${LIBDIR}/glew/include
    PRIVATE ${LIBDIR}/glm
    PRIVATE ${LIBDIR}/glfw/include
	PRIVATE ${LIBDIR}/stb
  # PRIVATE ${LIBDIR}/imgui
)

# enlist all the assets already in the build directory
file(GLOB_RECURSE OLD_RESOURCES
	LIST_DIRECTORIES true	# also list directories
	${BINDIR}/assets/*   # the pattern to look for. * is a wildcard
)
 # remove all the old assets
if(DEFINED OLD_RESOURCES AND NOT OLD_RESOURCES STREQUAL "")
	file(REMOVE_RECURSE ${OLD_RESOURCES})
endif()
# enlist all the runtime assets (i.e. the ones in the source directory)
file(GLOB_RECURSE ALL_RESOURCES
	RELATIVE ${RESDIR}	# format the output paths relative to RESDIR
	assets/*			# the pattern to look for. * is a wildcard
)
foreach(file ${ALL_RESOURCES})
    message("Copy file:  ${RESDIR}/${file}  -> ${BINDIR}/assets/${file}")
	# using configure_file instread of file(COPY ...) because we want it to happen every time we build
    configure_file( ${RESDIR}/${file} ${BINDIR}/assets/${file} COPYONLY)
endforeach(file)

#########################################
# Microsoft Visual studio 2017 (Windows)
#########################################
if(MSVC)
	# NOTE: if you find a nicer way to detect build configuration, please notify us on discord or gitlab!
	# Find the libraries matching build configuration: 4 => Win32, 8 => x64
	if( ${CMAKE_SIZEOF_VOID_P} EQUAL 4)
	# Win32 configuration
		#declare where to find glew32.lib
		set(GLEW_LIBRARY ${LIBDIR}/glew/lib/Release/Win32/glew32.lib)
		# Copy these files in order to allow windows to link your executeables
		file(COPY ${LIBDIR}/glew/bin/Release/Win32/glew32.dll DESTINATION ${BINDIR})
	else()
	# x64 configuration
		set(GLEW_LIBRARY ${LIBDIR}/glew/lib/Release/x64/glew32.lib)
		file(COPY ${LIBDIR}/glew/bin/Release/x64/glew32.dll DESTINATION ${BINDIR})
	endif()
else()
#########################################
# Apple, linux, others...
#########################################
	target_compile_options(
	    ${PROJECT}
	    PRIVATE "-Wall"
	    PRIVATE "-Wextra"
	    PRIVATE "-g"
	    PRIVATE "-std=c++17"
	)
endif()

target_link_libraries(
    ${PROJECT}
    PRIVATE ${OPENGL_LIBRARIES}
    PRIVATE ${GLEW_LIBRARY}
    PRIVATE glfw
)
message("CMake configured ${PROJECT} successfully!")
