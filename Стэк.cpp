// Стэк.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int _stateMenu;

void Menu()
{
    printf("Enter action:\n1 - Print stack\n2 - Find data in stack\n3 - Pop last element in stack\n4 - Push new element in stack\n5 - Delete stack\n6 - Save stack in file\n0 - Exit\n");
    _stateMenu = _getch() - 48;
}

#define STACK_OVERFLOW  -100
#define STACK_UNDERFLOW -101
#define OUT_OF_MEMORY   -102

typedef int T;

typedef struct Node_tag {
    T value;
    struct Node_tag* next;
} Node_t;

void push(Node_t** head, T value)
{
    Node_t* tmp = (Node_t*)malloc(sizeof(Node_t));
    if (tmp == NULL) {
        exit(STACK_OVERFLOW);
    }
    tmp->next = *head;
    tmp->value = value;
    *head = tmp;
}

T pop(Node_t** head)
{
    Node_t* out;
    T value;
    if (*head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    out = *head;
    *head = (*head)->next;
    value = out->value;
    free(out);
    return value;
}

T peek(const Node_t* head)
{
    if (head == NULL) {
        exit(STACK_UNDERFLOW);
    }
    return head->value;
}

void printStack(const Node_t* head)
{
    printf("stack > ");
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
}

void printStackF(const Node_t* head, FILE* F)
{
    while (head) {
        fprintf(F, "%d ", head->value);
        head = head->next;
    }
}

void finddt(const Node_t* head, int data)
{
    int c = 1;
    while (head)
    {
        if (head->value == data) printf("%d %d\n", head->value, c);
        head = head->next;
        c++;
    }
}

size_t getSize(const Node_t* head)
{
    size_t size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

int main() {
    int number;
    Node_t* head = NULL;
    char FILE_NAME[50];

    printf("Input file with stack: ");
    scanf("%s", FILE_NAME);

    FILE* fin = fopen(FILE_NAME, "r");

    if (!fin) {
        fprintf(stderr, "Can't open input file!\n");
        return 1;
    }

    while (fscanf(fin, "%d ", &number) == 1)
        push(&head, number);

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
            if (getSize(head) == 0)
            {
                printf("Stack size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printStack(head);
            printf("\n");

            system("pause");
            system("cls");
            Menu();
            break;
        case 2:
            system("cls");
            if (getSize(head) == 0)
            {
                printf("Stack size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printf("Enter data to find: ");
            scanf("%d", &number);
            finddt(head, number);

            system("pause");
            system("cls");
            Menu();
            break;
        case 3:
            system("cls");
            if (getSize(head) == 0)
            {
                printf("Stack size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printf("%d\n", pop(&head));

            system("pause");
            system("cls");
            Menu();
            break;
        case 4:
            system("cls");
            printf("Enter data to push: ");
            scanf("%d", &number);

            push(&head, number);

            system("pause");
            system("cls");
            Menu();
            break;
        case 5:
            system("cls");
            if (getSize(head) == 0)
            {
                printf("Stack size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            while (getSize(head) >0) pop(&head);
            printf("Stack cleared\n");

            system("pause");
            system("cls");
            Menu();
            break;
        case 6:
            system("cls");
            if (getSize(head) == 0)
            {
                printf("Stack size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printf("File name: ");
            scanf("%s", FILE_NAME);
            fin = fopen(FILE_NAME, "w");
            printStackF(head, fin);
            printf("Stack saved\n");
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
    return 0;
}