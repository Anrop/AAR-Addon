MINGW_COMPILER = i586-mingw32msvc-g++
BOOST_DIR = /tmp/boost_1_59_0/

windows:
	$(MINGW_COMPILER) -shared -o armastat.dll main.cpp \
		-w \
		-Os \
		-D_WIN32_WINNT=0x0501 \
		-DWINVER=0x0501 \
		-I$(BOOST_DIR) \
		-L$(BOOST_DIR)/stage_windows/lib/ \
		-lboost_system \
		-lboost_thread_win32 \
		-lboost_date_time \
		-lwsock32 \
		-lws2_32

linux:
	g++ -shared -o armastat.so main.cpp \
		-w \
		-Os \
		-I$(BOOST_DIR) \
		-L$(BOOST_DIR)/stage_linux/lib/ \
		-lboost_system \
		-lboost_thread \
		-lboost_date_time \
		-lpthread \
		-m32
