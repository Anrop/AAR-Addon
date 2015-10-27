#	GCCVERSION=$($HOST-g++ -E -dM $(mktemp --suffix=.h) | grep __VERSION__ | cut -d ' ' -f 3 | cut -d '"' -f 2) && \
# TODO: Make a nicer way to get gcc version. But only major and minor

FROM rubicks/mingw
RUN apt-get install -y libboost-all-dev gcc-multilib g++-multilib
RUN wget -P /tmp/ http://downloads.sourceforge.net/project/boost/boost/1.59.0/boost_1_59_0.tar.bz2
RUN tar -xf /tmp/boost_1_59_0.tar.bz2 -C /tmp/
RUN export PATH=/usr/i586-mingw32msvc:$PATH
WORKDIR /tmp/boost_1_59_0/
RUN HOST=i586-mingw32msvc && \
	GCCVERSION=4.2 && \
	echo "using gcc : $GCCVERSION : $HOST-g++ \
      : \
      <rc>$HOST-windres \
      <archiver>$HOST-ar \
      <cxxflags>-frandom-seed=boost1 \
      <ranlib>$HOST-ranlib \
;" > user-config.jam && \
  ./bootstrap.sh --without-icu

RUN ./b2 toolset=gcc target-os=windows variant=release \
	threading=multi threadapi=win32 link=static \
	runtime-link=static --user-config=user-config.jam \
	--without-mpi --without-python -sNO_BZIP2=1 \
	--without-context --without-coroutine --without-coroutine2 \
	--prefix=/usr/lib/boost stage

RUN mv stage stage_windows
RUN ./bootstrap.sh
RUN ./b2 address-model=32 link=static \
	--without-python --without-mpi \
	-sNO_BZIP2=1 stage

RUN mv stage stage_linux
CMD /code/docker.sh
