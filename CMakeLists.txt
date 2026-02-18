cmake_minimum_required(VERSION 3.10)

project(PsvitaSpot)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "PsvitaSpot")
set(VITA_TITLEID  "PSPOT0001")
set(VITA_VERSION  "01.00")

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Application.cpp
    src/Renderer.cpp
    src/InputHandler.cpp
    src/SpotifyAPI.cpp
    src/SpotifyUI.cpp
    src/PlaybackManager.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    vitaGL
    vitashark
    SceShaccCgExt
    SceShaccCg_stub
    taihen_stub
    SceGxm_stub
    SceDisplay_stub
    SceCtrl_stub
    SceNet_stub
    SceNetCtl_stub
    SceHttp_stub
    SceSysmodule_stub
    SceAppUtil_stub
    m
    pthread
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
)
