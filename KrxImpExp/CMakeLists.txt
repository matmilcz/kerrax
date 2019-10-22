cmake_minimum_required(VERSION 3.15.2)

project(IPhysique)

set(MAXSDK_18 "C:/Users/matmi/source/3ds Max 2018 SDK/maxsdk")
set(WINSDK "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.18362.0/um/arm64") # TODO: change to proper path

set(LIB_NAME "IPhysiqueLib")
set(IPHYSIQUE_SRC_PATH "src/IPhysique")
set(DEF_FILE "${IPHYSIQUE_SRC_PATH}/PhyExport.def")

include_directories(PUBLIC "${IPHYSIQUE_SRC_PATH}")
				#"$ENV{MAXSDK_11}/include"
				#"$ENV{MAXSDK_11}/include/CS"

link_directories("$ENV{MAXSDK_11}/lib/x64/Release")

#file (GLOB SOURCES "src/Physique/*.cpp")
#add_library("${LIB_NAME}" SHARED ${SOURCES}
#								 ${DEF_FILE})
						
add_library("${LIB_NAME}" SHARED "${IPHYSIQUE_SRC_PATH}/DllEntry.cpp"
								 "${IPHYSIQUE_SRC_PATH}/PhyExport.cpp"
								 "${IPHYSIQUE_SRC_PATH}/PublishedInterface.cpp"
								 "${IPHYSIQUE_SRC_PATH}/StdHeaders.cpp"
								 "${DEF_FILE}")

set_target_properties("${LIB_NAME}" PROPERTIES LINKER_LANGUAGE CXX)

add_compile_definitions(_RELEASE)
								 
target_link_libraries("${LIB_NAME}" comctl32.lib
									core.lib
									geom.lib
									mesh.lib
									poly.lib
									maxutil.lib
									helpsys.lib
									gup.lib
									paramblk2.lib)