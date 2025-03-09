#include <stdio.h>

// Объявление функций
// Declaring functions
void play_game(int *player_one_score, int *player_two_score);
int handle_player_one_input(char input, int paddle_one_top, int paddle_one_bottom,
                            int min_y, int max_y);
int handle_player_two_input(char input, int paddle_two_top, int paddle_two_bottom,
                            int min_y, int max_y);

int main(void) {
    // Ханение счета игроков
    // Storing player accounts
    int player_one_score = 0;
    int player_two_score = 0;

    // Основной игровой цикл
    // Main game cycle
    while (player_one_score < 21 && player_two_score < 21) {
        play_game(&player_one_score, &player_two_score);
    }
    
    // Поздравление победителя
    // Congratulations to the winner
    if (player_one_score == 21) {
        printf("Congratulations! Player One has won with a score of: %d - %d\n",
               player_one_score, player_two_score);
    } else if (player_two_score == 21) {
        printf("Congratulations! Player Two has won with a score of: %d - %d\n",
               player_two_score, player_one_score);
    }

    return 0;
}

void play_game(int *player_one_score, int *player_two_score) {
    // Позиции ракеток
    // Racket positions
    int paddle_one_top = 5;
    int paddle_one_bottom = 7;
    int paddle_one_x = 3;
    int paddle_two_top = 17;
    int paddle_two_bottom = 19;
    int paddle_two_x = 76;

    // Символы для отображения
    // Symbols to display
    char vertical_border = '|';
    char horizontal_border = '-';
    char empty_space = ' ';
    char ball_symbol = '*';

    // Позиции мяча
    // Ball positions
    int ball_x = 39;
    int ball_y = 12;
    int ball_speed_x = 1;
    int ball_speed_y = 1;

    // Параметры игрового поля
    // Parameters of the playing field
    int max_y = 25;
    int max_x = 80;
    int min_y = 1;

    printf("\033[0d\033[2J"); // Очистка экрана / Clearing the screen
    while (1) {
        printf("\033[0d\033[2J"); // Очистка экрана / Clearing the screen

        // Отображение игрового поля
        // Display of the playing field
        for (int y = 0; y < max_y; y++) {
            for (int x = 0; x < max_x; x++) {
                if (x == 0 || x == max_x - 1) {
                    printf("%c", vertical_border);
                } else if (y == 0 || y == max_y - 1) {
                    printf("%c", horizontal_border);
                } else if (y == ball_y && x == ball_x) {
                    printf("%c", ball_symbol);
                } else if ((y >= paddle_one_top && y <= paddle_one_bottom &&
                            x == paddle_one_x) ||
                           (y >= paddle_two_top && y <= paddle_two_bottom &&
                            x == paddle_two_x)) {
                    printf("%c", vertical_border);
                } else {
                    printf("%c", empty_space);
                }
            }
            printf("\n");
        }

        // Изменение направления мяча
        // Changing the direction of the ball
        if (ball_y == 23)
            ball_speed_y = -1;
        if (ball_y == 1)
            ball_speed_y = 1;

        // Проверка на победу первого игрока
        // Check for the victory of the first player
        if (ball_x == 79) {
            (*player_one_score)++;
            printf("Point for Player One! Current score: %d - %d\n",
                   *player_one_score, *player_two_score);
            break; // Завершение раунда / End of the round
        }
        
        // Проверка на победу второго игрока
        // Check for the victory of the second player
        if (ball_x == 0) {
            (*player_two_score)++;
            printf("Point for Player Two! Current score: %d - %d\n",
                   *player_one_score, *player_two_score);
            break; // Завершение раунда / End of the round
        }

        // Проверка мяча с ракетками
        // Checking the ball with rackets
        if ((paddle_two_top <= ball_y && ball_y <= paddle_two_bottom &&
             ball_x == paddle_two_x - 1))
            ball_speed_x = -1;
        if (paddle_one_top <= ball_y && ball_y <= paddle_one_bottom &&
            ball_x == paddle_one_x + 1)
            ball_speed_x = 1;

        // Текущий счет
        // Current account
        printf("Player One's score: %d\n", *player_one_score);
        printf("Player Two's score: %d\n", *player_two_score);
        
        // Ввод пользователя
        // User Input
        char input = getchar();

        // Ввод для первой ракетки
        // Input for the first racket
        if (handle_player_one_input(input, paddle_one_top, paddle_one_bottom,
                                    min_y, max_y) == 1) {
            paddle_one_top++;
            paddle_one_bottom++;
        } else if (handle_player_one_input(input, paddle_one_top, paddle_one_bottom,
                                           min_y, max_y) == -1) {
            paddle_one_top--;
            paddle_one_bottom--;
        }

        // Ввод для второй ракетки
        // Input for the second racket
        if (handle_player_two_input(input, paddle_two_top, paddle_two_bottom,
                                    min_y, max_y) == 1) {
            paddle_two_top++;
            paddle_two_bottom++;
        } else if (handle_player_two_input(input, paddle_two_top, paddle_two_bottom,
                                           min_y, max_y) == -1) {
            paddle_two_top--;
            paddle_two_bottom--;
        }
        
        // Движение мяча
        // Ball movement
        if (input == '\n') {
            ball_x += ball_speed_x;
            ball_y += ball_speed_y;
        }
    }
}

//Ввод для первой ракетки
//Input for the first racket
int handle_player_one_input(char input, int paddle_one_top, int paddle_one_bottom,
                            int min_y, int max_y) {
    if ((input == 'a' || input == 'A') && paddle_one_top != min_y)
        return -1;
    if ((input == 'z' || input == 'Z') && paddle_one_bottom != max_y - 2)
        return 1;
    return 0;
}

//Ввод для второй ракетки
//Input for the second racket
int handle_player_two_input(char input, int paddle_two_top, int paddle_two_bottom,
                            int min_y, int max_y) {
    if ((input == 'k' || input == 'K') && paddle_two_top != min_y)
        return -1;
    if ((input == 'm' || input == 'M') && paddle_two_bottom != max_y - 2)
        return 1;
    return 0;
}
