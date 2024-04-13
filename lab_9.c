#include <stdio.h>
#define MAX 100

// RecordType
struct RecordType
{
  int		id;
  char	name;
  int		order; 
};

// Fill out this structure
struct HashType
{
  struct RecordType records[MAX];
  int count;
};

// Compute the hash function
int hash(int x)
{
  return x % MAX;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
  FILE* inFile = fopen(inputFileName, "r");
  int dataSz = 0;
  int i, n;
  char c;
  struct RecordType *pRecord;
  *ppData = NULL;

  if (inFile)
  {
    fscanf(inFile, "%d\n", &dataSz);
    *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
    // Implement parse data block
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

// prints the records
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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
  int i;

  for (i=0;i<hashSz;++i)
  {
    if (pHashArray[i].count > 0) {
      printf("Index %d -> ", i);
      for (int j = 0; j < pHashArray[i].count; ++j) {
        printf("(%d, %c, %d) ", pHashArray[i].records[j].id, pHashArray[i].records[j].name, pHashArray[i].records[j].order);
      }
      printf("\n");
    }
  }
}

int main(void)
{
  struct RecordType *pRecords;
  int recordSz = 0;

  recordSz = parseData("input.txt", &pRecords);
  printRecords(pRecords, recordSz);
  // Your hash implementation

  struct HashType hashTable[MAX];
  for (int i = 0; i < MAX; ++i)
    hashTable[i].count = 0;
  for (int i = 0; i < recordSz; ++i){
      int index = hash(pRecords[i].id);
      struct HashType *chain = &hashTable[index];
      chain->records[chain->count++] = pRecords[i];
  }
  displayRecordsInHash(hashTable, MAX);
  
  return 0;
}