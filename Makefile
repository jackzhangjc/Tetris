CXX = g++
CXXFLAGS = -Wall -MMD -g
OBJECTS = main.o cell.o board.o block.o textdisplay.o posn.o level.o window.o score.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = game

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -lcurses

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC}
