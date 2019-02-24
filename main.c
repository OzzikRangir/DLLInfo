#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
    int data;
    char* firstname;
    char* lastname;
    char* number;
    int age;
    char gender;
    struct Node* next;
    struct Node* prev;
};

struct Node* head; // global variable - pointer to head node.


struct Node* newNode(char* firstname,char* lastname,char* number,int age,char gender)
{
    // allocate node
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    // put in the data

    newNode->firstname = firstname;
    newNode->lastname = lastname;
    newNode->number = number;
    newNode->age = age;
    newNode->gender = gender;
    newNode->prev = newNode->next = NULL;
    return newNode;
}

struct Node* getNode(int n)
{
    struct Node* temp = head;
    int count=1;
    while(temp != NULL)
    {
        if(count==n)
        {
            return temp;
        }
        temp = temp->next;
        count++;
    }
};


void sortedInsert(struct Node* newNode)
{
    struct Node* current;
    struct Node** head_ref = &head;
    // if list is empty
    if (*head_ref == NULL)
        *head_ref = newNode;

    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if (strcmp((*head_ref)->lastname, newNode->lastname)>0)
    {
        newNode->next = *head_ref;
        newNode->next->prev = newNode;
        *head_ref = newNode;
    }

    else
    {
        current = *head_ref;

        // locate the node after which the new node
        // is to be inserted
        while (current->next != NULL &&
                strcmp(current->next->lastname ,newNode->lastname)<0)
            current = current->next;

        /* Make the appropriate links */
        newNode->next = current->next;

        // if the new node is not inserted
        // at the end of the list
        if (current->next != NULL)
            newNode->next->prev = newNode;

        current->next = newNode;
        newNode->prev = current;
    }
}

void deleteNode(struct Node* del)
{
    struct Node** head_ref = &head;
    /* base case */
    if (*head_ref == NULL || del == NULL)
        return;

    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;

    /* Change next only if node to be deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;

    /* Change prev only if node to be deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;

    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}


struct Node* searchNode(char* string)
{
    struct Node* temp = head;
    while(temp != NULL)
    {
        if(strcmp(temp->firstname,string)==0)
            return temp;
        if(strcmp(temp->lastname,string)==0)
            return temp;
        if(strcmp(temp->number,string)==0)
            return temp;
        temp = temp->next;
    }
    return 0;
}

//Prints all the elements in linked list in forward traversal order
void printList()
{
    struct Node* temp = head;
    int n=1;
    while(temp != NULL)
    {
        printf("%d: ",n);
        printf("%s ",temp->firstname);
        printf("%s, ",temp->lastname);
        printf("%s, ",temp->number);
        printf("%d, ",temp->age);
        printf("%c\n",temp->gender);
        temp = temp->next;
        n++;
    }
    printf("\n");
}

void printNode(struct Node* node)
{
    struct Node* temp = head;
    int n=1;
    if(node!=0)
    {
        printf("Found:\n");
        while(temp != NULL)
        {
            if(temp==node)
            {
                printf("%d: ",n);
                printf("%s ",temp->firstname);
                printf("%s, ",temp->lastname);
                printf("%s, ",temp->number);
                printf("%d, ",temp->age);
                printf("%c\n",temp->gender);
                return;
            }
            temp = temp->next;
            n++;

        }
    }
    printf("Not found:\n");
}



void addingNode()
{
    char* firstname = malloc( sizeof(char) * ( 32 ) );
    char* lastname = malloc( sizeof(char) * ( 32 ) );
    char* number = malloc( sizeof(char) * ( 10 ) );
    int age;
    char gender;

    printf("Firstname: ");
    scanf("%s",firstname);
    printf("Lastname: ");
    scanf("%s",lastname);
    printf("Number: ");
    scanf("%s",number);
    printf("Age: ");
    scanf("%d",&age);
    printf("Gender: ");
    scanf(" %c",&gender);
    sortedInsert(newNode(firstname,lastname,number,age,gender));
    writeFiles();
}

void editNode(int n)
{
    if(getNode(n)!=0)
    {
        char* firstname = malloc( sizeof(char) * ( 32 ) );
        char* lastname = malloc( sizeof(char) * ( 32 ) );
        char* number = malloc( sizeof(char) * ( 10 ) );
        int age;
        char gender;

        struct Node* temp = getNode(n);
        printf("Editing #%d\n",n);
        printf("Firstname[%s]: ",temp->firstname);
        scanf("%s",firstname);
        printf("Lastname[%s]: ",temp->lastname);
        scanf("%s",lastname);
        printf("Number[%s]: ",temp->number);
        scanf("%s",number);
        printf("Age[%d]: ",temp->age);
        scanf("%d",&age);
        printf("Gender[%c]: ",temp->gender);
        scanf(" %c",&gender);
        temp->firstname=firstname;
        temp->lastname=lastname;
        temp->number=number;
        temp->age=age;
        temp->gender=gender;
        writeFiles();
        return;
    }
    printf("Not found");
}

void deleteMode(int n)
{
    if(getNode(n)!=0)
    {
        deleteNode(getNode(n));
        writeFiles();
    }
}

void printMenu()
{
    printf("Wybierz opcje:\n");
    printf("1. Dodaj\n");
    printf("2. Edytuj\n");
    printf("3. Usun\n");
    printf("4. Wyszukiwanie\n");
    printf("5. Wypisanie wpisow\n");
    printf("Wszystko inne zakoncz\n");
}

void readFiles()
{
    FILE * fp;
    struct Node* temp = head;
    char* firstname = malloc( sizeof(char) * ( 32 ) );
    char* lastname = malloc( sizeof(char) * ( 32 ) );
    char* number = malloc( sizeof(char) * ( 10 ) );
    int age=0;
    char gender=0;


    fp = fopen ("dataM.db", "r");

    while (fscanf(fp,"%s",firstname)==1)
    {
        fscanf(fp,"%s",lastname);
        fscanf(fp,"%s",number);
        fscanf(fp,"%d",&age);
        fscanf(fp," %c",&gender);
        sortedInsert(newNode(firstname,lastname,number,age,gender));
    }
    fclose(fp);

    firstname = malloc( sizeof(char) * ( 32 ) );
    lastname = malloc( sizeof(char) * ( 32 ) );
    number = malloc( sizeof(char) * ( 10 ) );
    age=0;
    gender=0;

    fp = fopen ("dataK.db", "r");

    while (fscanf(fp,"%s",firstname)==1)
    {
        fscanf(fp,"%s",lastname);
        fscanf(fp,"%s",number);
        fscanf(fp,"%d",&age);
        fscanf(fp," %c",&gender);
        sortedInsert(newNode(firstname,lastname,number,age,gender));
    }
    fclose(fp);
}



void writeFiles()
{
    FILE * fp;
    struct Node* temp = head;
    fp = fopen ("dataM.db", "w");
    while(temp != NULL)
    {
        if(temp->gender=='M')
        {
            fprintf(fp,"%s ",temp->firstname);
            fprintf(fp,"%s ",temp->lastname);
            fprintf(fp,"%s ",temp->number);
            fprintf(fp,"%d ",temp->age);
            fprintf(fp,"%c\n",temp->gender);
        }
        temp = temp->next;
    }
    fclose(fp);
    temp = head;
    fp = fopen ("dataK.db", "w");
    while(temp != NULL)
    {
        if(temp->gender=='K')
        {
            fprintf(fp,"%s ",temp->firstname);
            fprintf(fp,"%s ",temp->lastname);
            fprintf(fp,"%s ",temp->number);
            fprintf(fp,"%d ",temp->age);
            fprintf(fp,"%c\n",temp->gender);
        }
        temp = temp->next;
    }
    fclose(fp);
}






int main(int argc, char *argv[])
{
    //Tryb menu


    head = NULL;
    readFiles();
    if(argc == 1)
    {
        int mode;
        int n;
        char string[32];
        while(1)
        {
            printMenu();
            scanf("%d", &mode);
            system("cls");
            switch (mode)
            {
            case 1:
                addingNode();
                break;
            case 2:
                printf("Podaj numer edytowanego rekordu: \n");
                scanf("%d",&n);
                editNode(n);
                break;
            case 3:
                printf("Podaj numer usuwanego rekordu: \n");
                scanf("%d",&n);
                deleteMode(n);
                break;
            case 4:

                printf("Podaj szukany ciag znakow rekordu: \n");
                scanf("%s",string);
                printNode(searchNode(string));
                break;
            case 5:
                printList();
                break;
            default:
                return 0;
                break;
            }
        }
    }
    //Tryb interaktywny
    if(argc == 2)
    {
        if(strcmp(argv[1],"add")==0)
        {
            addingNode();
        }
        if(strcmp(argv[1],"list")==0)
        {
            printList();
        }
    }

    if(argc == 3)
    {
        if(strcmp(argv[1],"search")==0)
        {
            printNode(searchNode(argv[2]));
        }
        if(strcmp(argv[1],"edit")==0)
        {
            editNode(atoi(argv[2]));
        }
        if(strcmp(argv[1],"delete")==0)
        {
            deleteMode(atoi(argv[2]));
        }
    }
}
