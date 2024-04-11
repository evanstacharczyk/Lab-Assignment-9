//Evan Stacharczyk lab assignment 9 4/11/24

#include <stdio.h>
#include <stdlib.h> 
struct RecordType
{
    int id;
    char name;
    int order;
};

struct Node
{
    struct RecordType data;
    struct Node *next;
};

struct HashType
{
    struct Node *head;
};

int hash(int x, int hashSz)
{
    return x % hashSz; 
}

int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

//Print records.
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

//Inserts a record into hash table.
void insertRecord(struct HashType hashArray[], int hashSz, struct RecordType record)
{
    int index = hash(record.id, hashSz); 
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node)); 
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    newNode->data = record;
    newNode->next = hashArray[index].head;
    hashArray[index].head = newNode;
}

void displayRecordsInHash(struct HashType hashArray[], int hashSz)
{
    int i;
    for (i = 0; i < hashSz; ++i)
    {
        printf("Index %d -> ", i);
        struct Node *current = hashArray[i].head;
        while (current != NULL)
        {
            printf("(%d, %c, %d) -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashSz = 10; 
    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType *hashArray = (struct HashType *)malloc(hashSz * sizeof(struct HashType));
    if (hashArray == NULL)
    {
        printf("Memory allocation failed\n");
        exit(-1);
    }

    for (int i = 0; i < hashSz; ++i)
    {
        hashArray[i].head = NULL; 
    }

    for (int i = 0; i < recordSz; ++i)
    {
        insertRecord(hashArray, hashSz, pRecords[i]);
    }

    displayRecordsInHash(hashArray, hashSz);
    for (int i = 0; i < hashSz; ++i)
    {
        struct Node *current = hashArray[i].head;
        while (current != NULL)
        {
            struct Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashArray);
    free(pRecords);


    return 0;
}
