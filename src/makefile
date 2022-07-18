CXX_STANDARD = c++17
CXX_FLAGS = -std=${CXX_STANDARD} \
			-Wall \
			-Wextra \
			-Wshadow \
			-Wunreachable-code \
			-Wconversion \
			-flto

CURL = -lcurl
WXCONFIG_LIBS = `wx-config --libs --gl-libs`
WXCONFIG_CXXFLAGS = `wx-config --cxxflags`
LINKER_FLAG = -Wl,--rpath,/usr/local/lib/

TARGET := app

OBJ_FILES := $(patsubst %.cpp, %.o, $(wildcard *.cpp))

$(TARGET): $(OBJ_FILES)
	g++ $^ -o $@ $(CURL) $(WXCONFIG_LIBS) $(LINKER_FLAG)

$(OBJ_DIR)%.o: %.cpp
	g++ $(CXX_FLAGS) $(WXCONFIG_CXXFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	rm -rf $(TARGET) $(OBJ_FILES)