cmake_minimum_required(VERSION 2.8.8)
project(aar-addon CXX)

# Download automatically, you can also just copy the conan.cmake file
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
   message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
   file(DOWNLOAD "https://github.com/conan-io/cmake-conan/raw/v0.14/conan.cmake"
                 "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

if (WIN32)
   add_compile_options(-D_WIN32_WINNT=0x0601)
   add_compile_options(-DWINVER=0x0601)

   if(CMAKE_SIZEOF_VOID_P EQUAL 4)
      set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
      set(CONAN_ARCH "x86")
   else()
      set(CMAKE_SHARED_LIBRARY_SUFFIX "_x64.dll")
      set(CONAN_ARCH "x86_64")
   endif()
else()
   set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -m32")
   set(CMAKE_SHARED_LINK_FLAGS "${CMAKE_SHARED_LINK_FLAGS} -m32")
   set(CMAKE_SHARED_LIBRARY_SUFFIX ".so")
   set(CONAN_ARCH "x86")
endif()

conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing
                SETTINGS arch=${CONAN_ARCH}
                SETTINGS arch_build=${CONAN_ARCH}
)

add_subdirectory(src/lib)

enable_testing()
add_subdirectory(src/test)
