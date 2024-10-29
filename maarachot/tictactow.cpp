
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_SIZE 3
#define MAX_MOVES 9

// Function to validate the input (a 9-digit unique number containing digits from 1 to 9)
int validate_input(char *strategy) {
    if (strlen(strategy) != 9) return 0;   // Check if the strategy length is exactly 9
    int digits[10] = {0};
    for (int i = 0; i < 9; i++) {
        if (!isdigit(strategy[i]) || strategy[i] == '0') return 0;
        int num = strategy[i] - '0';
        if (digits[num]) return 0; // Array to track digit appearances
        digits[num] = 1;
    }
    return 1;
}


// print the board
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// פונקציה לבדיקת ניצחון
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        // בדיקת שורות
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        // בדיקת עמודות
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    // בדיקת אלכסונים
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0;
}

// פונקציה לביצוע המהלך של התוכנית לפי האסטרטגיה
int play_move(char *strategy, char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < MAX_MOVES; i++) {
        int pos = strategy[i] - '1'; // המרה למיקום בלוח (0-8)
        int row = pos / BOARD_SIZE, col = pos % BOARD_SIZE;
        if (board[row][col] == ' ') { // אם המיקום פנוי
            board[row][col] = 'X';
            printf("%d\n", pos + 1); // הדפסת המיקום ששיחקה (1-9)
            return pos + 1;
        }
    }
    return -1; // אם כל הלוח מלא
}

// פונקציית ראשית
int main(int argc, char *argv[]) {
    if (argc != 2 || !validate_input(argv[1])) {
        printf("Error\n");
        return 1;
    }

    char board[BOARD_SIZE][BOARD_SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char *strategy = argv[1];
    int move_count = 0;

    while (1) {
        play_move(strategy, board); // תוכנית משחקת
        move_count++;
        if (check_win(board, 'X')) { // בדיקת ניצחון
            printf("I win\n");
            break;
        }
        if (move_count == MAX_MOVES) { // בדיקת תיקו
            printf("DRAW\n");
            break;
        }

        int player_move;
        scanf("%d", &player_move); // השחקן משחק
        player_move--; // מעבר לאינדקס מ-0 עד 8

        int row = player_move / BOARD_SIZE, col = player_move % BOARD_SIZE;
        if (player_move < 0 || player_move >= MAX_MOVES || board[row][col] != ' ') {
            printf("Error\n");
            break;
        }
        board[row][col] = 'O';

        if (check_win(board, 'O')) { // בדיקת הפסד
            printf("I lost\n");
            break;
        }
        move_count++;
    }

    return 0;
}


