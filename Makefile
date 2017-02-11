windows:
	$(MINGW_COMPILER) -shared -o bin/anrop_aar.dll $(wildcard src/lib/*.cpp) \
		-DTARGET_WINDOWS=1 \
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
	g++ -shared -o bin/libanrop_aar.so $(wildcard src/lib/*.cpp) \
		-DTARGET_LINUX=1 \
		-fPIC \
		-w \
		-Os \
		-std=c++11 \
		-static-libgcc \
		-static-libstdc++ \
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
		-w \
		-Os \
		-std=c++11 \
		-Isrc/lib \
		-Lbin \
		-I$(BOOST_DIR) \
		-L$(BOOST_DIR)/stage_linux/lib/ \
		-lanrop_aar \
		-lboost_system \
		-lboost_thread \
		-lboost_date_time \
		-lpthread \
		-m32
