/*
Name: Mohammadreza Abolhassani
Student number: 2034569

This a is a Connect-Four game that lets the player play against the computer(AI)
The AI uses a minimax algorithm with alpha-beta pruning.
Since this game has a huge number of possible configurations, the AI needs a horizon, which is the number of moves it can see ahead.

----------------------------------------------------------------------------------------------------------------------------------------------------
The following is a short introduction and pseudocode of this algorithm from "en.wikipedia.org/wiki/Alpha-beta_pruning" :
Alpha–beta pruning is a search algorithm that seeks to decrease the number of nodes that are evaluated by the minimax algorithm in its search tree.
It is an adversarial search algorithm used commonly for machine playing of two-player games (Tic-tac-toe, Chess, Go, etc.).
It stops evaluating a move when at least one possibility has been found that proves the move to be worse than a previously examined move.
Such moves need not be evaluated further. When applied to a standard minimax tree, it returns the same move as minimax would,
but prunes away branches that cannot possibly influence the final decision.
The algorithm maintains two values, alpha and beta,
which respectively represent the minimum score that the maximizing player is assured of
and the maximum score that the minimizing player is assured of.
Initially, alpha is negative infinity and beta is positive infinity, i.e. both players start with their worst possible score.
Whenever the maximum score that the minimizing player (i.e. the "beta" player) is assured of
becomes less than the minimum score that the maximizing player (i.e., the "alpha" player) is assured of (i.e. beta < alpha),
the maximizing player need not consider further descendants of this node, as they will never be reached in the actual play. (The branch is pruned.)

function alphabeta(node, depth, alpha, beta, maximizingPlayer) is
	if depth = 0 or node is a terminal node then
		return the heuristic value of node
	if maximizingPlayer then
		value := -INFINITY
		for each child of node do
			value := max(value, alphabeta(child, depth - 1, alpha, beta, FALSE))
			alpha := max(alpha, value)
			if alpha >= beta then
				break (* beta cut-off *)
		return value
	else
		value := +INFINITY
		for each child of node do
			value := min(value, alphabeta(child, depth - 1, alpha, beta, TRUE))
			beta := min(beta, value)
			if beta <= alpha then
				break (* alpha cut-off *)
		return value

--------------------------------------------------------------------------------------------------------------------------------------------------------

The programmed is designed so that it can be adapted to other games by rewriting the member functions of the Board class and a few minor modifications.

*/

#include"Board.h" //our Board class can be re-defined for different games
#include <iostream>
#define MAX 10 //Infinity. Some number minimax would never reach 
#define HORIZON 12 //Number of moves the AI sees ahead
using namespace std;

int minimax_alpha(Board*, int, int, int, int*, int*);
int minimax_beta(Board*, int, int, int, int*, int*);
inline void handle_AI_play_X(Board*, int*, int*);
inline void handle_AI_play_O(Board*, int*, int*);
inline void handle_user_play_X(Board*, int*);
inline void handle_user_play_O(Board*, int*);

int main()
{
	cout << "Lets play Connect-Four!" << endl;
	cout << "Do you want to play first? (y/n): ";
	char c; //to hold the answer to above question
	do {
		cin >> c;
	} while (c != 'y' && c != 'n'); //making sure the input is valid
	int m; //always holds the index of the next move; whether the AI is making it or the user.
	int board_counter; //to hold the number of boards we go through every time we search for AI's best move
	Board board; //new board object
	if (c == 'n') { //AI plays first
		cout << "(X) plays first. You are (O)." << endl;
		while (true) {
			//it's the AI's turn and it's playing X
			handle_AI_play_X(&board, &m, &board_counter); //find the best move for AI and store it in m. then perform the move.
			if (board.evaluate() == 1) {
				cout << "The AI wins!";
				break;
			}
			else if (board.is_tie()) {
				cout << "It's a tie!" << endl;
				break;
			}
			//it's the user's turn to play and they're playing O
			handle_user_play_O(&board, &m); //ask the user their next move and store it in m.then perform the move.
			if (board.evaluate() == -1) {
				cout << "You win!";
				break;
			}
			else if (board.is_tie()) {
				cout << "It's a tie!" << endl;
				break;
			}
		}
	}
	else { //the user plays first
		cout << "You are (X)." << endl;
		board.ilustrate();
		while (true) {
			//it's the user's turn to play and they're playing X
			handle_user_play_X(&board, &m); //ask the user their next move and store it in m.then perform the move.
			if (board.evaluate() == 1) {
				cout << "You win";
				break;
			}
			else if (board.is_tie()) {
				cout << "It's a tie!" << endl;
				break;
			}
			//it's the AI's turn and it's playing O.
			handle_AI_play_O(&board, &m, &board_counter); //find the best move for AI and store it in m.then perform the move.
			if (board.evaluate() == -1) {
				cout << "The AI wins!";
				break;
			}
			else if (board.is_tie()) {
				cout << "It's a tie!" << endl;
				break;
			}
		}
	}
	cout << endl << "Written by MRA for Structured Programming course at LaSalle College." << endl;
	system("pause");
	return 0;
}

/* The following function
	is a generic function that will try to maximize the winnig chance of the first player by 
	returning the maximum value among the children nodes of the current node.
	parameters: 
		node : reference to the board object. the current state of the board is the node we are examining.
		depth : we need to know what level of the search tree are we at in order to stop after reaching the horizon.
		alpha1 and beta: the alpha and beta values passed from parent node. Infinty if it's the initial call.
		move: reference to the integer holding next move's index to be filled if it's the initial call.
		board_counter: reference to the integer holding the number of
			analysed boards for the current move so far.
	*/
int minimax_alpha(Board* node, int depth, int alpha1, int beta, int *move, int* board_counter) {
	*board_counter = *board_counter + 1; //started analysing another board 

	if (node->evaluate()) //terminal node with a winner
		return node->evaluate(); //return the heuristic value of node
	if(node->is_tie()) //terminal node with a tie
		return 0; //return the heuristic value of node
	if (depth == HORIZON) //the depth we have reached in the minimax search tree equals the horizon limit. go no further!
		return node->evaluate(); //return the heuristic value of node

	int alpha = alpha1; //alpha needs to be a local variable so we can change it when we find a better one
	int value, best_value = -MAX; //value will hold the next minimax value. best_value is the highest value found yet.
	for (int i = 1; i <= 7; i++) //for every child of the current node
		if (node->can_play(i)) { //making sure move i can be made or i is in fact a child of this node
			node->play_x(i); //moving to the child node
			value = minimax_beta(node, depth + 1, alpha, beta, move, board_counter); //call the minimizer function
			node->undo_play(i); //returning to the parent (current) node
			if (value > best_value) { //a child node with a higher value is found
				best_value = value;
				if (depth == 0) //if this is the initial call
					*move = i; //return the move index as AI's next move
			}
			if (alpha < best_value) //checking if alpha needs to be updated
				alpha = best_value;
			if (alpha >= beta) { //the pruning condition.
				break; //prune this branch. stop examining this node's children.
			}
		}
	return best_value;
}

/* The following function
	is a generic function that will try to maximize the winnig chance of the second player by
	returning the minimum value among the children nodes of the current node.
	parameters:
		node : reference to the board object. the current state of the board is the node we are examining.
		depth : we need to know what level of the search tree are we at in order to stop after reaching the horizon.
		alpha and beta1: the alpha and beta values passed from parent node. Infinty if it's the initial call.
		move: reference to the integer holding next move's index to be filled if it's the initial call.
		board_counter: reference to the integer holding the number of
			analysed boards for the current move so far.
	*/
int minimax_beta(Board* node, int depth, int alpha, int beta1, int *move, int* board_counter) {
	*board_counter = *board_counter + 1; //started analysing another board

	if (node->evaluate()) //teminal node with a winner
		return node->evaluate(); //return the heuristic value of node
	if(node->is_tie()) //terminal node with a tie
		return 0; //return the heuristic value of node
	if (depth == HORIZON) //the depth we have reached in the minimax search tree equals the horizon limit. go no further!
		return node->evaluate(); //return the heuristic value of node

	int beta = beta1; //beta needs to be a local variable so we can change it when we find a better one
	int value, best_value = MAX; //value will hold the next minimax value. best_value is the lowest value found yet. 
	for (int i = 1; i <= 7; i++) //for every child of the current node
		if (node->can_play(i)) { //making sure move i can be made or i is in fact a child of this node
			node->play_o(i); //moving to the child node
			value = minimax_alpha(node, depth + 1, alpha, beta, move, board_counter); //call the maximizer function
			node->undo_play(i); //returning to the parent (current) node
			if (value < best_value) { //a child node with a lower value is found
				best_value = value;
				if (depth == 0) //if this is the initial call
					*move = i; //return the move index as AI's next move
			}
			if (beta > best_value) //checking if beta needs to be updated
				beta = best_value;
			if (alpha >= beta) { //the pruning condition.
				break; //prune this branch. stop examining this node's children.
			}
		}
	return best_value;
}

/*	the following function
	finds the best move the AI can make if it's playing X by callig minimax_alpha function,
		performs the said move and shows the result to the user.
	parameters:
		board : reference to the game board object
		m: reference to the integer holding next move's index
		board_counter: reference to the integer holding the number of
			analysed boards for the current move to pass to minimax function.
*/
inline void handle_AI_play_X(Board* board, int* m, int* board_counter) {
	*board_counter = 0; //no boards analysed yet
	minimax_alpha(board, 0, -MAX, MAX, m, board_counter); //passing variable m by reference to the minimax function
	board->play_x(*m); //making the move
	cout << "The AI chooses: " << *m << endl; //informing the user of the AI's decision
	cout << "Number of boards analysed = " << *board_counter << endl; //or number of times minimax functions were called for a decision to be made
	board->ilustrate();  //printing the current state of the board to std output
}

/*	the following function
	finds the best move the AI can make if it's playing O by callig minimax_beta function,
		performs the said move and shows the result to the user.
	parameters:
		board : reference to the game board object
		m: reference to the integer holding next move's index
		board_counter: reference to the integer holding the number of
			analysed boards for the current move to pass to minimax function.
*/
inline void handle_AI_play_O(Board* board, int* m, int* board_counter) {
	*board_counter = 0; //no boards analysed yet
	minimax_beta(board, 0, -MAX, MAX, m, board_counter); //passing variable m by reference to the minimax function
	board->play_o(*m); //making the move
	cout << "The AI chooses: " << *m << endl; //informing the user of the AI's decision
	cout << "Number of boards analysed = " << *board_counter << endl; //or number of times minimax functions were called for a decision to be made
	board->ilustrate();  //printing the current state of the board to std output
}

/*	the following function
	handles user's input for when the user is playing X,
	performs the appropriate move and shows the result to the user
	parameters:
		board : reference to the game board object
		m: reference to the integer holding next move's index
*/
inline void handle_user_play_X(Board* board, int* m) {
	do {
		cout << "Choose a column that's not full (1-7): ";
		cin >> *m;
	} while (!board->can_play(*m)); //making sure the input is valid
	board->play_x(*m); // actually performing the move
	board->ilustrate(); //printing the current state of the board to std output
}

/*	the following function
	handles user's input for when the user is playing O,
	performs the appropriate move and shows the result to the user
	parameters: 
		board : reference to the game board object
		m: reference to the integer holding next move's index
*/
inline void handle_user_play_O(Board* board, int* m) {
	do {
		cout << "Choose a column that's not full (1-7): ";
		cin >> *m;
	} while (!board->can_play(*m)); //making sure the input is valid
	board->play_o(*m); //actually performing the move
	board->ilustrate(); //printing the current state of the board to std output
}