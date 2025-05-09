#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct {
    int year;
    int month;
    int day;
} mydate;

typedef struct {
    int hour;
    int minutes;
} mytime;

typedef struct bilList {
    char name[100];
    char city[100];
    char country[100];
    char buisnes[100];
    char coming[100];
    char sex[100];
    mydate birthdate;
    mytime birthtime;
    char acountnum[13];
    struct bilList *next;
    struct bilList *prev;
    float money;
} billionaire;

struct bilList* addBillionaire(billionaire *tail, char *information);
void printBillionaires(billionaire *tail);
void generateAccountNumber(char *acountnum);
float sumWealth(billionaire *tail);
void find(billionaire *tail,char look,char *information);
void PRINT(billionaire *temp);
void printFilterBillionaires(billionaire *tail, char *command, char *value);
billionaire* deleteOldNew(billionaire *tail,int deleteNewest);
void saveBillionairesToFile(billionaire *tail, const char *filename);
struct bilList* load(billionaire *tail,const char *filename,int i);

int main() {
    char information[1000];
    billionaire *tail = NULL;
    char look;
    srand(time(NULL));
    while (1) {
        printf("$> ");
        fgets(information, sizeof(information), stdin);
        information[strcspn(information, "\n")] = '\0';
        if ((strstr(information, "findN *") != NULL)||(strstr(information, "findC *") != NULL)||(strstr(information, "findS *") != NULL))
        {
            printBillionaires(tail);
        }
        else if (strcmp(information, "exit") == 0) {
            break;
        }
        else if (strstr(information, "new bill") != NULL) {
            char *adjustedInformation = information + 9;
            tail = addBillionaire(tail, adjustedInformation);
        } 
        else if (strcmp(information, "sum") == 0) {
            printf("Total wealth: %.2f\n", sumWealth(tail));
        }
        else if (strstr(information, "findN") != NULL){
            look = 'N';
            char *adjustedInformation = information + 6;
            find(tail,look,adjustedInformation);
        }
        else if (strstr(information, "findC") != NULL){
            look = 'C';
            char *adjustedInformation = information + 6;
            find(tail,look,adjustedInformation);
        }
        else if (strstr(information, "findS") != NULL){
            look = 'S';
            char *adjustedInformation = information + 6;
            find(tail,look,adjustedInformation);
        }
        else if (strstr(information, "print") != NULL) {
            char *command = strtok(information, " ");
            char *value = strtok(NULL, " ");
            if (value != NULL) {
                printFilterBillionaires(tail, command, value);
            }
            else {
                printf("Please provide a value for the print command.\n");
            }
        } 
        else if (strcmp(information, "deleteN") == 0) {
            tail = deleteOldNew(tail, 1);
        } 
        else if (strcmp(information, "deleteO") == 0) {
            tail = deleteOldNew(tail, 0);
        }
        else if (strstr(information, "save") != NULL) {
            char *filename = strtok(information + 5, " ");
            if (filename != NULL) {
                saveBillionairesToFile(tail, filename);
                printf("Data saved to %s\n", filename);
            } else {
                printf("Please provide a filename for saving.\n");
            }
        }
        else if (strstr(information, "load") != NULL)
        {
            char* token ;
            token = strtok(information, " ");
            token = strtok(NULL, " ");
            int i = atoi(token); 
            char *filename = strtok(NULL, " ");
            if (filename != NULL) {
               tail = load(tail,filename,i);
            } else {
                printf("Please provide a file that exist to load \n");
            }
        }
        else {
            printf("Please use 'new bill' to add new information or 'sum' to calculate total wealth.\n");
        }
    }
    printBillionaires(tail);

    return 0;
}

struct bilList* addBillionaire(billionaire *tail, char *information) {
    billionaire *temp = (billionaire *)malloc(sizeof(billionaire));
    int i,check=0;
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    char *token = strtok(information, ";");
    char *str = token;
    for (i = 0; str[i] != '\0'; i++) {
        if ((i == 0) && (islower(str[i]))) {
            str[i] = toupper(str[i]);
        }
        if ((i != 0) && (isupper(str[i])) && (str[i-1] != ' ')) {
            str[i] = tolower(str[i]);
        }
        if ((str[i] == ' ') && (islower(str[i+1]))) {
            str[i+1] = toupper(str[i+1]);
        }
    }
    if (token != NULL) {
       printf("Name: %s\n", token);
       strcpy(temp->name, token);
    }
    else
    {
        printf("You had something wrong in your information please try again.\n");
        free(temp);
        return tail;
    }
    token = strtok(NULL, "/");
    if (strcmp(token, "?") == 0) {
        if (token != NULL) {
            printf("City: Unknown\n");
            strcpy(temp->city, "Unknown");
        }
        else
        {
            printf("You had something wrong in your information please try again.\n");
            free(temp);
            return tail;
        }
    } 
    else {
        if (token != NULL) {
           printf("City: %s\n", token);
           strcpy(temp->city, token);
        }
        else
        {
            printf("You had something wrong in your information please try again.\n");
            free(temp);
            return tail;
        }
    }

    token = strtok(NULL, ";");
    if (strcmp(token, "?") == 0) {
        if (token != NULL) {
           printf("Country: Unknown\n");
           strcpy(temp->country, "Unknown");
        }
        else
        {
            printf("You had something wrong in your information please try again.\n");
            free(temp);
            return tail;
        }
    } 
    else {
        if (token != NULL) {
        printf("Country: %s\n", token);
        strcpy(temp->country, token);
        }
        else
        {
            printf("You had something wrong in your information please try again.\n");
            free(temp);
            return tail;
        }
    }

    token = strtok(NULL, ";");
    if (token != NULL) {
       printf("Business: %s\n", token);
       strcpy(temp->buisnes, token);
    }
    else
    {
        printf("You had something wrong in your information please try again.\n");
        free(temp);
        return tail;
    }
    token = strtok(NULL, ";");
    if (token != NULL) {
       printf("Coming: %s\n", token);
       strcpy(temp->coming, token);
    }
    else
    {
        printf("You had something wrong in your information please try again.\n");
        free(temp);
        return tail;
    }
    token = strtok(NULL, ";");
    if (token != NULL) {
        printf("Sex: %s\n", token);
        strcpy(temp->sex, token);
    }
    else
    {
        printf("You had something wrong in your information please try again.\n");
        free(temp);
        return tail;
    }
    token = strtok(NULL, ";");
    if (token != NULL) {
       printf("Birthdate and Time: %s\n", token);
       sscanf(token, "%d/%d/%d %d:%d", &temp->birthdate.day, &temp->birthdate.month, &temp->birthdate.year, &temp->birthtime.hour, &temp->birthtime.minutes);
    }
    else
    {
        printf("You had something wrong in your information please try again.\n");
        free(temp);
        return tail;
    }
    token = strtok(NULL, ";");
    if (token != NULL) {
       printf("Money: %s\n", token);
       temp->money = atof(token);
       if (temp->money < 0) {
           printf("You had something wrong in your information since you put a negative number in the money. Please try again.\n");
           free(temp);
           return tail;
        }
    }
    else
    {
        printf("You had something wrong in your information please try again.\n");
        free(temp);
        return tail;
    }
    generateAccountNumber(temp->acountnum);
    printf("Generated Account Number: %s\n\n", temp->acountnum);
    if (tail == NULL) {
        temp->next = temp;
        temp->prev = temp;
        return temp;
    } else {
        temp->next = tail->next;
        temp->prev = tail;
        tail->next->prev = temp;
        tail->next = temp;
        return temp;
    }
}

void printBillionaires(billionaire* tail) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    billionaire *temp = tail->next;
    do {
        PRINT(temp);
        temp = temp->next;
    } while (temp != tail->next);
}

void generateAccountNumber(char *acountnum) {
    int arr[10], i, sum = 0, sum1 = 0;
    char final[15];
    while (1) {
        sum = 0;
        sum1 = 0;
        for (i = 0; i < 10; i++) {
            arr[i] = rand() % 10;
        }
        for (i = 0; i < 10; i += 2) {
            arr[i] *= 2;
        }
        for (i = 0; i < 10; i++) {
            if (arr[i] >= 10) {
                int temp1 = arr[i] / 10;
                int temp2 = arr[i] % 10;
                arr[i] = temp1 + temp2;
            }
        }
        for (i = 0; i < 10; i++) {
            sum += arr[i];
        }
        sum1 = sum * 9;
        sum1 = sum1 % 10;
        sum += sum1;
        if ((sum % 10) == 0) {
            break;
        }
        printf("check");
    }
    final[5]='-';
    final[11]='-';
    for (i = 0; i < 11; i++) {
        if (i==5)
        {
            break;
        }
        final[i] = arr[i] + '0';
    }
    for (i = 6; i < 11; i++) {
        if (i==11)
        {
            break;
        }
        final[i] = arr[i-1] + '0';
    }
    final[12] = sum1 + '0';
    final[13] = '\0';
    strcpy(acountnum, final);
}

float sumWealth(billionaire *tail) {
    if (tail == NULL) {
        return 0.0;
    }

    float totalWealth = 0.0;
    billionaire *temp = tail->next;
    do {
        totalWealth += temp->money;
        temp = temp->next;
    } while (temp != tail->next);

    return totalWealth;
}
void PRINT(billionaire *temp)
{
    printf("Name: %s\n", temp->name);
    printf("City: %s\n", temp->city);
    printf("Country: %s\n", temp->country);
    printf("Business: %s\n", temp->buisnes);
    printf("Coming: %s\n", temp->coming);
    printf("Sex: %s\n", temp->sex);
    printf("Birthdate and Time: %d/%d/%d %02d:%02d\n", temp->birthdate.day, temp->birthdate.month, temp->birthdate.year, temp->birthtime.hour, temp->birthtime.minutes);
    printf("Account Number: %s\n", temp->acountnum);
    printf("Money: %.2f\n\n", temp->money);
}
void find(billionaire *tail,char look,char *information)
{   
    int i=0;
    printf("\n%c",look);
    if(tail==NULL)
    {
        printf("list does not have any billionaire\n");
    }
    billionaire *temp = tail->next;
    printf("\n%c",information[2]);
    do {
        if(look=='N')
        {
            if(strstr(temp->name,information)!=NULL )
            {
                PRINT(temp);
                i++;
            }
        }
        else if(look=='C')
        {
            if((strstr(temp->city,information)!=NULL)||(strstr(temp->country,information)!=NULL ))
            {
                PRINT(temp);
                i++;
            }
        }
        else if(look=='S')
        {
            if(strstr(temp->buisnes,information)!=NULL )
            {
                PRINT(temp);
                i++;
            }
        }
        temp = temp->next;
    } while (temp != tail->next);
    if(i==0)
    {
        printf("no more billionaire in list with the charachters you want\n");
    }
}
void printFilterBillionaires(billionaire *tail, char *command, char *value) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return;
    }

    billionaire *temp = tail->next;
    int compareMoney = 0, compareDate = 0, compareTime = 0;
    float moneyValue = 0.0;
    mydate dateValue = {0};
    mytime timeValue = {0};

    if (strcmp(command, "print+") == 0 || strcmp(command, "print-") == 0 || strcmp(command, "print=") == 0) {
        if (strchr(value, '/') != NULL) {
            sscanf(value, "%d/%d/%d", &dateValue.day, &dateValue.month, &dateValue.year);
            compareDate = 1;
        } else if (strchr(value, ':') != NULL) {
            sscanf(value, "%d:%d", &timeValue.hour, &timeValue.minutes);
            compareTime = 1;
        } else {
            moneyValue = atof(value);
            compareMoney = 1;
        }
    }

    do {
        int print = 0;

        if (compareMoney) {
            if ((strcmp(command, "print+") == 0 && temp->money > moneyValue) ||
                (strcmp(command, "print-") == 0 && temp->money < moneyValue) ||
                (strcmp(command, "print=") == 0 && temp->money == moneyValue)) {
                print = 1;
            }
        }

        if (compareDate) {
            if ((strcmp(command, "print+") == 0 && (temp->birthdate.year > dateValue.year ||
                (temp->birthdate.year == dateValue.year && temp->birthdate.month > dateValue.month) ||
                (temp->birthdate.year == dateValue.year && temp->birthdate.month == dateValue.month && temp->birthdate.day > dateValue.day))) ||
                (strcmp(command, "print-") == 0 && (temp->birthdate.year < dateValue.year ||
                (temp->birthdate.year == dateValue.year && temp->birthdate.month < dateValue.month) ||
                (temp->birthdate.year == dateValue.year && temp->birthdate.month == dateValue.month && temp->birthdate.day < dateValue.day))) ||
                (strcmp(command, "print=") == 0 && temp->birthdate.year == dateValue.year &&
                temp->birthdate.month == dateValue.month && temp->birthdate.day == dateValue.day)) {
                print = 1;
            }
        }

        if (compareTime) {
            if ((strcmp(command, "print+") == 0 && (temp->birthtime.hour > timeValue.hour ||
                (temp->birthtime.hour == timeValue.hour && temp->birthtime.minutes > timeValue.minutes))) ||
                (strcmp(command, "print-") == 0 && (temp->birthtime.hour < timeValue.hour ||
                (temp->birthtime.hour == timeValue.hour && temp->birthtime.minutes < timeValue.minutes))) ||
                (strcmp(command, "print=") == 0 && temp->birthtime.hour == timeValue.hour &&
                temp->birthtime.minutes == timeValue.minutes)) {
                print = 1;
            }
        }

        if (print) {
            printf("Name: %s\n", temp->name);
            printf("City: %s\n", temp->city);
            printf("Country: %s\n", temp->country);
            printf("Business: %s\n", temp->buisnes);
            printf("Coming: %s\n", temp->coming);
            printf("Sex: %s\n", temp->sex);
            printf("Birthdate and Time: %d/%d/%d %02d:%02d\n", temp->birthdate.day, temp->birthdate.month, temp->birthdate.year, temp->birthtime.hour, temp->birthtime.minutes);
            printf("Account Number: %s\n", temp->acountnum);
            printf("Money: %.2f\n\n", temp->money);
        }

        temp = temp->next;
    } while (temp != tail->next);
}

billionaire* deleteOldNew(billionaire *tail, int deleteNewest) {
    if (tail == NULL) {
        printf("List is empty.\n");
        return NULL;
    }

    billionaire *target = deleteNewest ? tail : tail->next;
    if (target->next == target) { 
        free(target);
        return NULL;
    }

    target->prev->next = target->next;
    target->next->prev = target->prev;

    if (deleteNewest) {
        tail = target->prev;
    } else {
        if (tail == target) {
            tail = target->prev;
        }
    }

    free(target);
    return tail;
}
void saveBillionairesToFile(billionaire *tail, const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Failed to open file %s for writing.\n", filename);
        return;
    }

    billionaire *temp = tail;
    if (temp != NULL) {
        do {
            fprintf(fp, "%s;%s/%s;%s;%s;%s;%d/%d/%d %02d:%02d;%.2f\n",
                    temp->name, temp->city, temp->country, temp->buisnes, temp->coming,
                    temp->sex, temp->birthdate.day, temp->birthdate.month, temp->birthdate.year,
                    temp->birthtime.hour, temp->birthtime.minutes, temp->money );
            temp = temp->next;
        } while (temp != tail);
    }

    fclose(fp);
}
struct bilList* load(billionaire *tail,const char *filename,int i)
{
    FILE *file = fopen(filename, "r");
    struct bilList* temp ;
    char information[1000];
    if (file) 
    {
        while (fscanf(file, "%99[^\n]\n", information) == 1)
        {
            if(i==0)
            {
                break;
            }
            int x=0;
            printf("%s\n",information);
            tail = addBillionaire(tail,information);
            i--;
        }
        printf("The file '%s' exists.\n", filename);
        fclose(file);
    } 
    else 
    {
        printf("The file '%s' does not exist.\n", filename);
    }
    return tail;
}