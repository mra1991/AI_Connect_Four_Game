#ifndef BOARD_H
#define BOARD_H
class Board
{
private:
	int brd[6][7]; //the brd array represents the game board. a cell holds 0 if it's empty, 1 if it's occupied by an X and -1 for an O.
public:
	Board();
	inline int get_cell(int, int); //safe reding access to the private array brd 
	inline void set_cell(int, int, int); //safe writing access to the private array brd
	bool can_play(int); //is this move possible? 
	void play_x(int); //drop an X down a column
	void play_o(int); //drop an O down a column
	void undo_play(int); //take out a piece from atop a column
	bool is_tie(); //are all the columns full?
	int evaluate(); //returns 1 for X's win, -1 for O's win and 0 otherwise(a tie or unfinished game)
	void ilustrate(); //print the board in its current state in the std output
};
#endif

