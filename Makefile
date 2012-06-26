
all : $(prog) *.cpp *.h

$(prog) : $(prog).o
	g++ -Wall -Wextra -lsfml-graphics -lsfml-window -lsfml-system -lGLU -lGL $< -g -o $@
$(prog).o : $(prog).cpp
	g++ -c -g $< 
