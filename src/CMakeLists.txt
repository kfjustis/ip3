set(SRCS
        filter.cpp
        main.cpp
        matrix.cpp
        tests.cpp
    )

set(HEADERS
        filter.h
        matrix.h
        tests.h
    )

add_executable(${CMAKE_PROJECT_NAME} ${SRCS} ${HEADERS})

target_link_libraries(${CMAKE_PROJECT_NAME} ${OpenCV_LIBS})
