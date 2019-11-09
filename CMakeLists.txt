cmake_minimum_required(VERSION 3.15)
project(new_courses C)

set(CMAKE_C_STANDARD 11)

include_directories(src/client)
include_directories(src/common)
include_directories(src/server)
include_directories(src/test)

add_executable(client
        src/client/bmp.c
        src/client/bmp.h
        src/client/client.c
        src/client/client.h
        src/client/couleur.c
        src/client/couleur.h
        src/common/const.h
        src/common/enum.c
        src/common/enum.h
        src/common/json.c
        src/common/json.h
        src/common/tools.c
        src/common/tools.h
        src/common/types.c
        src/common/types.h)

add_executable(server
        src/common/const.h
        src/common/enum.c
        src/common/enum.h
        src/common/json.c
        src/common/json.h
        src/common/tools.c
        src/common/tools.h
        src/common/types.c
        src/common/types.h
        src/server/server.c
        src/server/server.h
        )

