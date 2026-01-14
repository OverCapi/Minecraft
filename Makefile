#Colors
LIGHT_GRAY	= \033[2m
ORANGE		= \033[1;33m
DARK_GRAY	= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
RESET		= \033[0m

#Forme
BOLD		= \033[1m
ITALIC		= \033[3m
UNDERLINE	= \033[4m
CROSS		= \033[9m
FLASH		= \033[5m
NEGATIF		= \033[7m

SRCS_DIR	 = ./src/
INCLUDES_DIR = ./include/
LIBS_DIR 	 = ./lib/
OBJS_DIR	 = ./objs/

SRCS_CPP		= main.cpp \
				  GLFW_Wrapper/GLFW_Wrapper.cpp \
				  GL_Wrapper/VertexBuffer.cpp \
				  GL_Wrapper/ElementBuffer.cpp \
				  GL_Wrapper/BufferLayout.cpp \
				  GL_Wrapper/VertexArray.cpp \
				  GL_Wrapper/Shader.cpp \
				  GL_Wrapper/Texture2D.cpp
SRCS_C			= glad.c
OBJS			= $(addprefix ${OBJS_DIR}, $(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o))


TARGET = ft_minercaft

COMMON_FLAG = -Wall -Wextra -Werror -g3
FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit

all: ${OBJS_DIR} ${TARGET}

${TARGET}: ${OBJS}
	@c++ ${COMMON_FLAG} -I ${INCLUDES_DIR} -L ${LIBS_DIR} ${OBJS} -lglfw3 ${FRAMEWORKS} -o ${TARGET}
	@echo "${GREEN}${TARGET} is compiled ! ✅${RESET}"

${OBJS_DIR}%.o: ${SRCS_DIR}%.cpp
	@c++ ${COMMON_FLAG} -I ${INCLUDES_DIR} -c $< -o $@
	@echo "${YELLOW}$@ is compiled ! ✅${RESET}"

${OBJS_DIR}%.o: ${SRCS_DIR}%.c
	@cc ${COMMON_FLAG} -I ${INCLUDES_DIR} -c $< -o $@
	@echo "${YELLOW}$@ is compiled ! ✅${RESET}"

${OBJS_DIR}:
	@mkdir -p ./objs
	@mkdir -p ./objs/GLFW_Wrapper
	@mkdir -p ./objs/GL_Wrapper

clean:
	@rm -rf objs
	@echo "${RED}${TARGET} objects are deleted ! 🧹 ${RESET}"

fclean: clean
	@rm -f ${TARGET}

re: fclean all