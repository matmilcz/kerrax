cmake_minimum_required(VERSION 3.15.2)

project(IPhysique)

set(MAXSDK_18 "$ENV{MAXSDK_11}/maxsdk")
#set(WINSDK "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64")

set(LIB_NAME "IPhysiqueLib")
set(IPHYSIQUE_SRC_PATH "src/IPhysique")

include_directories(PUBLIC "${IPHYSIQUE_SRC_PATH}"
						   "${MAXSDK_18}/include"
						   "${MAXSDK_18}/include/CS")

link_directories("${MAXSDK_18}/lib/x64/Release")
				 #"${WINSDK}")
						
add_library("${LIB_NAME}" SHARED "${IPHYSIQUE_SRC_PATH}/DllEntry.cpp"
								 "${IPHYSIQUE_SRC_PATH}/PhyExport.cpp"
								 "${IPHYSIQUE_SRC_PATH}/PublishedInterface.cpp"
								 "${IPHYSIQUE_SRC_PATH}/StdHeaders.cpp"
								 "${IPHYSIQUE_SRC_PATH}/PhyExport.def")

set_target_properties("${LIB_NAME}" PROPERTIES LINKER_LANGUAGE CXX)

add_compile_definitions(_RELEASE
						UNICODE
						_UNICODE)
								 
target_link_libraries("${LIB_NAME}" comctl32.lib
									core.lib
									geom.lib
									mesh.lib
									poly.lib
									maxutil.lib
									gup.lib
									paramblk2.lib)