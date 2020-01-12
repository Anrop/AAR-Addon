Anrop AAR Addon
===============

[![Build Status](https://travis-ci.org/Anrop/AAR-Addon.svg)](https://travis-ci.org/Anrop/AAR-Addon)

ARMA AAR client project.
This repository handles the game server side of the stats tracking by providing the in-game addon for gathering game related data and the library necessary to provision the data to a backend.

Building
------
The library is written in C++ and depends on BOOST.org.
It has been written using variants of GCC and as such may need some slight modifications for MSVS or other compiler brands.

In order to unify the build environments on all platforms Docker has been used to facilitate this solution.
Configurations for Docker and Docker-Composer has been included and the Makefiles are written with this in mind.

To use simply install Docker and Docker-Compose.  
Please refer to their respective manuals for a complete installation guide.

Once the two pre-requisites have been installed you may simply build the environment with:  
$ docker-compose build

This will install the toolchain necessary to compile the binaries and also prepare all the dependencies such as BOOST.
Finally you can trigger a build of the libraries by running the docker app like so:  
$ docker-compose up

Config
------
Add a JSON file to your CWD when launching Arma named `aar.json`.
The file should have the following format:
````json
{
	"hostname": "api.aar.anrop.se"
}
````
