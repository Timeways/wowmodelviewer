# CxImage lib

set(SRC_FILES
    tif_xfile.cpp
    ximabmp.cpp
    ximadsp.cpp
    ximaenc.cpp
    ximaexif.cpp
    ximage.cpp
    ximagif.cpp
    ximahist.cpp
    ximaico.cpp
    ximainfo.cpp
    ximaint.cpp
    ximajas.cpp
    ximajbg.cpp
    ximajpg.cpp
    ximalpha.cpp
    ximalyr.cpp
    ximamng.cpp
    ximapal.cpp
    ximapcx.cpp
    ximapng.cpp
    ximaraw.cpp
    ximasel.cpp
    ximaska.cpp
    ximatga.cpp
    ximath.cpp
    ximatif.cpp
    ximatran.cpp
    ximawbmp.cpp
    ximawmf.cpp
    ximawnd.cpp
    xmemfile.cpp
)

message(STATUS "Using CxImage")

if (APPLE)
  add_definitions(-D_MAC)
  add_definitions(-D_MAC_INTEL)
endif()

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux)
  add_definitions(-D_LINUX)
  add_definitions(-D_LINUX32)
endif()

if (WIN32)
    include_directories(${CMAKE_SOURCE_DIR}/Dependencies/include)
  add_definitions(-D_WINDOWS)
  add_definitions(-D_WIN32)
endif()

add_library(cximage STATIC ${SRC_FILES})
set_property(TARGET cximage PROPERTY FOLDER "3rdparty libraries")
target_link_libraries(cximage ${CMAKE_SOURCE_DIR}/Dependencies/lib/jpeg.lib 
  ${CMAKE_SOURCE_DIR}/Dependencies/lib/libpng.lib)

#if(WIN32)
#  install(TARGETS cximage RUNTIME DESTINATION "${WMV_BASE_PATH}/../bin/")
#endif(WIN32)

