cmake_minimum_required(VERSION 3.15.2)

project(IPhysique)

set(MAXSDK_18 "C:/Users/matmi/source/3ds Max 2018 SDK/maxsdk")
set(WINSDK "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\arm64") # TODO: change to proper path

set(LIB_NAME "IPhysiqueLib")
set(DEF_FILE "src/IPhysique/PhyExport.def")

include_directories(PUBLIC "src/IPhysique")

link_directories("$ENV{MAXSDK_11}/lib/x64/Release")

#file (GLOB SOURCES "src/Physique/*.cpp")
#add_library("${LIB_NAME}" SHARED ${SOURCES}
#								 ${DEF_FILE})
						
add_library("${LIB_NAME}" SHARED "src/IPhysique/DllEntry.cpp"
								 "src/IPhysique/PhyExport.cpp"
								 "src/IPhysique/PublishedInterface.cpp"
								 "src/IPhysique/StdHeaders.cpp"
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