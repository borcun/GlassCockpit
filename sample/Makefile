CXX=g++
CXXFLAGS=-Wall ${INC_DIR} ${EXT_INC_DIR}
SOURCE=Main.cpp AppObject.cpp FLTKRenderWindow.cpp
OBJ=$(SOURCE:.cpp=.o)
EXEC=opengc-sample

INC_DIR=-I ../ext/tinyjpeg -I ../ext/libshape -I ../src/config  -I ../src/data -I ../src/font -I ../src/navigation -I ../src/gauge -I ../src/util
EXT_INC_DIR=-I /usr/include/FL -I /usr/include/freetype2 -I /usr/include/FTGL -I /usr/include/libxml2

LFLAGS=-Wl,--no-as-needed -lfltk -lfltk_gl -lftgl -lGL -lGLU -lm -lxml2 -lfreetype -lz -ltinyjpeg -lshape -lopengc-config -lopengc-font -lopengc-navigation -lopengc-data -lopengc-gauge
LINK_DIR=-L ../build/ext/tinyjpeg/Debug -L ../build/ext/libshape/Debug -L ../build/src/config/Debug -L ../build/src/navigation/Debug -L ../build/src/data/Debug -L ../build/src/font/Debug -L ../build/src/gauge/Debug
EXT_LINK_DIR=-L /usr/lib/x86_64-linux-gnu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(EXT_LINK_DIR) $(LINK_DIR) $(LFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC) *~
