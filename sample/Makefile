CXX=g++
CXXFLAGS=-Wall ${INC_DIR} ${EXT_INC_DIR}
SOURCE=Main.cpp AppObject.cpp FLTKRenderWindow.cpp
OBJ=$(SOURCE:.cpp=.o)
EXEC=opengc-sample

INC_DIR=-I ../src/tinyjpeg -I ../src/libshape -I ../src/base  -I ../src/data -I ../src/navigation -I ../src/gauge -I ../src/util
EXT_INC_DIR=-I /usr/include/FL -I /usr/include/freetype2 -I /usr/include/FTGL -I /usr/include/libxml2

LFLAGS=-Wl,--no-as-needed -lfltk -lfltk_gl -lftgl -lGL -lGLU -lm -lxml2 -lfreetype -lz -ltinyjpeg -lshape -lopengc-base -lopengc-navigation -lopengc-data -lopengc-gauge
LINK_DIR=-L ../build/src/tinyjpeg -L ../build/src/libshape -L ../build/src/base -L ../build/src/navigation -L ../build/src/data -L ../build/src/gauge
EXT_LINK_DIR=-L /usr/lib/x86_64-linux-gnu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(EXT_LINK_DIR) $(LINK_DIR) $(LFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC) *~
