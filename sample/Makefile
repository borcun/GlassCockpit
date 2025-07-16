CXX=g++
CXXFLAGS=-Wall ${INC_DIR} ${EXT_INC_DIR}
SOURCE=Main.cpp AppObject.cpp FLTKRenderWindow.cpp
OBJ=$(SOURCE:.cpp=.o)
EXEC=opengc-sample

INC_DIR=-I ../externals/tinyjpeg -I ../externals/libshape -I ../externals/zlib  -I ../include/config  -I ../include/data -I ../include/font -I ../include/navigation -I ../include/gauge -I ../include/util -I ../externals/FTGL -I ../externals/libxml2/include -I ../externals/freetype/include
EXT_INC_DIR=-I /usr/include/FL

LFLAGS=-Wl,--no-as-needed -lfltk -lfltk_gl -lftgl -lGL -lGLU -lm -lxml2 -lfreetype -lz -ltinyjpeg -lshape -lopengc-config -lopengc-font -lopengc-navigation -lopengc-data -lopengc-gauge
LINK_DIR=-L ../build/externals/zlib -L ../build/externals/libxml2 -L ../build/externals/ftgl -L ../build/externals/freetype -L ../build/externals/tinyjpeg -L ../build/externals/libshape -L ../build/src/config -L ../build/src/navigation -L ../build/src/data -L ../build/src/font -L ../build/src/gauge
EXT_LINK_DIR=-L /usr/lib/x86_64-linux-gnu

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(EXT_LINK_DIR) $(LINK_DIR) $(LFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -rf $(OBJ) $(EXEC) *~
