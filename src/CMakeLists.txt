set(SOURCE_FILES
        main.cpp
        game.cpp game.h
        controller.cpp controller.h)

add_subdirectory(backend)
add_subdirectory(frontend)

# Create the main executable
qt_add_executable(${PROJECT_NAME} main.cpp ${SOURCE_FILES})

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE $<CONFIG:Release>) # this avoids opening console window on Windows in Release mode
endif ()

target_include_directories(${PROJECT_NAME} PRIVATE ${BACKEND_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE lib${PROJECT_NAME}Backend lib${PROJECT_NAME}Frontend)
