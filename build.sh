set -e

make windows
make linux
make test
LD_LIBRARY_PATH=bin:$LD_LIBRARY_PATH bin/test
