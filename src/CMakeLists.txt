set(SRCS
        main.cpp
        matrix.cpp
    )

set(HEADERS
        matrix.h
    )

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})
