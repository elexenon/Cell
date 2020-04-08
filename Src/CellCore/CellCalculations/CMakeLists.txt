cmake_minimum_required(VERSION 3.5)

project(CellCalculations LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(JSONINCLUDE ./thirdParty/jsoncpp-1.9.2)
set(JSONSRC ./thirdParty/jsoncpp-1.9.2/jsoncpp.cpp)

set(ARMAINCLUDE ./thirdParty/armadillo-9.850.1)
set(ARMALIBPATH F:/Dependency/C++/armadillo-9.850.1/lib_win64)

set(PROTOCINCLUDE ./thirdParty/google)
set(PROTOCLIBPATH F:/Dependency/C++/protobuf-3.11.4/cmakeBuild)

include_directories(${JSONINCLUDE} ${ARMAINCLUDE} ${PROTOCINCLUDE})

link_directories(${ARMALIBPATH} ${PROTOCLIBPATH})

link_libraries(${ARMALIBPATH}/blas_win64_MT.lib ${ARMALIBPATH}/lapack_win64_MT.lib
               ${PROTOCLIBPATH}/libprotobuf.a ${PROTOCLIBPATH}/libprotobuf-lite.a ${PROTOCLIBPATH}/libprotoc.a)

add_executable(CellCalculations main.cpp ${JSONSRC}
                                CellBlob.h CellBlob.cpp CellLayer.h CellLayer.cpp CellNet.h CellNet.cpp)
