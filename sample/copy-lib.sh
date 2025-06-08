mkdir -p lib
find ../build/ -name *.so -print0 | xargs -0 cp -t lib/
export LD_LIBRARY_PATH=lib
