windows:
	$(MINGW_COMPILER) -shared -o bin/armastat.dll src/lib/main.cpp \
		-fPIC \
		-w \
		-Os \
		-std=c++11 \
		-static-libgcc \
		-static-libstdc++ \
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
	g++ -shared -o bin/libarmastat.so src/lib/main.cpp \
		-fPIC \
		-w \
		-Os \
		-std=c++11 \
		-I$(BOOST_DIR) \
		-L$(BOOST_DIR)/stage_linux/lib/ \
		-lboost_system \
		-lboost_thread \
		-lboost_date_time \
		-lpthread \
		-m32

test:
	g++ \
		-o bin/test src/test/main.cpp $(wildcard src/test/**/*.cpp) \
		-std=c++11 \
		-Isrc/lib \
		-Lbin \
		-larmastat \
		-m32
