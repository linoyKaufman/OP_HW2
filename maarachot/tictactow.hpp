#ifndef TTT_HPP
#define TTT_HPP


#define BOARD_SIZE 3
#define MAX_MOVES 9


int validate_input(char *strategy);                
void print_board(char board[BOARD_SIZE][BOARD_SIZE]); 
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player); 
int play_move(char *strategy, char board[BOARD_SIZE][BOARD_SIZE]); 

#endif // TTT_HPP
