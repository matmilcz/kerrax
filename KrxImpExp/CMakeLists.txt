cmake_minimum_required(VERSION 3.15.2)

set(CMAKE_CXX_SYSROOT_FLAG_CODE "list(APPEND CMAKE_CXX_SOURCE_FILE_EXTENSIONS meta)")
set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS "C;M;c++;cc;cpp;cxx;mm;CPP;meta")

project(Kerrax CXX)

#set(CMAKE_CXX_SOURCE_FILE_EXTENSIONS "C;M;c++;cc;cpp;cxx;mm;CPP;meta")
message("CMAKE_CXX_SOURCE_FILE_EXTENSIONS ${CMAKE_CXX_SOURCE_FILE_EXTENSIONS}")

set(MAXSDK_18 "$ENV{MAXSDK_18}/maxsdk")
#set(WINSDK "C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10586.0/um/x64")

add_compile_definitions(_RELEASE
						UNICODE
						_UNICODE)

link_directories("${MAXSDK_18}/lib/x64/Release")
				 #"${WINSDK}")

				 
### IPhysiqueLib ###

set(IPHYSIQUE_OUT "IPhysiqueLib")
set(IPHYSIQUE_SRC_PATH "src/IPhysique")
				 
add_library("${IPHYSIQUE_OUT}" SHARED "${IPHYSIQUE_SRC_PATH}/DllEntry.cpp"
									  "${IPHYSIQUE_SRC_PATH}/PhyExport.cpp"
									  "${IPHYSIQUE_SRC_PATH}/PublishedInterface.cpp"
									  "${IPHYSIQUE_SRC_PATH}/StdHeaders.cpp"
									  "${IPHYSIQUE_SRC_PATH}/PhyExport.def")

target_include_directories("${IPHYSIQUE_OUT}" PUBLIC "${IPHYSIQUE_SRC_PATH}"
													 "${MAXSDK_18}/include"
													 "${MAXSDK_18}/include/CS")
									  
set_target_properties("${IPHYSIQUE_OUT}" PROPERTIES LINKER_LANGUAGE CXX)
								 
target_link_libraries("${IPHYSIQUE_OUT}" comctl32.lib
										 core.lib
										 geom.lib
										 mesh.lib
										 poly.lib
										 maxutil.lib
										 gup.lib
										 paramblk2.lib)
										 
										 
### Max3dsImporter ###

set(MAX3DSIMPORTER_OUT "Max3dsImporterLib")
set(META_SRC_PATH "src/Meta")
set(METACPP_SRC_PATH "src/MetaCpp")
set(METAMAXSDK_SRC_PATH "src/MetaMaxSdk")
set(TSTL_SRC_PATH "src/tstl")

set_source_files_properties("${META_SRC_PATH}/3dsInfoDlgInput.meta" PROPERTIES LANGUAGE CXX)

add_library("${MAX3DSIMPORTER_OUT}" SHARED "${META_SRC_PATH}/3dsFileLoader.meta"
										   "${META_SRC_PATH}/3dsImporter.meta"
										   "${META_SRC_PATH}/3dsImporterDefs.meta"
										   "${META_SRC_PATH}/3dsImporterDlgInput.meta"
										   "${META_SRC_PATH}/3dsImporterDlgOutput.meta"
										   "${META_SRC_PATH}/3dsInfoDlgInput.meta"
										   "${META_SRC_PATH}/3dsReadChunk.meta"
										   "${META_SRC_PATH}/File.meta"
										   "${META_SRC_PATH}/ImpExpPathes.meta"
										   "${META_SRC_PATH}/NameAnalyzer.meta"
										   "${META_SRC_PATH}/ObjArrayUtils.meta"
										   "${META_SRC_PATH}/ObjectStats.meta"
										   "${META_SRC_PATH}/RunUIExe.meta"
										   "${META_SRC_PATH}/SceneAnalyzer.meta")

target_include_directories("${MAX3DSIMPORTER_OUT}" PUBLIC "${META_SRC_PATH}"
														  "${METACPP_SRC_PATH}"
														  "${METAMAXSDK_SRC_PATH}"
														  "${TSTL_SRC_PATH}"
														  "${MAXSDK_18}/include"
														  "${MAXSDK_18}/include/CS")

set_target_properties("${MAX3DSIMPORTER_OUT}" PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries("${MAX3DSIMPORTER_OUT}" comctl32.lib
											  core.lib
											  geom.lib
											  mesh.lib
											  mnmath.lib
											  poly.lib
											  maxutil.lib)