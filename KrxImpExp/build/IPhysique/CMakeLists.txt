cmake_minimum_required(VERSION 3.15.2)

project(IPhysique)

set(MAXSDK_18 "C:/Users/matmi/source/3ds Max 2018 SDK/maxsdk")
#set(KRXIMPEXP "C:/Users/matmi/source/repos/kerraxNew/KrxImpExp")
set(KRXIMPEXP "../..")

set(LIB_NAME "IPhysiqueLib")
set(DEF_FILE "${KRXIMPEXP}/src/Physique/PhyExport.def")

include_directories(PUBLIC "${KRXIMPEXP}/src/Physique")

link_directories("${MAXSDK_18}/lib/x64/Release")

file (GLOB SOURCES "../../src/Physique/*.cpp")
add_library("${LIB_NAME}" SHARED ${SOURCES})

#add_library("${LIB_NAME}" SHARED "${KRXIMPEXP}/src/Physique/DllEntry.cpp"
#								 "${KRXIMPEXP}/src/Physique/PhyExport.cpp"
#								 "${KRXIMPEXP}/src/Physique/PublishedInterface.cpp"
#								 "${KRXIMPEXP}/src/Physique/StdHeaders.cpp")
								 
target_link_libraries("${LIB_NAME}" core.lib
									geom.lib
									mesh.lib
									poly.lib
									maxutil.lib
									helpsys.lib
									gup.lib
									paramblk2.lib)