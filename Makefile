all: game

game: main.o iGraphics.o keyboard.o mouse.o draw.o point.o color.o object.o circle.o button.o game_details.o game_window.o grid.o box.o image_render.o chess_piece.o chess_board.o chess_cell.o chess_team.o
	g++32  -LOpengl\\lib  main.o iGraphics.o keyboard.o mouse.o draw.o point.o color.o object.o circle.o button.o game_details.o game_window.o grid.o box.o  image_render.o chess_piece.o chess_board.o chess_cell.o chess_team.o -o game -lfreeglut -lGlaux -lopengl32 -lglu32 -lwinmm -lgdi32 -static-libgcc -static-libstdc++ 

main.o: main.cpp
	g++32 -IOpengl\\include -w -c main.cpp

iGraphics.o: iGraphics.cpp
	g++32 -IOpengl\\include -w -c iGraphics.cpp

keyboard.o: keyboard.cpp
	g++32 -IOpengl\\include -w -c keyboard.cpp

mouse.o: mouse.cpp
	g++32 -IOpengl\\include -w -c mouse.cpp

draw.o: draw.cpp
	g++32 -IOpengl\\include -w -c draw.cpp

point.o: point.cpp
	g++32 -IOpengl\\include -w -c point.cpp

color.o: color.cpp
	g++32 -IOpengl\\include -w -c color.cpp

object.o: object.cpp
	g++32 -IOpengl\\include -w -c object.cpp

circle.o: circle.cpp
	g++32 -IOpengl\\include -w -c circle.cpp

game_details.o: game_details.cpp
	g++32 -IOpengl\\include -w -c game_details.cpp

grid.o: grid.cpp
	g++32 -IOpengl\\include -w -c grid.cpp

button.o: button.cpp
	g++32 -IOpengl\\include -w -c button.cpp

box.o: box.cpp
	g++32 -IOpengl\\include -w -c box.cpp

image_render.o: image_render.cpp
	g++32 -IOpengl\\include -w -c image_render.cpp

chess_piece.o: chess_piece.cpp
	g++32 -IOpengl\\include -w -c chess_piece.cpp

chess_board.o: chess_board.cpp
	g++32 -IOpengl\\include -w -c chess_board.cpp

chess_cell.o: chess_cell.cpp
	g++32 -IOpengl\\include -w -c chess_cell.cpp

chess_team.o: chess_team.cpp
	g++32 -IOpengl\\include -w -c chess_team.cpp

game_window.o: game_window.cpp
	g++32 -IOpengl\\include -w -c game_window.cpp
	
run: game
	./game

clean:
	rm -rf *o