Вызов из папки проекта (корневой)
conan install conanfile.txt --build=missing
-Создается файл "CMakeUserPresets" в корневой папке
-Создается папка build из-за опции в "conanfile" 
	[layout]
	cmake_layout
-Создается папка ./build/generators с нужной фигней для CMake


Вызов из папки проекта (корневой)
cmake --preset conan-default
или из папки ./build
cmake .. --preset conan-default

cmake --build . --preset conan-release
