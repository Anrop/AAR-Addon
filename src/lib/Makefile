GCC_COMPILER = i586-mingw32msvc-g++
BOOST_INCLUDE = /tmp/boost_1_59_0/
BOOST_LIBS = /tmp/boost_1_59_0/stage/lib/

all:
	$(GCC_COMPILER) -shared -o armastat.dll main.cpp \
		-w \
		-Os \
		-D_WIN32_WINNT=0x0501 \
		-DWINVER=0x0501 \
		-I$(BOOST_INCLUDE) \
		-L$(BOOST_LIBS) \
		-lboost_system \
		-lboost_thread_win32 \
		-lboost_date_time \
		-lwsock32 \
		-lws2_32
