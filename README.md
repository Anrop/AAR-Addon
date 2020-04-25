# Anrop AAR Addon

[![Build Status](https://travis-ci.org/Anrop/AAR-Addon.svg)](https://travis-ci.org/Anrop/AAR-Addon)

Anrop AAR addon for Arma 3.
This repository handles the game server side of the stats tracking by providing the in-game addon for gathering game related data and the library necessary to provision the data to a backend.

The library is written in C++ and depends on Boost C++.
It has been written to support GCC and MSVC.

## Building

* Conan is used to download required libraries.
* CMake is used to build all binaries.

Make sure you have Python 3 and pip installed.

Install Conan using `pip install conan` before using CMake

### Linux

You can build the project using CLion or other CMake compatible IDEs.

```
mkdir build
cd build
cmake ..
make
```

### Windows

You can also build the project using CLion, Visual Studio or other CMake compatible IDEs.

```
mkdir build
cd build
```

#### 32 bit

```
cmake .. -G "Visual Studio 16 2019" -A Win32
cmake --build .
```

#### 64 bit

```
cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build .
```

## Config

Add a JSON file to your CWD when launching Arma named `aar.json`.
The file should have the following format:
````json
{
	"authorization": "token authorization", // Optional
	"hostname": "api.aar.anrop.se"
}
````
