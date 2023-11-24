

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Course
{ // Created the structure of the course with its data fields
    char Name[50];
    char Code[10];
    char Topics[100];
    int Credits;
    char Department[40];
} Course;

typedef struct Hash_Table_Item // Created the hash table item Structure
{
    int flag;
    Course Data;
} Hash_Table_Item;
int NumElementsQuadratic = 0;
int NumElementsDouble = 0;
double ReHashValue = 0.75;
int QuadraticCollisions = 0;
int DoubleCollisions = 0;
int QSize = 5;                                                      // Quadratic Hash size
int DSize = 5;                                                      // Double Hash size
Hash_Table_Item *QuadraticTable;                                    // Initialized the array of the ReHashed quadratic Hash table
Hash_Table_Item *HDoubleTable;                                      // Initialized the array of the ReHashed double Hash table
int String_Hashing(char *x);                                        // Function prototype
Hash_Table_Item *DoubleHash(Course, Hash_Table_Item *);             // Function prototype
void ReadFile();                                                    // Function prototype
void ViewMenu();                                                    // Function prototype
Hash_Table_Item *QuadraticHash(Course C, Hash_Table_Item *);        // Function prototype
int PrimeSize(int Count);                                           // Function prototype
int IsPrime(int x);                                                 // Function prototype
void initialize_arrays(Hash_Table_Item *);                          // Function prototype
int Prev_Prime();                                                   // Function prototype
int H2(char *);                                                     // Function prototype
void PrintHashes(Hash_Table_Item *);                                // Function prototype
void Print_Tables_Info();                                           // Function prototype
void Search_For_Word(Hash_Table_Item *HT, int size, char *Name);    // Function prototype
void Delete_From_Tables(char *Name, Hash_Table_Item *HT, int size); // Function prototype
void PrintToOut();                                                  // Function prototype
Hash_Table_Item *ReHashQuad(Course C, Hash_Table_Item *, int);      // Function prototype
Hash_Table_Item *ReHashDouble(Course C, Hash_Table_Item *, int);    // Function prototype
int main()
{
    QuadraticTable = (Hash_Table_Item *)malloc(sizeof(Hash_Table_Item));
    HDoubleTable = (Hash_Table_Item *)malloc(sizeof(Hash_Table_Item));
    initialize_arrays(HDoubleTable);
    initialize_arrays(QuadraticTable);
    ViewMenu();
    return 0;
}
int String_Hashing(char *x) // Function to Hash the course names
{
    long value = 0;
    while (*x != '\0')
    {
        value = (value << 5) + *(x++);
    }

    return abs(value);
}
int H2(char *x)
{
    return Prev_Prime(DSize) - (String_Hashing(x) % Prev_Prime(DSize));
}
Hash_Table_Item *DoubleHash(Course C, Hash_Table_Item *HT) // Hash function to consider the index of insertion
{
    if (((double)(1 + NumElementsDouble) / QSize) > ReHashValue)
    {
        int oldSize = DSize;
        DSize = PrimeSize(DSize * 2);
        HDoubleTable = ReHashDouble(C, HDoubleTable, oldSize);
    }
    int Hash1 = String_Hashing(C.Name);
    int Hash2 = H2(C.Name);
    int index = Hash1;
    int i = 0;
    while (HT[index].flag == 1)
    {
        if (strcmp(HT[index].Data.Name, C.Name) == 0)
        {
            printf("\nCourse already presents \n");
            return HT;
        }
        index = (index + Hash2 * i++) % QSize;
        if (index == Hash1)
        {
            printf("\n Insertion has failed \n");
            return HT;
        }
    }
    HT[index].Data = C;
    HT[index].flag = 1;
    NumElementsDouble++;
    printf("\nCourse %s is Inserted\n", C.Name);
    return HT;
}
void ReadFile() // Function to Read the data from the file
{
    int Count = 0; // Counter to count the number of courses read

    FILE *in;
    in = fopen("offered_courses.txt", "r");
    // Initialized the data fields used to create each Course Structure
    char line[200];
    char Name[50];
    char code[10];
    char *Department;
    char topics[100];
    char *token;
    Course Temp;
    while (fgets(line, 200, in) != NULL) // While loop will stop when we reach the end of the file
    {
        // Tokenization for every line to get the data properly
        printf("%s", line);
        token = strtok(line, ":");
        strcpy(Name, token);
        token = strtok(NULL, "#");
        int Credits = atoi(token);
        token = strtok(NULL, "#");
        strcpy(code, token);
        token = strtok(NULL, "/");
        Department = token;
        token = strtok(NULL, "\n");
        strcpy(topics, token);
        Count++;
        strcpy(Temp.Name, Name);
        strcpy(Temp.Code, code);
        strcpy(Temp.Department, Department);
        Temp.Credits = Credits;
        strcpy(Temp.Topics, topics);
        QuadraticTable = QuadraticHash(Temp, QuadraticTable);
        HDoubleTable = DoubleHash(Temp, HDoubleTable);
    }
    QSize = PrimeSize(Count);
    DSize = QSize;

    printf("\n");
}
void ViewMenu() // Function of the menu
{
    Course C;
    int choice;
    char *token;
    int Table;
    while (choice != 9)
    {
        printf("1-Print hashed tables (including empty spots).\n");
        printf("2-Print out table size and the load factor.\n");
        printf("3-Print out the used hash functions. \n");
        printf("4-Insert a new record to hash table (insertion will be done on both hash tables).\n");
        printf("5-Search for a specific word (specify which table to search in).\n");
        printf("6-Delete a specific record (from both tables).\n");
        printf("7-Compare between the two methods in terms of number of collisions occurred.\n");
        printf("8-Save hash table back to a file named saved_courses.txt (of the double hashing)\n");
        printf("9-Exit!\n");
        printf("-----------------------------\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);
        printf("-----------------------------\n");
        switch (choice)
        {
        case 1:
            ReadFile();
            printf("\n---------------------------------------\nPrinted the Hash tables!\n---------------------------------------\n\n");
            break;
        case 2:
            Print_Tables_Info(); // Function call
            printf("\n---------------------------------------\nPrinted size and load factor!\n---------------------------------------\n\n");
            break;
        case 3:
            printf("Used Shifting hashing\n");
            printf("\n---------------------------------------\nPrinted the used functions!\n---------------------------------------\n\n");
            break;
        case 4:
            printf("Enter the name of the course : \n");
            getchar();
            gets(token);
            strcpy(C.Name, strtok(token, "\n"));
            printf("Enter the code of the course : \n");
            getchar();
            gets(token);
            strcpy(C.Code, strtok(token, "\n"));
            printf("Enter the Topics of the course(each two separated by ", ") : \n");
            getchar();
            gets(token);
            strcpy(C.Topics, strtok(token, "\n"));
            printf("Enter the Department of the course : \n");
            getchar();
            gets(token);
            strcpy(C.Department, strtok(token, "\n"));
            printf("Enter the credits of the course : \n");
            scanf("%d", &(C.Credits));
            QuadraticTable = QuadraticHash(C, QuadraticTable); // Function call
            HDoubleTable = DoubleHash(C, HDoubleTable);        // Functon call
            printf("\n---------------------------------------\nInserted a new record!\n---------------------------------------\n\n");
            break;
        case 5:
            printf("Enter the name of the course : \n");
            getchar();
            gets(token);
            token = strtok(token, "\n");
            printf("You want to find in : \n1-Quadratic Table.\n2-Double Table\n");
            scanf("%d", &Table);
            if (Table == 1)
                Search_For_Word(QuadraticTable, QSize, token); // Function call
            else if (Table == 2)
                Search_For_Word(HDoubleTable, DSize, token); // Function call
            else
                printf("Error!\n");
            printf("\n---------------------------------------\nSearch is done!\n---------------------------------------\n\n");
            break;
        case 6:
            printf("Enter the name of the course : \n");
            getchar();
            gets(token);
            token = strtok(token, "\n");
            Delete_From_Tables(token, QuadraticTable, QSize);
            Delete_From_Tables(token, HDoubleTable, DSize);
            printf("\n---------------------------------------\nDeletion is done!\n---------------------------------------\n\n");
            break;
        case 7:
            printf("Collisions in Double : %d \nCollisions in Quadratic : %d\n", NumElementsDouble, NumElementsQuadratic);
            printf("\n---------------------------------------\nPrinted the comparsion between the two Hashes!\n---------------------------------------\n\n");
            break;
        case 8:
            PrintToOut();
            printf("\n---------------------------------------\nSaved to the output file!\n---------------------------------------\n\n");
            break;
        case 9:
            printf("\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -\nThe Program has exit\n-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -\n\n");
            break;
        default:
            printf("Unknown choice.....Choose a valid one!\n");
            break;
        }
    }
}
Hash_Table_Item *QuadraticHash(Course C, Hash_Table_Item *HT) // Function for the Hash that uses Quadratic Hashing
{
    if (((double)(1 + NumElementsQuadratic) / QSize) > ReHashValue)
    {
        int oldSize = QSize;
        QSize = PrimeSize(QSize * 2);
        QuadraticTable = ReHashQuad(C, QuadraticTable, oldSize);
    }
    int index = String_Hashing(C.Name);
    int i = index;
    int h = 1;
    Hash_Table_Item *new_item = (Hash_Table_Item *)malloc(sizeof(Hash_Table_Item));
    new_item->Data = C;
    while (HT[i].flag == 1)
    {

        if (strcmp(HT[i].Data.Name, C.Name) == 0)
        {
            printf("\nThsi Course already presents\n");
            return HT;
        }
        i = (i + (h * h)) % QSize;
        h++;
        QuadraticCollisions++;
        if (i == index)
        {
            printf("\n Hash table is full, cannot add more elements \n");
            return HT;
        }
    }

    HT[i].flag = 1;
    HT[i].Data = C;
    NumElementsQuadratic++;
    printf("\nCourse %s has been inserted\n", C.Name);
    return HT;
}
int PrimeSize(int Count) // Function to return the size for a Hash Table
{
    for (int i = Count;; i++)
    {
        if (IsPrime(i) == i)
            return i;
    }
}
int IsPrime(int x)
{ // Function to check if the number is prime
    int i;
    for (i = 2; i < x; i++)
    {
        if (x % i == 0)
            break;
    }
    if (i == x)
        return x;
    return 0;
}
void initialize_arrays(Hash_Table_Item *HT)
{
    Hash_Table_Item *ptr = HT;
    int i;
    for (i = 0; i < 5; i++)
    {
        ptr->flag = 0;
        ptr++;
    }
}
int Prev_Prime() // Function to get the previous prime number
{
    for (int i = QSize - 1; i > 2; i--)
    {
        if (IsPrime(i) == i)
            return i;
    }
}
void PrintHashes(Hash_Table_Item *HT) // Function to print Has Tables
{
    int index = -1;
    do
    {
        index++;
        if (HT[index].flag == 0)
            printf("Index %d Empty!\n", index);
        else if (HT[index].flag == 1)
            printf("Index %d has : %s %s %d %s %s", index, HT[index].Data.Name, HT[index].Data.Code, HT[index].Data.Credits, HT[index].Data.Department, HT[index].Data.Topics);
    } while (index != QSize);
}
void Print_Tables_Info() // Function to print the tables info
{
    printf("Size of Quadratic Hash Table : %d and the load factor of it : %f\n", QSize, (double)NumElementsQuadratic / QSize);
    printf("Size of Double Hash Table : %d and the load factor of it : %f\n", DSize, (double)NumElementsDouble / DSize);
}
void Search_For_Word(Hash_Table_Item *HT, int size, char *Name) // Function to search for a record in a specific tree
{
    int index = -1;
    do // Do while loop to search in all the table
    {
        index++;
        if (strcmp(HT[index].Data.Name, Name) == 0)
            printf("Found in the index %d\n", index);
    } while (index != size);
}
void Delete_From_Tables(char *Name, Hash_Table_Item *HT, int size)
{
    int index = -1;
    do // Do while loop to search and delete from a table
    {
        index++;

        if (strcmp(HT[index].Data.Name, Name) == 0)
        {
            Course *ptr = &(HT[index].Data);
            ptr = NULL;
            HT[index].flag = 0;
            return;
        }

    } while (index != size);
    printf("Course %s is not found \n", Name);
}
void PrintToOut()
{ // Function to print to the output File
    FILE *out;

    int index = -1;
    out = fopen("saved_courses.txt", "w");
    do // Do while loop to print all the indexes that are not empty
    {
        index++;
        if (HDoubleTable[index].flag == 1)
            fprintf(out, "%s:%d#%s#%s/%s\n", HDoubleTable[index].Data.Name, HDoubleTable[index].Data.Credits, HDoubleTable[index].Data.Code, HDoubleTable[index].Data.Department, HDoubleTable[index].Data.Topics);
    } while (index != DSize);
    fclose(out);
}
Hash_Table_Item *ReHashQuad(Course C, Hash_Table_Item *HT, int Size) // Function to make a new Hash Table if the load rate is reached
{
    Hash_Table_Item *New;
    int index = -1;
    int counter = 0;
    do
    {
        index++;
        if (HT[index].flag == 1)
        {
            New = QuadraticHash(HT[index].Data, New);
            counter++;
        }
    } while (index != Size);
    NumElementsQuadratic -= counter;
    return New;
}
Hash_Table_Item *ReHashDouble(Course C, Hash_Table_Item *HT, int Size) // Function to make a new Hash Table if the load rate is reached
{
    Hash_Table_Item *New;
    int counter = 0;
    int index = -1;
    do
    {
        index++;
        if (HT[index].flag == 1)
        {
            New = DoubleHash(HT[index].Data, New);
            counter++;
        }
    } while (index != Size);
    NumElementsDouble -= counter;
    New = DoubleHash(C, New);
    return New;
}
