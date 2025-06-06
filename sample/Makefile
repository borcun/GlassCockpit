CXX=clang++
SOURCE=Main.cpp AppObject.cpp FLTKRenderWindow.cpp
OBJ=Main.o AppObject.o FLTKRenderWindow.o
EXEC=sample
INC_DIR=-I ../Source/Base -I ../Source/DataSources -I ../Source/Navigation -I ../Source/Gauges -I ../Util -I /opt/homebrew/opt/fltk/include
EXT_INC_DIR=-I /opt/homebrew/opt/fltk/include -I /opt/homebrew/opt/freetype2/include -I /opt/homebrew/opt/zlib/include -I /opt/homebrew/opt/ftgl/include
LFLAGS=-lfltk -lfltk_gl -lftgl -lfreetype -lz -lopengc-base -lopengc-navigation -lopengc-datasources -lopengc-gauges
LINK_DIR=-L ../build/Source/Base/Debug -L ../build/Source/Navigation/Debug -L ../build/Source/DataSources/Debug -L ../build/Source/Gauges/Debug
EXT_LINK_DIR=-L /opt/homebrew/opt/fltk/lib -L /opt/homebrew/opt/freetype2/lib -L /opt/homebrew/opt/zlib/lib -L /opt/homebrew/opt/ftgl/lib

all:
	${CXX} -c -Wall ${SOURCE} ${INC_DIR} ${EXT_INC_DIR}
	${CXX} ${OBJ} -o -v ${EXEC} ${LFLAGS} ${LINK_DIR} ${EXT_LINK_DIR}

clean:
	rm -rf ${OBJ} ${EXEC} *~
