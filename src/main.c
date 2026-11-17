#include "arraylist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pid;
    const char *name;
} Process;

static void print_int_list(const ArrayList *list, const char *label) {
    printf("%s [size=%zu]: [ ", label, al_size(list));
    for (size_t i = 0; i < al_size(list); i++) {
        int *val = (int *)al_get(list, i);
        printf("%d ", *val);
    }
    printf("]\n");
}

int main(void) {
    printf("=== 1. Тестування базових операцій (int) та розширення пам'яті ===\n");
    ArrayList *nums = al_create(2);
    if (!nums) {
        fprintf(stderr, "Помилка виділення пам'яті\n");
        return 1;
    }

    for (int i = 1; i <= 5; i++) {
        int *v = malloc(sizeof(int));
        *v = i * 10;
        al_add(nums, v);
    }
    print_int_list(nums, "Після add(10..50)");

    printf("\n=== 2. Тестування insert(index, item) ===\n");
    int *ins_head = malloc(sizeof(int));
    *ins_head = 5;
    al_insert(nums, 0, ins_head);

    int *ins_mid = malloc(sizeof(int));
    *ins_mid = 25;
    al_insert(nums, 3, ins_mid);
    print_int_list(nums, "Після insert(0, 5) та insert(3, 25)");

    printf("\n=== 3. Тестування set(index, item) та get(index) ===\n");
    int *new_val = malloc(sizeof(int));
    *new_val = 999;
    int *old_val = (int *)al_get(nums, 2);
    if (al_set(nums, 2, new_val)) {
        free(old_val);
    }
    print_int_list(nums, "Після set(2, 999)");
    printf("Елемент за індексом 2: %d\n", *(int *)al_get(nums, 2));

    printf("\n=== 4. Тестування remove(index) та стиснення пам'яті ===\n");
    while (al_size(nums) > 1) {
        int *removed = (int *)al_remove(nums, 0);
        printf("Видалено елемент: %d (залишилось: %zu)\n", *removed, al_size(nums));
        free(removed);
    }
    print_int_list(nums, "Фінальний стан списку");

    printf("\n=== 5. Перевірка виходу за межі масиву ===\n");
    printf("get(100) == NULL: %s\n", al_get(nums, 100) == NULL ? "OK" : "FAIL");
    printf("set(100) == false: %s\n", !al_set(nums, 100, NULL) ? "OK" : "FAIL");
    printf("remove(100) == NULL: %s\n", al_remove(nums, 100) == NULL ? "OK" : "FAIL");

    while (al_size(nums) > 0) {
        free(al_remove(nums, 0));
    }
    al_destroy(nums);

    printf("\n=== 6. Демонстрація поліморфізму (зберігання різних типів) ===\n");
    ArrayList *mixed = al_create(3);
    int num_item = 42;
    char *str_item = "Kharkiv National University";
    Process proc_item = { .pid = 1337, .name = "systemd" };

    al_add(mixed, &num_item);
    al_add(mixed, str_item);
    al_add(mixed, &proc_item);

    printf("mixed[0] (int): %d\n", *(int *)al_get(mixed, 0));
    printf("mixed[1] (char*): %s\n", (char *)al_get(mixed, 1));
    Process *p = (Process *)al_get(mixed, 2);
    printf("mixed[2] (struct Process): PID=%d, NAME=%s\n", p->pid, p->name);

    al_destroy(mixed);
    printf("\nУсі тести успішно завершено!\n");
    return 0;
}
