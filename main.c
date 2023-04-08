#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ToDo todo;

struct ToDo {
    char data[100];
    todo *next;
    int position;
};

todo *head = NULL;
int size = 0;

/* function */
void listToDo();
void createToDo();
void updateToDo();
void deleteToDo();

void printUI() {
    printf("\n1.List TODO");
    printf("\n2.Creat a TODO");
    printf("\n3.Update TODO");
    printf("\n4.Delete TODO");
    printf("\n5.Exit");
    printf("\n\n-> ");
}

void tbc() {
    char k[10];
    printf("\n\nType Enter to continue....\n");
    fflush(stdin);
    fgets(k,sizeof(k), stdin);
    if(strchr(k, '\n') != NULL) {
        system("clear");
    }
    return;
}

void reallocToDoPosition() {
    todo *current;
    int pos = 1;
    current = head;

    while (current != NULL) {
        current->position = pos++;
        current = current->next;
    }
}

void listToDo() {
    system("clear");

    todo *current;
    current = head;
    if(current == NULL) {
        printf("\n Your ToDo list is empty!\n");
    } else {
        while(current != NULL) {
            printf("\n%d. %s", current->position, current->data);
            current = current->next;
        }
    }

}

void createToDo() {
    // head is null -> make head
    // head not null but next node is null
    todo *tmp,*current;
    char todo;

    system("clear");

    fflush(stdin);
    printf("input your todo: ");
    tmp = malloc(sizeof(todo));
    scanf("%[^\n]s", tmp->data);

    if(head == NULL) {
        tmp->position = 1;
        head = tmp;

    } else {
        current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        tmp->position = current->position + 1;
        current->next = tmp;
        printf("Ok! Marked. \n");
    }
}

void updateToDo() {
    todo *current;
    char todo[100];
    int target;
    int check;

    system("clear");

    if(head == NULL) {
        printf("\n Your ToDo list is empty!\n");
        return;
    }

    listToDo();
    printf("\n\nInput position of TODO that you want to update: ");


    do {
        fflush(stdin);
        check = scanf("%d", &target);
        if(check != 1) {
            while (getchar() != '\n');
            printf("\n Please input Number\n");
        }

    }while (check != 1);

    fflush(stdin);
    printf("Text you want to update: ");
    scanf("%[^\n]s", todo);

    current = head;

    while(current != NULL) {
        if(current->position == target) {
            strcpy(current->data, todo);
            printf("\nUpdated!\n");
            return;
        }
        current = current->next;
    }
    printf("\nNo target position..\n");
}

void deleteToDo() {
    todo *prev,*current;
    int target;
    int check;

    system("clear");

    if(head == NULL) {
        printf("\n Your ToDo list is empty!\n");
        return;
    }

    listToDo();
    printf("\n\nInput position of TODO that you want to delete: ");


    do {
        fflush(stdin);
        check = scanf("%d", &target);
        if(check != 1) {
            while (getchar() != '\n');
            printf("\n Please input Number\n");
        }

    }while (check != 1);

    current = head;

    // handle head
    if(current->position == target) {
        if(current->next == NULL) {
            head = NULL;
        } else {
            current = head;
            head = head->next;
            free(current);
            reallocToDoPosition();
        }
        printf("\nDeleted!\n");
        return;
    }

    current = head->next;
    prev = head;

    while(current != NULL) {
        if(current->position == target) {
            prev->next = current->next;
            printf("\nDeleted!\n");
            reallocToDoPosition();
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("\nNo target position..\n");
}


int main() {
    int choice;
    int check;

    system("clear");

    while(1) {
        printUI();

        fflush(stdin);
        check = scanf("%d", &choice);
        // validate input
        if(check != 1 || (choice > 5 || choice < 1))
        {
            while (getchar() != '\n');
            printf("\n Please input 1-5.\n");
        } else {
            switch (choice) {
                case 1:
                    listToDo();
                    tbc();
                    break;
                case 2:
                    createToDo();
                    break;
                case 3:
                    updateToDo();
                    break;
                case 4:
                    deleteToDo();
                    break;
                case 5:
                    exit(0);
            }
        }
    }

}
