cmake_minimum_required(VERSION 2.8) # Проверка версии CMake.
									# Если версия установленой программы
									# старее указаной, произайдёт аварийный выход.

project(zip)				# Название проекта

set(SOURCE_LIB zip.c)		# Установка переменной со списком исходников

add_library(zip STATIC ${SOURCE_LIB})# Создание статической библиотеки