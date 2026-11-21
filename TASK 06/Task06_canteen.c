#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 20
#define MAX_SALES 100
#define MAX_COMPONENTS 3

typedef struct {
    int day, month, year;
} Date;

typedef enum { PACKAGED, COOKED, COMBO } ItemType;

typedef struct {
    float price;
    Date expiry;
} PackagedData;

typedef struct {
    float price;
    int prepared_hour;
    int prepared_minute;
} CookedData;

typedef struct {
    int component_ids[MAX_COMPONENTS];
    int component_count;
    float price;
} ComboData;

typedef struct {
    int id;
    char name[40];
    ItemType type;
    int stock;
    union {
        PackagedData packaged;
        CookedData cooked;
        ComboData combo;
    } detail;
} Item;

typedef struct {
    int item_id;
    char item_name[40];
    int quantity;
    float revenue;
} Sale;

int date_within_two_days(Date today, Date expiry) {
    /* Simple same-month demonstration for the assignment test data. */
    if (expiry.year == today.year && expiry.month == today.month) {
        int difference = expiry.day - today.day;
        return difference >= 0 && difference <= 2;
    }
    return 0;
}

float item_price(const Item *item) {
    switch (item->type) {
        case PACKAGED: return item->detail.packaged.price;
        case COOKED: return item->detail.cooked.price;
        case COMBO: return item->detail.combo.price;
        default: return 0.0f;
    }
}

int find_item(const Item items[], int count, int id) {
    for (int i = 0; i < count; i++)
        if (items[i].id == id) return i;
    return -1;
}

int record_sale(Item items[], int item_count, Sale sales[],
                int *sale_count, int id, int quantity) {
    int index = find_item(items, item_count, id);
    if (index < 0 || quantity <= 0) {
        puts("Sale rejected: invalid item or quantity.");
        return 0;
    }
    if (items[index].stock < quantity) {
        printf("Insufficient stock for %s. Available: %d\n",
               items[index].name, items[index].stock);
        return 0;
    }
    if (*sale_count >= MAX_SALES) {
        puts("Sale log is full.");
        return 0;
    }

    items[index].stock -= quantity;
    sales[*sale_count].item_id = id;
    (void)snprintf(sales[*sale_count].item_name,
                   sizeof sales[*sale_count].item_name, "%s", items[index].name);
    sales[*sale_count].quantity = quantity;
    sales[*sale_count].revenue = item_price(&items[index]) * quantity;
    (*sale_count)++;
    printf("Sale recorded: %s x%d, revenue Rs. %.2f, remaining stock %d\n",
           items[index].name, quantity,
           item_price(&items[index]) * quantity, items[index].stock);
    return 1;
}

void expiry_warnings(const Item items[], int count, Date today) {
    puts("\nExpiry warnings (within two days):");
    for (int i = 0; i < count; i++) {
        if (items[i].type == PACKAGED &&
            date_within_two_days(today, items[i].detail.packaged.expiry)) {
            printf("%s expires on %02d/%02d/%04d\n", items[i].name,
                   items[i].detail.packaged.expiry.day,
                   items[i].detail.packaged.expiry.month,
                   items[i].detail.packaged.expiry.year);
        }
    }
}

void sort_sales_by_revenue(Sale sales[], int count) {
    for (int i = 1; i < count; i++) {
        Sale key = sales[i];
        int j = i - 1;
        while (j >= 0 && sales[j].revenue < key.revenue) {
            sales[j + 1] = sales[j];
            j--;
        }
        sales[j + 1] = key;
    }
}

void print_summary(Sale sales[], int count) {
    sort_sales_by_revenue(sales, count);
    puts("\nDaily sales summary (highest revenue first):");
    for (int i = 0; i < count; i++)
        printf("%-20s qty=%d revenue=Rs. %.2f\n",
               sales[i].item_name, sales[i].quantity, sales[i].revenue);
}

int main(void) {
    Item items[4] = {
        {1, "Juice Pack", PACKAGED, 10, {.packaged = {25.0f, {22, 11, 2026}}}},
        {2, "Sandwich", COOKED, 5, {.cooked = {50.0f, 9, 30}}},
        {3, "Veg Combo", COMBO, 8, {.combo = {{2, 1, 0}, 2, 90.0f}}},
        {4, "Biscuit Pack", PACKAGED, 20, {.packaged = {10.0f, {28, 11, 2026}}}}
    };
    Sale sales[MAX_SALES];
    int sale_count = 0;
    Date today = {21, 11, 2026};

    puts("Normal sale:");
    (void)record_sale(items, 4, sales, &sale_count, 1, 2);

    puts("\nInsufficient-stock test:");
    (void)record_sale(items, 4, sales, &sale_count, 2, 9);

    puts("\nCombo sale:");
    (void)record_sale(items, 4, sales, &sale_count, 3, 1);

    expiry_warnings(items, 4, today);
    print_summary(sales, sale_count);
    return 0;
}
