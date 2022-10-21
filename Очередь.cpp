// Очередь.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <locale.h>

int _stateMenu;

void Menu()
{
    printf("Enter action:\n1 - Print queue\n2 - Find data in queue\n3 - Pop first element in queue\n4 - Push new element in queue\n5 - Delete queue\n6 - Save queue in file\n0 - Exit\n");
    _stateMenu = _getch() - 48;
}

struct list
{
    int el;
    list* next;
};

struct queue
{
    list* beg, * end;
};

void qpush(queue* q, int iEl)   //добавить в очередь
{
    list* tmp;
    tmp = new list;
    tmp->next = NULL;
    tmp->el = iEl;
    if (q->end != NULL)
        q->end->next = tmp;
    else
        q->beg = tmp;
    q->end = tmp;
}

int qpop(queue* q, int* iEl) // взять из очереди
{
    if (q->beg == NULL) return 0;
    list* tmp;
    tmp = q->beg;
    *iEl = tmp->el;
    q->beg = tmp->next;
    delete tmp;
    if (q->beg == NULL) q->end = NULL;
    return *iEl;
}

queue* CreateQueue()            //создать очередь
{
    queue* q;
    q = new queue;
    q->beg = NULL;
    q->end = NULL;
    return q;
}

int isQueueEmpty(queue* q)      //проверка очереди на пустоту
{
    if (q->beg == NULL) return 1;
    return 0;
}

int ClearQueue(queue* q)        //очистка очереди
{
    if (q->beg == NULL) return 0;
    list* tmp, * t;
    tmp = q->beg;
    while (tmp->next != NULL)
    {
        t = tmp;
        tmp = t->next;
        delete t;
    }
    q->beg = NULL;
    q->end = NULL;
    return 1;
}

void finddt(queue* q, int data)
{
    queue* tmp = CreateQueue();
    int iEl, c = 1;
    while (!isQueueEmpty(q))
    {
        qpop(q, &iEl);
        if (iEl == data) printf("%d %d\n", iEl, c);
        qpush(tmp, iEl);
        c++;
    }
    while (!isQueueEmpty(tmp))
    {
        qpop(tmp, &iEl);
        qpush(q, iEl);
    }
}

void PrintQueueF(queue* q, FILE* F)       //вывестии очередь на экран
{
    queue* tmp = CreateQueue();
    int iEl;
    while (!isQueueEmpty(q))
    {
        qpop(q, &iEl);
        fprintf(F, "%d ", iEl);
        qpush(tmp, iEl);
    }
    while (!isQueueEmpty(tmp))
    {
        qpop(tmp, &iEl);
        qpush(q, iEl);
    }
}

void PrintQueue(queue* q)       //вывестии очередь на экран
{
    queue* tmp = CreateQueue();
    int iEl;
    while (!isQueueEmpty(q))
    {
        qpop(q, &iEl);
        printf("%d ", iEl);
        qpush(tmp, iEl);
    }
    while (!isQueueEmpty(tmp))
    {
        qpop(tmp, &iEl);
        qpush(q, iEl);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    int number;
    char FILE_NAME[50];

    printf("Input file with queue: ");
    scanf("%s", FILE_NAME);

    queue* q = CreateQueue();
    FILE* fin = fopen(FILE_NAME, "r");

    if (!fin) {
        fprintf(stderr, "Can't open input file!\n");
        return 1;
    }

    while (fscanf(fin, "%d ", &number) == 1)
        qpush(q, number);

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
            if (isQueueEmpty(q))
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            PrintQueue(q);
            printf("\n");

            system("pause");
            system("cls");
            Menu();
            break;
        case 2:
            system("cls");
            if (isQueueEmpty(q))
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printf("Enter data to find: ");
            scanf("%d", &number);
            finddt(q, number);

            system("pause");
            system("cls");
            Menu();
            break;
        case 3:
            system("cls");
            if (isQueueEmpty(q))
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            printf("%d\n", qpop(q, &number));

            system("pause");
            system("cls");
            Menu();
            break;
        case 4:
            system("cls");
            printf("Enter data to push: ");
            scanf("%d", &number);

            qpush(q, number);

            system("pause");
            system("cls");
            Menu();
            break;
        case 5:
            system("cls");
            if (isQueueEmpty(q))
            {
                printf("Queue size = 0\n");
                system("pause");
                system("cls");
                Menu();
                break;
            }

            ClearQueue(q);
            printf("Queue cleared\n");
            system("pause");
            system("cls");
            Menu();
            break;
        case 6:
            system("cls");
            if (isQueueEmpty(q))
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
            PrintQueueF(q, fin);
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
    return 0;
}