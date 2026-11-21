#include "token.h"

int shared_counter = 1000;

int next_extern_token(void) {
    return ++shared_counter;
}

int next_token(void) {
    static int counter = 1000;
    return ++counter;
}

int auto_token(void) {
    int token = 1000;
    return ++token;
}
