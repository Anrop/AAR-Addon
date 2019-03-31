file(GLOB aar_SRC
    "*.hpp"
    "*.cpp"
)

add_library(anrop_aar STATIC ${aar_SRC})
target_include_directories(anrop_aar PUBLIC ./)
target_link_libraries(anrop_aar CONAN_PKG::boost CONAN_PKG::nlohmann_json)
