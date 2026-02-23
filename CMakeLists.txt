cmake_minimum_required(VERSION 3.12)
project(PsvitaSpot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED ENV{VITASDK})
  message(FATAL_ERROR "VITASDK environment variable not set")
endif()

set(VITASDK $ENV{VITASDK})
set(CMAKE_TOOLCHAIN_FILE "${VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain")

include("${VITASDK}/share/vita.cmake" REQUIRED)

project(PsvitaSpot C CXX)

set(VITA_APP_NAME "PsvitaSpot")
set(VITA_TITLEID  "PSPOT0001")
set(VITA_VERSION  "01.00")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -O2")

add_executable(PsvitaSpot
  src/main.cpp
  src/Application.cpp
  src/Renderer.cpp
  src/InputHandler.cpp
)

target_include_directories(PsvitaSpot PRIVATE include)

target_link_libraries(PsvitaSpot
  vitaGL
  vitashark
  SceShaccCgExt_stub
  SceShaccCg_stub
  taihen_stub
  SceAppMgr_stub
  SceAppUtil_stub
  SceAudio_stub
  SceCtrl_stub
  SceCommonDialog_stub
  SceDisplay_stub
  SceGxm_stub
  SceSysmodule_stub
  SceTouch_stub
  SceNet_stub
  SceNetCtl_stub
  SceHttp_stub
  m
  pthread
)

vita_create_self(PsvitaSpot.self PsvitaSpot)
vita_create_vpk(PsvitaSpot.vpk ${VITA_TITLEID} PsvitaSpot.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
)
