#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <conio.h>
#include "PQueue.h"

int _stateMenu;

void Menu()
{
    printf("Enter action:\n1 - Print queue\n2 - Find priority in queue\n3 - Find data in queue\n4 - Pop first element with highest priority\n5 - Push new element with priority and data\n6 - Delete queue\n7 - Save queue in file\n0 - Exit\n");
    _stateMenu = _getch() - 48;
}

typedef struct PQNODE {
    void* data;
    int priority;
    struct PQNODE* prev;
    struct PQNODE* next;
} PQNode;

static PQNode* pqn_new(void* data, int priority) {
    PQNode* node = (PQNode*)malloc(sizeof(PQNode));
    assert(node);

    node->data = data;
    node->priority = priority;
    node->prev = NULL;
    node->next = NULL;

    return node;
}

struct PQUEUE {
    PQNode* head;
    PQNode* tail;
};

PQueue* pq_new(void) {
    PQueue* pq = (PQueue*)malloc(sizeof(PQueue));
    assert(pq);

    pq->head = NULL;
    pq->tail = NULL;

    return pq;
}

void pq_push(PQueue* pq, void* data, int priority) {
    PQNode* node = pqn_new(data, priority);

    if (pq_is_empty(pq)) {
        pq->head = pq->tail = node;
    }
    else {
        PQNode* last = pq->tail;

        while (last && last->priority > priority) {
            last = last->prev;
        }
        while (last && last->priority == priority && last->data < data)
            last = last->prev;

        if (!last) {
            node->next = pq->head;
            pq->head->prev = node;
            pq->head = node;
        }
        else if (last == pq->tail) {
            node->prev = pq->tail;
            pq->tail->next = node;
            pq->tail = node;
        }
        else {
            node->prev = last;
            node->next = last->next;
            last->next->prev = node;
            last->next = node;
        }
    }
}

void pq_push_copy(PQueue* pq, const void* data, int priority, void* (*data_copy_func)(const void*)) {
    pq_push(pq, data_copy_func(data), priority);
}

void pq_findpr(PQueue* pq, int priority) {
    PQNode* last = pq->head;
    int c = 1;

    while (last && last->priority <= priority)
    {
        if (last->priority == priority)
        {
            printf("%d %d %d\n", (int)last->priority, (int)last->data, c);
        }

        last = last->next;
        c++;
    }
}

void pq_finddt(PQueue* pq, void* data) {
    PQNode* last = pq->head;
    int c = 1;

    while (last && last != pq->tail)
    {
        if (last->data == data)
        {
            printf("%d %d %d\n", (int)last->priority, (int)last->data, c);
        }

        last = last->next;
        c++;
    }

    if (pq->tail->data == data)
    {
        printf("%d %d %d\n", (int)pq->tail->priority, (int)pq->tail->data, c);
    }
}

void* pq_front_data(PQueue* pq) {
    assert(!pq_is_empty(pq));
    return pq->head->data;
}

int pq_front_priority(PQueue* pq) {
    assert(!pq_is_empty(pq));
    return pq->head->priority;
}

void pq_shift(PQueue* pq) {
    assert(!pq_is_empty(pq));

    if (pq->head == pq->tail) {
        free(pq->head);
        pq->head = pq->tail = NULL;
    }
    else {
        PQNode* second = pq->head->next;
        second->prev = NULL;
        free(pq->head);
        pq->head = second;
    }
}

void pq_shift_data(PQueue* pq, void (*data_destructor_func)(void*)) {
    assert(!pq_is_empty(pq));
    data_destructor_func(pq->head->data);
    pq_shift(pq);
}

int pq_is_empty(PQueue* pq) {
    return (pq->head == NULL);
}

unsigned pq_size(PQueue* pq) {
    unsigned size = 0;
    PQNode* node;

    for (node = pq->head; node; node = node->next)
        ++size;

    return size;
}

void pq_free(PQueue* pq) {
    while (!pq_is_empty(pq))
        pq_shift(pq);
}

void pq_free_data(PQueue* pq, void (*data_destructor_func)(void*)) {
    while (!pq_is_empty(pq))
        pq_shift_data(pq, data_destructor_func);
}

void pq_print(PQueue* pq) {
    PQNode* last = pq->head;

    while (last && last != pq->tail)
    {
        printf("%d %d\n", (int)last->priority, (int)last->data);
        last = last->next;
    }
    printf("%d %d\n", (int)pq->tail->priority, (int)pq->tail->data);
}

void pq_printf(PQueue* pq, FILE* f) {
    PQNode* last = pq->head;

    while (last && last != pq->tail)
    {
        fprintf(f, "%d %d\n", (int)last->priority, (int)last->data);
        last = last->next;
    }
    fprintf(f, "%d %d\n", (int)pq->tail->priority, (int)pq->tail->data);
}

int main() {
    int number;
    int mas;
    char FILE_NAME[50];
    printf("Input file with queue: ");
    scanf("%s", FILE_NAME);
    PQueue* queue = pq_new();
    FILE* fin = fopen(FILE_NAME, "r");
    if (!fin) {
        fprintf(stderr, "Can't open input file!\n");
        return 1;
    }

    while (fscanf(fin, "%d ", &number) == 1) {
        fscanf(fin, "%d\n", &mas);
        pq_push(queue, (void*)mas, number);
    }

    if (ferror(fin) | fclose(fin))
        fprintf(stderr, "Error reading input file!\n");
    
    system("pause");
    system("cls");
    Menu();

    while (_stateMenu != 0)
    {
        switch (_stateMenu)
        {
        case 1:
            system("cls");
            if (pq_size(queue) == 0)
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            pq_print(queue);

            system("pause");
            system("cls");
            Menu();
            break;
        case 2:
            system("cls");
            if (pq_size(queue) == 0)
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }
            printf("Enter priority to find: ");
            scanf("%d", &number);

            pq_findpr(queue, number);

            system("pause");
            system("cls");
            Menu();
            break;
        case 3:
            system("cls");
            if (pq_size(queue) == 0)
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }
            printf("Enter data to find: ");
            scanf("%d", &mas);

            pq_finddt(queue, (void*)mas);

            system("pause");
            system("cls");
            Menu();
            break;
        case 4:
            system("cls");
            if (pq_size(queue) == 0)
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }
            printf("%d %d\n", pq_front_priority(queue), pq_front_data(queue));
            pq_shift(queue);

            system("pause");
            system("cls");
            Menu();
            break;
        case 5:
            system("cls");
            printf("Enter priority and data: ");
            scanf("%d %d", &number, &mas);

            pq_push(queue, (void*)mas, number);

            system("pause");
            system("cls");
            Menu();
            break;
        case 6:
            system("cls");
            if (pq_size(queue) == 0)
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            pq_free(queue);

            system("pause");
            system("cls");
            Menu();
            break;
        case 7:
            system("cls");
            if (pq_size(queue) == 0)
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printf("File name: ");
            scanf("%s", FILE_NAME);
            fin = fopen(FILE_NAME, "w");
            pq_printf(queue, fin);
            printf("Queue saved\n");
            fclose(fin);

            system("pause");
            system("cls");
            Menu();
            break;
        case 0:
            exit(EXIT_SUCCESS);
        default:
            system("cls");
            printf("Wrong number");
            system("pause");
            system("cls");
            Menu();
            break;
        }
    }
}