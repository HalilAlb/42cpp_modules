NAME    := zombie
CXX     := c++
CXXFLAGS:= -Wall -Wextra -Werror -std=c++98 -MMD

SRC     := main.cpp newZombie.cpp randomChumb.cpp Zombie.cpp
OBJDIR  := objs
OBJ     := $(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))
DEPS    := $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(OBJ) -o $@

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re
