#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define MAX 30


struct list{
    char name[MAX];
    char number[MAX];
};

struct phonebook{
    struct list *next;
    int element_cnt;
    int size;
};


struct phonebook* init(int n);
void destroy(struct phonebook *phonebookptr);

bool insert(struct phonebook *phonebookptr, char *name2, char *number);

char *get(struct phonebook *phonebookptr, char *name2);
void print(struct phonebook*);
void dump(struct phonebook *phonebookptr, char *name);


int main(){
    int exit = 0;
    char option;
    struct phonebook *phonebookptr = NULL;
    int n;
    char name[MAX];
    char number[MAX];
    bool ptfa;
    char *foundnumber;
    char filename[MAX];

    while(exit == 0){
        printf("init: i    insert: n    get: g    print: p    dump: d    exit: e\n");
        printf("Enter you option\n");
        scanf("%s", &option);

        if(phonebookptr == NULL && option != 'i'){
            printf("please choose 'i' at first to make phonebook\n");
        }else{
            switch(option){
                case 'i':
                    if(phonebookptr){
                        destroy(phonebookptr);
                    }
                    printf("How many people do you enter?? - \n");
                    scanf("%d", &n);
                    phonebookptr = init(n);
                    printf("Phone book created successfully\n");
                    break;

                case 'n':
                    printf("What is the name?? - \n");
                    scanf("%s", &name);
                    printf("What is the number?? - \n");
                    scanf("%s", &number);
                    ptfa = insert(phonebookptr, name, number);
                    if(ptfa == 1){
                        printf("Inserted successfully\n");
                    } else{
                        printf("unable to insert the data\n");
                    }
                    break;

                case 'g':
                    printf("Enter the name you want to search\n");
                    scanf("%s", name);
                    foundnumber = get(phonebookptr, name);
                    if(foundnumber){
                        printf("Phone number: %s\n",foundnumber);
                    }else{
                        printf("the name is not here\n");
                    }
                    break;

                case 'p':
                    print(phonebookptr);
                    break;

                case 'd':
                    printf("Name the file name: \n");
                    scanf("%s", filename);
                    dump(phonebookptr, filename);
                    printf("The file made successfully\n");
                    break;

                case 'e':
                    exit = 1;
                    break;

                default:
                    printf("Please enter your option correctly\n");

            }
        }
    }
    return 0;
}


struct phonebook* init(int n){
    struct list *next = (struct list*)malloc(sizeof(struct list)*n);
    struct phonebook *phonebookptr = (struct phonebook*)malloc(sizeof(struct phonebook));
    phonebookptr -> next = (struct list*)malloc(sizeof(struct list)*n);
    phonebookptr -> element_cnt = 0;
    phonebookptr -> size = n;
    return phonebookptr;
}

void destroy(struct phonebook *phonebookptr){
    free(phonebookptr);
}


bool insert(struct phonebook *phonebookptr, char *name2, char *number){
    struct list *next = phonebookptr -> next;
    int cnt = phonebookptr -> element_cnt;
    int max = phonebookptr -> size;

    for(int i = 0; i < cnt; i++){
        if(strcmp((next + i) -> name, name2) == 0){
            strcpy((next + i) -> number, number);
            return true;
        }
    }

    if(cnt == max){
        return false;
    }else{
        strcpy((next + cnt) -> name, name2);
        strcpy((next + cnt) -> number, number);
        phonebookptr -> element_cnt++;
        return true;
    }
}




char *get(struct phonebook *phonebookptr, char *name2){
    struct list *next = phonebookptr -> next;
    int element_cnt = phonebookptr -> element_cnt;
    for(int i = 0; i < element_cnt; i++){
        if(strcmp((next + i) -> name, name2) == 0){
            return (next + i) -> number;
        }
    }

    return NULL;
}


void print(struct phonebook *phonebookptr){
    struct list *next = phonebookptr -> next;
    int element_cnt = phonebookptr -> element_cnt;
    for(int i = 0; i < element_cnt; i++){
        printf("%s %s\n", (next + i) -> name, (next + i) -> number);
    }
}

void dump(struct phonebook *phonebookptr, char *name){
    struct list *next = phonebookptr -> next;
    FILE *fpin;
    fpin = fopen(name, "w");
    if(fpin == NULL){
        printf("unable to open the file\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i <phonebookptr -> element_cnt; i++){
        fprintf(fpin, "%s %s\n", (next + i) -> name, (next + i) -> number);
    }
    fclose(fpin);
}