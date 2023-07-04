#include <stdio.h>
#include <ncurses.h>

/*
 Направление мяча по переменной ball_ternd:
 0 - влево, 1 - вправо, 2 - влево вверх, 3 - влево вниз, 4 - вправо вверх, 5 - вправо вниз
 */
void field(int left_racket_up, int right_racket_up, int ball_x, int ball_y, int score_left, int score_right);
int ball_trend_x(int ball_x, int ball_trend);
int ball_trend_y(int ball_y, int ball_trend);
int main() {
    int row, col;
    initscr();
    getmaxyx(stdscr, row, col);
    char x = '\n', left_up = 'a', left_down = 'z', right_up = 'k', right_down = 'm';
    int left_racket_up = 12, right_racket_up = 12;
    int ball_x = 13, ball_y = 40, score_left = 0, score_right = 0, ball_trend = 0;
    field(left_racket_up, right_racket_up, ball_x, ball_y, score_left, score_right);
    halfdelay(1);
    while (x != 'q') {
        x = getch();
        //if (x == ERR) x = '\n';
        if (x == left_up) {
            left_racket_up = left_racket_up - 1;
            if (left_racket_up <= 0) {
                left_racket_up = left_racket_up + 1;
            }
        } else if (x == left_down) {
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
        if (ball_y == 0) {
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
            printw("\033[H\033[J");
            printw("Player 1 WIN\n");
            endwin();
            return 0;
        } else if (score_right == 21) {
            printw("\033[H\033[J");
            printw("Player 2 WIN\n");
            endwin();
            return 0;
        }
    }
    endwin();
    return 0;
}
void field(int left_racket_up, int right_racket_up, int ball_x, int ball_y, int score_left, int score_right) {
    clear();
    printw("\n");
    int j = 1;
    for (int i = 0; i < 82; i++) {
        if (i == 10) {
            printw("Player 1: %02d", score_left);
        } else if (i == 50) {
            printw("Player 2: %02d", score_right);
        }
        printw(" ");
    }
    printw("\n");
    for (int i = 0; i < 82; i++) {
        printw("#");
    }
    printw("\n");
    while (j < 27) {
        for (int i = 0; i < 82; i++) {
            if ((j >= left_racket_up && j <= left_racket_up + 2) && i == 1) {
                printw("]");
            }
            if ((j >= right_racket_up && j <= right_racket_up + 2) && i == 81) {
                printw("[");
            }
            if ((j >= left_racket_up && j <= left_racket_up + 2) && (j >= right_racket_up
                && j <= right_racket_up + 2) && (i == 1 || i == 2)) {
            } else if ((j >= left_racket_up && j <= left_racket_up + 2) && i == 1) {
            } else if ((j >= right_racket_up && j <= right_racket_up + 2) && i == 1) {
            } else if (i == 0 || i == 81) {
                printw("|");
            } else if (j == ball_x && i == ball_y) {
                printw("o");
            } else {
                printw(" ");
            }
        }
        j++;
        printw("\n");
    }
    for (int i = 0; i < 82; i++) {
        printw("#");
    }
    printw("\n");
    refresh();
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
