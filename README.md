## Build Linux
```shell
sudo apt-get update && sudo apt-get install libgtest-dev libboost-all-dev -y
cd "./project_dir"
mkdir build && cd build
cmake ..
# build release
cmake --build . --config Release
# build deb-package
cmake --build . --target package
```

## Build OpenCV
```shell
# Install minimal prerequisites (Ubuntu 18.04 as reference)
sudo apt update && sudo apt install -y g++ wget unzip 
# Download and unpack sources
wget -O opencv.zip https://github.com/opencv/opencv/archive/4.9.zip
unzip opencv.zip
# Create build directory
mkdir -p build && cd build
# Configure
cmake ../opencv-4.9
# Build
cmake --build .
```
## Build Windows
Если используется пакетный менеджер Conan, то перед сборкой проекта необходимо установить флаг CONAN_PKG опции (по умолчанию OFF)
```shell
cmake . -DCONAN_PKG=ON
```
Установка пакетов с использованием версии Conan выше 2 с использованием preset
```shell
cd "./project_dir"
conan install conanfile.txt --build=missing
```
- Создается файл "CMakeUserPresets" в корневой папке
- Создается папка `./build` из-за опции в "conanfile"  
> [layout]  
> cmake_layout

- Создается папка `./build/generators` с нужной фигней для CMake  
Далее из папки проекта вызываем
```shell
cmake --preset conan-default
cmake --build . --preset conan-release
```
