mkdir -p build
cd build
#LDFLAGS:  -L/usr/local/opt/qt5/lib
#    CPPFLAGS: -I/usr/local/opt/qt5/include
cmake -DCMAKE_PREFIX_PATH="/usr/local/Cellar/qt5/5.6.1-1/;/usr/local/Cellar/python/2.7.12" -DPYTHON_LIBRARY=/usr/local/Cellar/python/2.7.12/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib ..
make
