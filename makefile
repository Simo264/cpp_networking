CXX_STANDARD = c++17
CXX_FLAGS = -std=${CXX_STANDARD} \
			-Wall \
			-Wextra \
			-Wshadow \
			-Wstrict-prototypes \
			-Wunreachable-code \
			-Wconversion \
			-flto \


TARGET = "netw"

HTTP_DIR = "./http"
HTTP_CPP = ${HTTP_DIR}/http.cpp
HTTP_OBJ = ${HTTP_DIR}/http.o

OBJECTS = ${TARGET}.o ${HTTP_OBJ}

${TARGET} : ${TARGET}.o ${HTTP_OBJ}
	g++ ${CXX_FLAGS} ${TARGET}.o ${HTTP_OBJ} -o ${TARGET} -lcurl
	make clean

${TARGET}.o : 
	g++ -c ${TARGET}.cpp -o ${TARGET}.o

${HTTP_OBJ} : 
	g++ -c ${HTTP_CPP} -o ${HTTP_OBJ}

.PHONY : clean
clean : 
	rm -rf ${OBJECTS}