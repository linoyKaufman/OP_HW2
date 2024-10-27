#ifndef TTT_HPP
#define TTT_HPP

// גודל הלוח ומספר מקסימלי של מהלכים
#define BOARD_SIZE 3
#define MAX_MOVES 9

// פונקציות
int validate_input(char *strategy);                 // פונקציה לבדיקת תקינות הקלט
void print_board(char board[BOARD_SIZE][BOARD_SIZE]); // פונקציה להדפסת הלוח
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player); // פונקציה לבדיקת ניצחון
int play_move(char *strategy, char board[BOARD_SIZE][BOARD_SIZE]); // פונקציה לביצוע מהלך לפי האסטרטגיה

#endif // TTT_HPP
