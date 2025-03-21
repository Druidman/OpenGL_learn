# Makefile

CXX = g++
CXXFLAGS = -std=c++11 -Wall
LDFLAGS = -lglfw -lGLEW -lGL

SRC_DIR = src
VENDOR_DIR = $(SRC_DIR)/vendor/stb_image
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))
OBJS += $(OBJ_DIR)/stb_image.o

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
    @mkdir -p $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/stb_image.o: $(VENDOR_DIR)/stb_image.cpp
    @mkdir -p $(OBJ_DIR)
    $(CXX) $(CXXFLAGS) -c $< -o $@

clean: 
    rm -rf $(OBJ_DIR) $(TARGET)
                    

.PHONY: all clean