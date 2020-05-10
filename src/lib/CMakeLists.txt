file(GLOB aar_SRC
    "*.hpp"
    "*.cpp"
)

add_library(anrop_aar SHARED ${aar_SRC})
target_include_directories(anrop_aar PUBLIC ./)
target_link_libraries(anrop_aar CONAN_PKG::boost CONAN_PKG::nlohmann_json)

add_library(anrop_aar_static STATIC ${aar_SRC})
target_include_directories(anrop_aar_static PUBLIC ./)
target_link_libraries(anrop_aar_static CONAN_PKG::boost CONAN_PKG::nlohmann_json)
