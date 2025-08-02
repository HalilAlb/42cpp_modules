NAME 	:=	megaphone
CXXFLAGS:=	-Wall -Wextra -Werror -std=c++98 -MMD
SRC		:=	megaphone.cpp
OBJS_DIR:=	./objs/
OBJ := $(addprefix $(OBJS_DIR),$(SRC:.cpp=.o))
DEPS := $(OBJ:.o=.d)
CXX		:=	c++

RED		:=	\033[0;31m
ROSE	:=	\033[0;95m
GREEN	:=	\033[0;32m
NC		:=	\033[0m
YELLOW	:=	\033[0;33m
CYAN	:=	\033[1;34m
ERASE	:=	\033[2K\r
BLUE	:=	\033[34m
END		:=	\033[0m

all: title $(NAME) 

title:
	@clear
	@echo "$(YELLOW)==== Making $(NAME) Project ====\n$(NC)"   

$(NAME): $(OBJ)
	@echo "\n > Creating: $(GREEN)$(NAME)...✅$(NC)"
	@$(CXX) $(OBJ) -o $(NAME)
	@echo " >$(CYAN) Done 🔥$(NC)"
	@echo "\n => Run the project:$(ROSE) ./$(NAME)\n$(NC)"

$(OBJS_DIR)%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@printf "$(ERASE) > Compiling: $(CYAN)$@$(NC)$(END)"    
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)
	@echo " >$(RED) Deleting objects files...✅$(NC)"
	@echo " >$(CYAN) Done 🔥\n$(NC)"

fclean: clean
	@rm -rf $(NAME)
	@echo " >$(RED) Deleting $(NAME) file...✅$(NC)"
	@echo " >$(CYAN) Done 🔥\n$(NC)"

re: fclean all

-include $(DEPS)

.PHONY: all title clean fclean re