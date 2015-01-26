wget http://www.cmake.org/files/v3.1/cmake-3.1.1-Linux-x86_64.tar.gz
tar xf cmake-3.1.1-Linux-x86_64.tar.gz
export PATH=`pwd`/cmake-3.1.1-Linux-x86_64/bin:$PATH
echo $PATH && cmake --version
sudo apt-add-repository ppa:sonkun/sfml-stable -y
sudo apt-add-repository ppa:boost-latest/ppa -y
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y
sudo add-apt-repository "deb http://llvm.org/apt/precise/ llvm-toolchain-precise-3.5 main" -y
sudo add-apt-repository ppa:libreoffice/ppa -y
sudo apt-get update -q
sudo apt-get install libsfml-dev boost1.55 g++-4.9 clang-3.5 doxygen valgrind --force-yes
if [ "$CXX" = "g++" ]
then
   export CXX="g++-4.9"
   CXXFLAGS=-fprofile-arcs -ftest-coverage
   LDFLAGS=$CXXFLAGS
   CFLAGS=$CXXFLAGS
fi
if [ "$CXX" = "clang++" ]; then export CXX="clang++-3.5"; fi
