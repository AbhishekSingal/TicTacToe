PROJECT := TicTacToe
COMPILER := clang++
CXXFLAGS := -w -std=c++17 -I./
PATH := ./
BUILD := ./build

${BUILD}/ITicTacToe.o : $(PATH)/source/ITicTacToe.cpp
	@echo
	@echo Building ITicTacToe.o ...
	${COMPILER} ${CXXFLAGS} $(PATH)/source/ITicTacToe.cpp -c -o ${BUILD}/ITicTacToe.o

${BUILD}/ConsoleTicTacToe.o : $(PATH)/source/ConsoleTicTacToe.cpp ${BUILD}/ITicTacToe.o
	@echo
	@echo Building ConsoleTicTacToe.o ...
	${COMPILER} ${CXXFLAGS} $(PATH)/source/ConsoleTicTacToe.cpp -c -o ${BUILD}/ConsoleTicTacToe.o

${BUILD}/ConsoleTicTacToe: ${BUILD}/ConsoleTicTacToe.o
	@echo
	@echo Building ConsoleTicTacToe ...
	${COMPILER} ${CXXFLAGS} ${BUILD}/ConsoleTicTacToe.o ${BUILD}/ITicTacToe.o -o ${BUILD}/ConsoleTicTacToe

build : ${BUILD}/ConsoleTicTacToe ${BUILD}/ITicTacToe.o
	@echo
	@echo ${PROJECT} Builded Successfully 
	@echo

run :
	@echo Running ${BUILD}/ConsoleTicTacToe ...
	@${BUILD}/ConsoleTicTacToe

clean :
	rm -rf ${BUILD} 
	mkdir ${BUILD}

