APP_NAME = ninja
LIB_NAME = ninjalib


CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD -I sfml/include -I src    
FLAG = export LD_LIBRARY_PATH=~/cw-ip-013_keyboardninja/sfml/lib:${LD_LIBRARY_PATH}


PATH_SFML = -L sfml/lib
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

CC = g++
CXX = clang++

BIN_DIR = bin
OBJ_DIR = obj
SRC_DIR = src
SFML_DIR = sfml
SFML_INCLUDE = include


APP_PATH = $(BIN_DIR)/$(APP_NAME)/$(APP_NAME)
LIB_PATH = $(OBJ_DIR)/$(SRC_DIR)/$(LIB_NAME)/$(LIB_NAME).a


SRC_EXT = cpp
HPP_EXT = hpp

APP_SOURCES = $(shell find $(SRC_DIR)/$(APP_NAME) -name '*.$(SRC_EXT)')
APP_OBJECTS = $(APP_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)

LIB_SOURCES = $(shell find $(SRC_DIR)/$(LIB_NAME) -name '*.$(SRC_EXT)')
LIB_OBJECTS = $(LIB_SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/$(SRC_DIR)/%.o)


DEPS = $(APP_OBJECTS:.o=.d) $(LIB_OBJECTS:.o=.d)
DEPS_TEST = $(LIB_SFML_OBJECTS:.o=.d) 

.PHONY: all
all: $(APP_PATH)

-include $(DEPS)
	

$(APP_PATH): $(APP_OBJECTS) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^  -o $@ $(PATH_SFML) $(LIBS)  

$(LIB_PATH): $(LIB_OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.$(SRC_EXT) 
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@ 

.PHONY: clean
clean:
	$(RM) $(APP_PATH) $(LIB_PATH) $(TEST_PATH)
	find $(OBJ_DIR) -name '*.o' -exec $(RM) '{}' \;
	find $(OBJ_DIR) -name '*.d' -exec $(RM) '{}' \;
