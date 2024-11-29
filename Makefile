TARGET := a.out
GCC := arm-linux-g++

SRC_DIR := src
INC_DIR := inc

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(SRCS:$(SRC_DIR)/%.cpp=$(SRC_DIR)/%.o)

CFLAGS := -I$(INC_DIR) -std=c++11

${TARGET}: ${OBJS}
	${GCC} $^ -o $@ -pthread
	cp ${TARGET} ~/tftpboot

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	${GCC} $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f ${TARGET}
