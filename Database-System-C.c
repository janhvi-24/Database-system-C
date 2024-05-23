#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 10
#define MAX_RECORDS 100
#define MAX_FIELD_LENGTH 50
#define MAX_FIELDS 5

typedef struct {
    char name[MAX_FIELD_LENGTH];
    char value[MAX_FIELD_LENGTH];
} Field;

typedef struct {
    Field fields[MAX_FIELDS];
} Record;

typedef struct {
    char name[MAX_FIELD_LENGTH];
    char fieldNames[MAX_FIELDS][MAX_FIELD_LENGTH];
    int fieldCount;
    Record records[MAX_RECORDS];
    int recordCount;
} Table;

Table tables[MAX_TABLES];
int tableCount = 0;

void createTable(char *name, char fieldNames[][MAX_FIELD_LENGTH], int fieldCount) {
    if (tableCount >= MAX_TABLES) {
        printf("Max table limit reached.\n");
        return;
    }

    strcpy(tables[tableCount].name, name);
    tables[tableCount].fieldCount = fieldCount;
    tables[tableCount].recordCount = 0;

    for (int i = 0; i < fieldCount; i++) {
        strcpy(tables[tableCount].fieldNames[i], fieldNames[i]);
    }

    tableCount++;
    printf("Table '%s' created successfully.\n", name);
}

void insertRecord(char *tableName, char values[][MAX_FIELD_LENGTH]) {
    int tableIndex = -1;
    for (int i = 0; i < tableCount; i++) {
        if (strcmp(tables[i].name, tableName) == 0) {
            tableIndex = i;
            break;
        }
    }

    if (tableIndex == -1) {
        printf("Table '%s' not found.\n", tableName);
        return;
    }

    Table *table = &tables[tableIndex];
    if (table->recordCount >= MAX_RECORDS) {
        printf("Max record limit reached for table '%s'.\n", tableName);
        return;
    }

    for (int i = 0; i < table->fieldCount; i++) {
        strcpy(table->records[table->recordCount].fields[i].name, table->fieldNames[i]);
        strcpy(table->records[table->recordCount].fields[i].value, values[i]);
    }

    table->recordCount++;
    printf("Record inserted successfully into table '%s'.\n", tableName);
}

void queryTable(char *tableName) {
    int tableIndex = -1;
    for (int i = 0; i < tableCount; i++) {
        if (strcmp(tables[i].name, tableName) == 0) {
            tableIndex = i;
            break;
        }
    }

    if (tableIndex == -1) {
        printf("Table '%s' not found.\n", tableName);
        return;
    }

    Table *table = &tables[tableIndex];
    printf("Table: %s\n", table->name);
    for (int i = 0; i < table->fieldCount; i++) {
        printf("%s\t", table->fieldNames[i]);
    }
    printf("\n");

    for (int i = 0; i < table->recordCount; i++) {
        for (int j = 0; j < table->fieldCount; j++) {
            printf("%s\t", table->records[i].fields[j].value);
        }
        printf("\n");
    }
}

int main() {
    char fieldNames1[][MAX_FIELD_LENGTH] = {"ID", "Name", "Age"};
    createTable("Users", fieldNames1, 3);

    char values1[][MAX_FIELD_LENGTH] = {"1", "Alice", "23"};
    insertRecord("Users", values1);
    char values2[][MAX_FIELD_LENGTH] = {"2", "Bob", "30"};
    insertRecord("Users", values2);

    queryTable("Users");

    return 0;
}
