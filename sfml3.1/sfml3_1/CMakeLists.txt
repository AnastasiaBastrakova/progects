add_executable(sfml3_1 main.cpp)

target_include_directories(sfml3_1 PRIVATE ${SFML_INCLUDE_DIR})
target_compile_features(sfml3_1 PUBLIC cxx_std_17)
target_compile_definitions(sfml3_1 PRIVATE SFML_STATIC)

target_link_libraries(sfml3_1 ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})