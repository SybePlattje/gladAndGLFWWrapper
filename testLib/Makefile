NAME = LIB
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -MMD -MP -std=c++23
LFLAGS = -lglfw -ldl -lpthread -lGL -lm
SRC_DIR = ./../src
OBJ_DIR = ./obj
CXXSOURCES = $(wildcard $(SRC_DIR)/*.cpp)
CSOURCES = ../external/glad/src/glad.c

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(CXXSOURCES))
OBJECTS += $(OBJ_DIR)/glad.o
OBJECTS += $(OBJ_DIR)/main.o
DEPS = $(OBJECTS:.o=.d)
INCLUDE = -I../include -I../externalLib/glad/include/ -I../externalLib

ifdef DEBUG
CXXFLAGS += -g3
endif

ifdef FSAN
CXXFLAGS += -g3 -fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR)/glad.o: ../externalLib/glad/src/glad.c
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	$(MAKE) DEBUG=1

rebug: fclean debug

fsan:
	$(MAKE) FSAN=1

resan: fclean fsan

valgrind: rebug
	valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes --log-file=valgrind.log ./$(NAME)


.PHONY: all clean fclean re debug rebug fsan resan valgrind