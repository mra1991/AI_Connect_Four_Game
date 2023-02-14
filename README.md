# AI_Connect_Four_Game
Play Connect Four board-game against an AI that uses a minimax algorithm with alpha-beta pruning. A c++ console application.

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
    
    -------------------------------------------------------------------------------------------------------------------------------------------------
    
