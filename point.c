#include <stdio.h>

/*
 Направление мяча по переменной ball_ternd:
 0 - влево, 1 - вправо, 2 - влево вверх, 3 - влево вниз, 4 - вправо вверх, 5 - вправо вниз
 */

void field(int left_racket_up, int right_racket_up, int ball_x, int ball_y, int score_left, int score_right);
int ball_trend_x(int ball_x, int ball_trend);
int ball_trend_y(int ball_y, int ball_trend);

int main() {
    char x, left_up = 'a', left_down = 'z', right_up = 'k', right_down = 'm';
    int left_racket_up = 12, right_racket_up = 12, ball_x = 13, ball_y = 40, score_left = 0, score_right = 0, ball_trend = 0;
    
    field(left_racket_up, right_racket_up, ball_x, ball_y, score_left, score_right);
    
    while (x != 'q'){
        scanf("%c", &x);
        
        if (x == left_up) {
            left_racket_up = left_racket_up - 1;
            if (left_racket_up <= 0) {
                left_racket_up = left_racket_up + 1;
            }
        } else if (x == left_down ) {
            left_racket_up = left_racket_up + 1;
            if (left_racket_up >= 25) {
                left_racket_up = left_racket_up - 1;
            }
        } else if (x == right_up) {
            right_racket_up = right_racket_up - 1;
            if (right_racket_up <= 0) {
                right_racket_up = right_racket_up + 1;
            }
        } else if (x == right_down) {
            right_racket_up = right_racket_up + 1;
            if (right_racket_up >= 25) {
                right_racket_up = right_racket_up - 1;
            }
        }
        
        ball_y = ball_trend_y(ball_y, ball_trend);
        ball_x = ball_trend_x(ball_x, ball_trend);
        
        if(ball_y == 0){
            score_right += 1;
            ball_x = 13;
            ball_y = 40;
            ball_trend = 0;
        } else if (ball_y == 82) {
            score_left += 1;
            ball_x = 13;
            ball_y = 40;
            ball_trend = 1;
        } else if (ball_y == 2 && ball_x == left_racket_up) {
            ball_x -= 1;
            ball_y += 2;
            ball_trend = 4;
        } else if (ball_y == 2 && ball_x == left_racket_up + 1) {
            ball_y += 2;
            ball_trend = 1;
        } else if (ball_y == 2 && ball_x == left_racket_up + 2) {
            ball_x += 1;
            ball_y += 2;
            ball_trend = 5;
        } else if (ball_y == 81 && ball_x == right_racket_up) {
            ball_x -= 1;
            ball_y -= 3;
            ball_trend = 2;
        } else if (ball_y == 81 && ball_x == right_racket_up + 1) {
            ball_y -= 2;
            ball_trend = 0;
        } else if (ball_y == 81 && ball_x == right_racket_up + 2) {
            ball_x += 1;
            ball_y -= 3;
            ball_trend = 3;
        } else if (ball_x == 27) {
            if (ball_trend == 5) {
                ball_x -= 2;
                ball_y += 1;
                ball_trend = 4;
            } else if (ball_trend == 3) {
                ball_x -= 2;
                ball_y -= 1;
                ball_trend = 2;
            }
        } else if (ball_x == 0) {
            if (ball_trend == 4) {
                ball_x += 2;
                ball_y += 1;
                ball_trend = 5;
            } else if (ball_trend == 2) {
                ball_x += 2;
                ball_y -= 1;
                ball_trend = 3;
            }
        }
        
        field(left_racket_up, right_racket_up, ball_x, ball_y, score_left, score_right);
        if (score_left == 21) {
            printf("\033[H\033[J");
            printf("Player 1 WIN\n");
            return 0;
        } else if (score_right == 21) {
            printf("\033[H\033[J");
            printf("Player 2 WIN\n");
            return 0;
        }
    }
    printf("\033[H\033[J");
    return 0;
}


void field(int left_racket_up, int right_racket_up, int ball_x, int ball_y, int score_left, int score_right) {
    printf("\033[H\033[J");
    printf("\n");
    int j = 1;
    for (int i = 0; i < 82; i++) {
        if (i == 10) {
            printf("Player 1: %02d", score_left);
        } if (i == 50){
            printf("Player 2: %02d", score_right);
        }
        printf(" ");
    }
    printf("\n");
    for (int i = 0; i < 82; i++) {
        printf("#");
    }
    printf("\n");
    while (j < 27) {
        for (int i = 0; i < 82; i++){
            if((j >= left_racket_up && j <= left_racket_up + 2) && i == 1) {
                printf("]");
            }
            if((j >= right_racket_up && j <= right_racket_up + 2) && i == 81) {
                printf("[");
            }
            if ((j >= left_racket_up && j <= left_racket_up + 2) && (j >= right_racket_up && j <= right_racket_up + 2) && (i == 1 || i == 2)) {
            } else if ((j >= left_racket_up && j <= left_racket_up + 2) && i == 1) {
            } else if ((j >= right_racket_up && j <= right_racket_up + 2) && i == 1) {
            } else if (i == 0 || i == 81) {
                printf("|");
            } else if (j == ball_x && i == ball_y) {
                printf("●");
            } else {
                printf(" ");
            }
            
        }
        
        j++;
        printf("\n");
    }
    
    for(int i = 0; i < 82; i++){
        printf("#");
    }
    printf("\n");
}

int ball_trend_x(int ball_x, int ball_trend) {
    if (ball_trend == 2 || ball_trend == 4) {
        ball_x -= 1;
    } else  if (ball_trend == 3 || ball_trend == 5) {
        ball_x += 1;
    }
    return ball_x;
}

int ball_trend_y(int ball_y, int ball_trend) {
    if (ball_trend == 0 || ball_trend == 2 || ball_trend == 3) {
        ball_y -= 1;
    } else if (ball_trend == 1 || ball_trend == 4 || ball_trend == 5) {
        ball_y += 1;
    }
    return ball_y;
}

int ball_trend_start(int ball_trend, int score_left, int score_right) {
    if (score_left > score_right && ball_trend == 0) {
        ball_trend = 1;
    } else if (score_left <= score_right && ball_trend == 1){
        ball_trend = 0;
    }
    
    return ball_trend;
}

