cmake_minimum_required(VERSION 3.15.2)

project(MaxAscImporter CXX)

set(OUTPUT_NAME "0KrxAscImp.dll")
set(MAXSDK_18 "C:/Users/matmi/source/3ds Max 2018 SDK/maxsdk")
set(KRXIMPEXP "C:/Users/matmi/source/repos/kerraxNew/KrxImpExp")

include_directories(PUBLIC "${MAX_SDK}/include"
						   "${MAX_SDK}/include/CS"
						   "${KRXIMPEXP}/src/Meta"
						   "${KRXIMPEXP}/src/MetaMaxSdk"
						   "${KRXIMPEXP}/src/MetaCpp"
						   "${KRXIMPEXP}/src/tstl")

link_directories("${MAX_SDK}/lib")
						   
add_compile_definitions(WIN32
						_DEBUG
						_WINDOWS
						_USRDLL
						MAXASCIMPORTER_EXPORTS
						_WINDLL
						_UNICODE
						UNICODE)
						
add_library(${OUTPUT_NAME} SHARED "${KRXIMPEXP}/src/Meta/AscImporter.meta")

set_target_properties(${OUTPUT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(${OUTPUT_NAME} comctl32.lib
								core.lib
								geom.lib
								mesh.lib
								poly.lib
								maxutil.lib)