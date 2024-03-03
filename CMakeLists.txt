cmake_minimum_required(VERSION 3.12)
project(elschool_api CXX)

# Enable userver libraries that are needed in this project
set(USERVER_FEATURE_PATCH_LIBPQ OFF)
set(USERVER_FEATURE_POSTGRESQL ON CACHE BOOL "" FORCE)

# Compatibility mode: some systems don't support these features
set(USERVER_FEATURE_CRYPTOPP_BLAKE2 OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_GRPC_CHANNELZ OFF CACHE BOOL "" FORCE)
set(USERVER_FEATURE_REDIS_HI_MALLOC ON CACHE BOOL "" FORCE)

# Adding userver dependency
add_subdirectory(third_party/userver)
userver_setup_environment()

add_subdirectory(third_party/gumbo-parser/)

add_subdirectory(third_party/boost/uuid)

set(BOOST_UUID_INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/third_party/boost/uuid/include)

include_directories(src)

# Common sources
add_library(${PROJECT_NAME}_objs OBJECT
        src/handlers/marks/average_marks/average_marks.cpp
        src/handlers/marks/average_marks/average_marks.hpp
        src/handlers/marks/today_marks/today_marks.cpp
        src/handlers/marks/today_marks/today_marks.hpp
        src/handlers/marks/marks_base.cpp
        src/handlers/marks/marks_base.hpp
        src/handlers/users_handler/users_handler.cpp
        src/handlers/users_handler/users_handler.hpp
        src/handlers/token_handler/token_handler.cpp
        src/handlers/token_handler/token_handler.hpp
        src/token_manager/token_manager.cpp
        src/token_manager/token_manager.hpp
        src/token_manager/token_cache.cpp
        src/token_manager/token_cache.hpp
        src/parser/parser.hpp
        src/parser/parser.cpp
        src/user_manager/user_manager.cpp
        src/user_manager/user_manager.hpp
        src/utils/exceptions.h
        src/utils/constants_storage.h
)
target_link_libraries(${PROJECT_NAME}_objs PUBLIC userver-postgresql ${BOOST_UUID_INCLUDE_DIR} gumbo)


# The Service
add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_objs)


# Unit Tests
add_executable(${PROJECT_NAME}_unittest
        utests/token_cache_tests/token_cache_tests.cpp
        utests/parser_tests/parser_tests.cpp
        utests/parser_tests/mocked_time_provider.cpp
)

target_link_libraries(${PROJECT_NAME}_unittest PRIVATE  ${PROJECT_NAME}_objs userver-utest)
add_google_tests(${PROJECT_NAME}_unittest)



# Benchmarks
add_executable(${PROJECT_NAME}_benchmark

)
target_link_libraries(${PROJECT_NAME}_benchmark PRIVATE ${PROJECT_NAME}_objs userver-ubench)
add_google_benchmark_tests(${PROJECT_NAME}_benchmark)


# Functional Tests
include(UserverTestsuite)

userver_testsuite_add_simple()


# Install
include(GNUInstallDirs)

if(DEFINED ENV{PREFIX})
  message(STATUS "Set install prefix: $ENV{PREFIX}")
  file(TO_CMAKE_PATH "$ENV{PREFIX}" PREFIX_PATH)
  set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
endif()

file(GLOB CONFIGS_FILES ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.yaml ${CMAKE_CURRENT_SOURCE_DIR}/configs/*.json)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT ${PROJECT_NAME})
install(FILES ${CONFIGS_FILES} DESTINATION ${CMAKE_INSTALL_SYSCONFDIR}/${PROJECT_NAME} COMPONENT ${PROJECT_NAME})
