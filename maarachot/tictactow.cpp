#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_SIZE 3
#define MAX_MOVES 9

// Function to validate the input (a 9-digit unique number containing digits from 1 to 9)
int validate_input(char *strategy) {
    if (strlen(strategy) != 9) return 0; // Check if the strategy length is exactly 9
    int digits[10] = {0}; // Array to track digit appearances
    for (int i = 0; i < 9; i++) {
        if (!isdigit(strategy[i]) || strategy[i] == '0') return 0; // Ensure digit is between 1 and 9
        int num = strategy[i] - '0';
        if (digits[num]) return 0; // Check if the digit has already appeared
        digits[num] = 1; // Mark the digit as used
    }
    return 1; // Input is valid
}

// Function to print the Tic-Tac-Toe board
void print_board(char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check if the player has won
int check_win(char board[BOARD_SIZE][BOARD_SIZE], char player) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        // Check rows
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return 1;
        // Check columns
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) return 1;
    }
    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return 1;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return 1;
    return 0; // No win detected
}

// Function to make a move based on the strategy
int play_move(char *strategy, char board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < MAX_MOVES; i++) {
        int pos = strategy[i] - '1'; // Convert character to board index (0-8)
        int row = pos / BOARD_SIZE, col = pos % BOARD_SIZE;
        if (board[row][col] == ' ') { // Check if position is available
            board[row][col] = 'X'; // Place 'X' on the board
            printf("%d\n", pos + 1); // Print the move played (1-9)
            return pos + 1;
        }
    }
    return -1; // If the board is full, no move is made
}

// Main function
int main(int argc, char *argv[]) {
    if (argc != 2 || !validate_input(argv[1])) { // Validate the input argument
        printf("Error\n");
        return 1;
    }

    // Initialize an empty Tic-Tac-Toe board
    char board[BOARD_SIZE][BOARD_SIZE] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    char *strategy = argv[1]; // Strategy provided by the user
    int move_count = 0; // Track the number of moves

    while (1) {
        play_move(strategy, board); // Program's turn to play
        move_count++;
        if (check_win(board, 'X')) { // Check if the program wins
            printf("I win\n");
            break;
        }
        if (move_count == MAX_MOVES) { // Check for a draw
            printf("DRAW\n");
            break;
        }

        int player_move;
        scanf("%d", &player_move); // User's turn to play
        player_move--; // Convert to 0-based index

        int row = player_move / BOARD_SIZE, col = player_move % BOARD_SIZE;
        if (player_move < 0 || player_move >= MAX_MOVES || board[row][col] != ' ') { // Validate move
            printf("Error\n");
            break;
        }
        board[row][col] = 'O'; // Place 'O' for the user's move

        if (check_win(board, 'O')) { // Check if the user wins
            printf("I lost\n");
            break;
        }
        move_count++; // Increase move count
    }

    return 0;
}
