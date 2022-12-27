cmake_minimum_required(VERSION 3.10)

project(C_UTILS
		VERSION 1.0.0
		DESCRIPTION "C Utilities project" 
		HOMEPAGE_URL "HTTPS://GITHUB.COM/DALITSOSAKALA/C_UTILS.GIT")

include(GNUInstallDirs)

#add_library(<name>[STATIC | SHARED | MODULE])
add_library(mod SHARED sources/modular.c)

set_target_properties(mod PROPERTIES SOVERSION 1)

# target_compile_definitions(mod PRIVATE DEBUG=1)

IF(UNIX) 
	target_link_libraries(mod m) 
ENDIF(UNIX)

set_target_properties(mod PROPERTIES PUBLIC_HEADER include/modular.h)

target_include_directories(mod PRIVATE .)
#target_include_directories(mylib PRIVATE include)

#Declare files to install
install(TARGETS mod LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} PUBLIC_HEADER  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
