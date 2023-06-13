# Найдите пакет rapidJSON
find_package(rapidjson CONFIG REQUIRED)

find_package(Doxygen)

set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/Doxyfile)
set(DOXYGEN_CONFIGURED_INPUT ${DOXYGEN_IN})

add_custom_target(doc ALL
	COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIGURED_INPUT}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	VERBATIM
)
# Добавьте исполняемый файл
add_executable(SysCalculator main.cpp)

# Добавьте пути к заголовочным файлам SysCalculator
include_directories(SysCalculator)

# Добавьте исходные файлы SysCalculator в библиотеку SysCalculator
add_library(Calculator SysCalculator/SysCalculator.cpp SysCalculator/include/SysCalculator.hpp)

# Свяжите библиотеку SysCalculator с исполняемым файлом
target_link_libraries(SysCalculator Calculator rapidjson)

set(DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")

# Создать папку для файлов вывода
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Release/out")

set(INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")
file(COPY ${DATA_DIR} DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Release")

# Установка файлов приложения в директорию инсталяции
install(TARGETS SysCalculator DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/config" DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/Release/out" DESTINATION .)


install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/../Documentation/rtf/refman.rtf DESTINATION .)