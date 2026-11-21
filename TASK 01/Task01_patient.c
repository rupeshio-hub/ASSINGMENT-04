#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct {
    int systolic;
    int diastolic;
} BloodPressure;

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char name[50];
    int age;
    char phone[16]; /* 15 digits plus '\0' */
    BloodPressure bp;
    Date visit_date;
} Patient;

int addPatient(Patient *p, const char *name, int age, const char *phone,
               int systolic, int diastolic, Date date) {
    if (p == NULL || name == NULL || phone == NULL ||
        age < 0 || age > 130 ||
        strlen(name) >= sizeof p->name ||
        strlen(phone) >= sizeof p->phone ||
        systolic <= 0 || diastolic <= 0) {
        return 0;
    }

    (void)snprintf(p->name, sizeof p->name, "%s", name);
    p->age = age;
    (void)snprintf(p->phone, sizeof p->phone, "%s", phone);
    p->bp.systolic = systolic;
    p->bp.diastolic = diastolic;
    p->visit_date = date;
    return 1;
}

void print_patient(const Patient *p) {
    printf("%s, age %d, phone %s, BP %d/%d, visit %02d/%02d/%04d\n",
           p->name, p->age, p->phone, p->bp.systolic, p->bp.diastolic,
           p->visit_date.day, p->visit_date.month, p->visit_date.year);
}

void sort_by_age(Patient patients[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (patients[j].age < patients[i].age) {
                Patient temp = patients[i];
                patients[i] = patients[j];
                patients[j] = temp;
            }
        }
    }
}

int main(void) {
    Patient patients[MAX_PATIENTS];
    int count = 0;
    Date d1 = {21, 11, 2026}, d2 = {20, 11, 2026};

    if (addPatient(&patients[count], "Arun", 20, "9876543210", 120, 80, d1))
        count++;
    if (addPatient(&patients[count], "Meena", 19, "91234567890", 110, 70, d2))
        count++;

    sort_by_age(patients, count);
    puts("Patients sorted by age:");
    for (int i = 0; i < count; i++) print_patient(&patients[i]);

    printf("sizeof(Patient) = %zu bytes\n", sizeof(Patient));
    return 0;
}
