aux_source_directory(. SRC_LIST)

list(REMOVE_ITEM SRC_LIST ./main.cpp)

add_library(crowbase ${SRC_LIST})
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} crowbase)
target_link_libraries(${PROJECT_NAME} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(${PROJECT_NAME} pthread)
target_link_libraries(${PROJECT_NAME} couchbase)
