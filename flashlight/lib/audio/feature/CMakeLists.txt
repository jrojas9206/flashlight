cmake_minimum_required(VERSION 3.5.1)

# ----------------------------- Dependencies -----------------------------
# CBLAS
if (FL_LIBRARIES_USE_MKL)
  find_package(MKL REQUIRED)
  set(CBLAS_LIBRARIES ${MKL_LIBRARIES})
  set(CBLAS_INCLUDE_DIR ${MKL_INCLUDE_DIR})
  setup_install_find_module(${CMAKE_MODULE_PATH}/FindMKL.cmake)
else ()
  find_package(CBLAS REQUIRED)
endif ()
message(STATUS "CBLAS found (include: ${CBLAS_INCLUDE_DIR}, library: ${CBLAS_LIBRARIES})")

# FFTW
find_package(FFTW3 REQUIRED)
if (FFTW3_FOUND)
  message(STATUS "FFTW found")
  setup_install_find_module(${CMAKE_MODULE_PATH}/FindFFTW3.cmake)
else()
  message(FATAL_ERROR "FFTW not found")
endif()

# OpenMP
if(NOT TARGET OpenMP::OpenMP_CXX)
  find_package(Threads REQUIRED)
  add_library(OpenMP::OpenMP_CXX IMPORTED INTERFACE)
  set_property(TARGET OpenMP::OpenMP_CXX
    PROPERTY INTERFACE_COMPILE_OPTIONS
    ${OpenMP_CXX_FLAGS})
  # Same flag has to be given to the linker
  set_property(TARGET OpenMP::OpenMP_CXX
    PROPERTY INTERFACE_LINK_LIBRARIES
    ${OpenMP_CXX_FLAGS} Threads::Threads)
endif()

# ----------------------------- Lib -----------------------------
target_sources(
  fl-libraries
  PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}/Ceplifter.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Dct.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Derivatives.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Dither.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Mfcc.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Mfsc.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PowerSpectrum.cpp
  ${CMAKE_CURRENT_LIST_DIR}/PreEmphasis.cpp
  ${CMAKE_CURRENT_LIST_DIR}/SpeechUtils.cpp
  ${CMAKE_CURRENT_LIST_DIR}/TriFilterbank.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Windowing.cpp
  )

target_link_libraries(
  fl-libraries
  PRIVATE
  ${CBLAS_LIBRARIES}
  FFTW3::fftw3
  OpenMP::OpenMP_CXX
  )

target_include_directories(
  fl-libraries
  PUBLIC
  ${CBLAS_INCLUDE_DIR}
  )
