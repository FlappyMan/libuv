cmake_minimum_required( VERSION 3.10.2 )

PROJECT(TestLib)

#find_package(OpenSSL REQUIRED)
#find_package(Threads REQUIRED)

SET(OPENSOUR_LIB_ROOT "/usr/local/UkexServer/lib")
SET(OPENSOUR_LIB_BASELIB "../../BaseLib/")
SET(OPENSOUR_LIB_PROTOCOL "../../Protocol/")

SET(CMAKE_SOURCE_DIR .)
SET(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
set(CMAKE_CXX_FLAGS "-std=c++11")


include_directories(
			${OPENSOUR_LIB_ROOT}/protobuf/include
			${OPENSOUR_LIB_ROOT}/openssl/include
			${OPENSOUR_LIB_ROOT}/jsoncpp/include
	        ${OPENSOUR_LIB_ROOT}/spdlog/include
			${OPENSOUR_LIB_ROOT}/mysqlinc
			${OPENSOUR_LIB_PROTOCOL}
			${OPENSOUR_LIB_BASELIB}
)

link_directories()


aux_source_directory(. SRC_LIST)
add_executable(BackTrade ${SRC_LIST})
target_link_libraries(BackTrade  pthread mysqlclient)
