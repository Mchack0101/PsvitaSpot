cmake_minimum_required(VERSION 3.10)

project(PsvitaSpot)

include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "PsvitaSpot")
set(VITA_TITLEID  "PSPOT0001")
set(VITA_VERSION  "01.00")

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    vitaGL
    SceGxm_stub
    SceDisplay_stub
    SceCtrl_stub
)

vita_create_self(${PROJECT_NAME}.self ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} ${PROJECT_NAME}.self
    VERSION ${VITA_VERSION}
    NAME ${VITA_APP_NAME}
)
