# Casino

A casino filled with bots throwing money around where you can play Texas Holdem, Roulette and Jackpot.
Made as a final project for the Object-Oriented Programming course on the second semester of Computer Science studies by me and Kamil Michalak (kmichal4)

## Building

In order to compile the Casino CMake 3.11 is required (unless you remove all tests, then the minimum version is 3.04) and Qt5, which can be downloaded from qt.io or your distro's package manager. On Windows, you'll need to edit this line of code in CMakeLists.txt:
```cmake
set(PATH_TO_QT5 "D:\\Kody\\Qt5\\5.15.2\\msvc2019_64") # path to your Qt5 directory goes here
```
You need to set the `PATH_TO_QT5` variable to your installation. Included .dlls are compatible with MSVC 64-bit, so if you're using a different compiler you'll need to copy them from the `bin` directory in the Qt5 installation. Afterwards it's just
```sh
mkdir build
cd build
cmake ..
cmake --build . --target Casino
```

Have fun!
