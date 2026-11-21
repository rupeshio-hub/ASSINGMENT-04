#include <stdio.h>

struct account {
    int number;
    float balance;
};

void addInterest(struct account *a, float rate) {
    if (a == NULL) return;
    printf("Address inside function: %p\n", (void *)a);
    a->balance += a->balance * rate / 100.0f;
}

/* Alternative: pass by value and return the updated structure. */
struct account addInterest_value(struct account a, float rate) {
    a.balance += a.balance * rate / 100.0f;
    return a;
}

int main(void) {
    struct account list[3] = {{101, 5000.0f}, {102, 12000.0f}, {103, 800.0f}};
    struct account *p = list;

    puts("Pointer-based update:");
    for (int i = 0; i < 3; i++) {
        printf("Address in main: %p\n", (void *)&list[i]);
        addInterest(&list[i], 4.0f);
    }

    puts("Updated accounts:");
    for (int i = 0; i < 3; i++)
        printf("%d %.2f\n", p[i].number, p[i].balance);

    puts("Dot and arrow examples:");
    printf("dot: %d %.2f\n", list[0].number, list[0].balance);
    printf("arrow: %d %.2f\n", p->number, p->balance);

    list[0] = addInterest_value(list[0], 1.0f);
    printf("After value-return alternative: %d %.2f\n",
           list[0].number, list[0].balance);
    return 0;
}
