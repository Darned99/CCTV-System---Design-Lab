# Minimalna wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(CCTV-System-Design-Lab)

# Standard C++ (można zmienić na C++17 lub nowszy w razie potrzeby)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Ścieżki do katalogów
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CONFIG_DIR ${CMAKE_SOURCE_DIR}/config)
set(DOCS_DIR ${CMAKE_SOURCE_DIR}/docs)
set(LOGS_DIR ${CMAKE_SOURCE_DIR}/logs)
set(TEST_DATA_DIR ${CMAKE_SOURCE_DIR}/test_data)
set(BUILD_DIR ${CMAKE_SOURCE_DIR}/build)

# Włącz OpenCV
find_package(OpenCV REQUIRED)

# Włączenie folderu źródłowego
include_directories(${SRC_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})

# Dodanie źródeł
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)

# Tworzenie pliku wykonywalnego
add_executable(cctv_system ${SOURCES})

# Linkowanie bibliotek OpenCV
target_link_libraries(cctv_system ${OpenCV_LIBS})

# Specjalne instrukcje dla użytkownika
message(STATUS "Aby skonfigurować projekt, upewnij się, że dane testowe znajdują się w ${TEST_DATA_DIR}")
message(STATUS "Pliki konfiguracyjne są w katalogu ${CONFIG_DIR}")
message(STATUS "Ustawienie domyślnego folderu budowania na ${BUILD_DIR}")

# Opcjonalne ustawienia dla build folderu
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})
