# Укажите путь к Qt
QT_DIR = /usr/local/opt/qt

# Укажите путь к заголовочным файлам и библиотекам Qt
QT_INCLUDE = -I$(QT_DIR)/include
QT_LIB = -L$(QT_DIR)/lib -lQt6Core -lQt6Gui -lQt6Widgets

# Укажите путь к компилятору и флагам компиляции
CXX = g++
CXXFLAGS = -std=c++11 -Wall $(QT_INCLUDE)

# Укажите исходные файлы и целевой исполняемый файл
SOURCES = main.cpp SnakeModel.cpp SnakeView.cpp SnakeController.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = SnakeGame

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS) $(QT_LIB)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean