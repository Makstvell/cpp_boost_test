rmdir /S /Q build
mkdir build 
cd build
cmake -G "Visual Studio 17 2022" ..
cmake --build . --config Release --target Makstvell_TCP
cd Release
Makstvell_TCP.exe
pause