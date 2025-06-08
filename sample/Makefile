CXX=g++
CXXFLAGS=-Wall ${INC_DIR} ${EXT_INC_DIR}
SOURCE=Main.cpp AppObject.cpp FLTKRenderWindow.cpp
OBJ=$(SOURCE:.cpp=.o)
EXEC=opengc

INC_DIR=-I ../Source/ImageCodecs -I ../Source/ShapeLib -I ../Source/Base -I ../Source/ImageCodecs  -I ../Source/DataSources -I ../Source/Navigation -I ../Source/Gauges -I ../Util
EXT_INC_DIR=-I /usr/include/FL -I /usr/include/freetype2 -I /usr/include/FTGL -I /usr/include/libxml2

LFLAGS=-Wl,--no-as-needed -lfltk -lfltk_gl -lftgl -lGL -lGLU -lm -lxml2 -lfreetype -lz -ltinyjpeg -lshape -lopengc-base -lopengc-navigation -lopengc-datasources -lopengc-gauges
LINK_DIR=-L ../build/Source/ImageCodecs -L ../build/Source/ShapeLib -L ../build/Source/Base -L ../build/Source/Navigation -L ../build/Source/DataSources -L ../build/Source/Gauges
EXT_LINK_DIR=-L /usr/lib/x86_64-linux-gnu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(EXT_LINK_DIR) $(LINK_DIR) $(LFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC) *~
