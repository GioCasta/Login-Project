#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define PWD_MIN_LENGTH 8
#define PWD_MAX_LENGTH 16
#define NAME_MIN_LENGTH 3 
#define NAME_MAX_LENGTH 20 
#define SURNAME_MIN_LENGTH 3 
#define SURNAME_MAX_LENGTH 20
#define MIN_NUM_RANGE_ASCII 48
#define MAX_NUM_RANGE_ASCII 57
#define MIN_MINUSC_RANGE_ASCII 97
#define MAX_MINUSC_RANGE_ASCII 122
#define MIN_MAIUSC_RANGE_ASCII 65
#define MAX_MAIUSC_RANGE_ASCII 90

bool containsNum(char password[]){
    bool function = false;
    for(int i=0; i<strlen(password); i++){
        if(password[i]>=MIN_NUM_RANGE_ASCII && password[i]<=MAX_NUM_RANGE_ASCII){
        function = true;
        }
    }
    return function;
}

bool containsMinusc(char password[]){
    bool function = false;
    for(int i=0; i<strlen(password); i++){
        if(password[i]>=MIN_MINUSC_RANGE_ASCII && password[i]<=MAX_MINUSC_RANGE_ASCII){
        function = true;
        }
    }
    return function;
}

bool containsMaiusc(char password[]){
    bool function = false;
    for(int i=0; i<strlen(password); i++){
        if(password[i]>=MIN_MAIUSC_RANGE_ASCII && password[i]<=MAX_MAIUSC_RANGE_ASCII){
        function = true;
        }
    }
    return function;
}

bool containsSpecial(char password[]){
    bool function = false;
    for(int i=0; i<strlen(password); i++){
        if(password[i]== 46 || password[i]== 33 || password[i]== 63 || 
        password[i]== 44 || password[i]== 58 || password[i]== 59){
        function = true;
        }
    }
    return function;
}

bool isBetweenLength(char word[], int min, int max){
    bool function = false;
    if(strlen(word) >= min && strlen(word) <= max){
        function = true;
    }
    return function;
}


bool containsOnlyLetters(char word[]){
    bool function = true;
    for(int i=0; i<strlen(word); i++){
        if(!(word[i]>=MIN_MAIUSC_RANGE_ASCII && word[i]<=MAX_MAIUSC_RANGE_ASCII) 
            && !(word[i]>=MIN_MINUSC_RANGE_ASCII && word[i]<=MAX_MINUSC_RANGE_ASCII)){
            function = false;
        }
    }
    return function;
}

void caseSensitive(char maiusc[]){
    for(int i=0;i<strlen(maiusc); i++){
        if(maiusc[i]<=MAX_MAIUSC_RANGE_ASCII&&maiusc[i]>=MIN_MAIUSC_RANGE_ASCII){
            maiusc[i]+=32;
        }
    }
}

void insertPassword(char pwd[]){
    char input[30];
    bool isCorrect = false;
    
    while(!isCorrect){
        //entro nel corpo del while solo se la condizione dentro le tonde
        //è vera
        printf("Inserisci la password: \n");
        scanf("%s",input);
        
        if(isBetweenLength(input, PWD_MIN_LENGTH, PWD_MAX_LENGTH) && containsNum(input) &&
        containsMaiusc(input) && containsMinusc(input) 
        && containsSpecial(input)){
            isCorrect = true;
            printf("Password corretta!\n");
            strcpy(pwd, input);
        } else {
           printf("Password non corretta\n");
        }
    }
}

void insertName(char name[]){
    char input[30];
    bool isCorrect = false;
    
    while(!isCorrect){
        printf("Inserisci il nome: \n");
        scanf("%s", input);
        
        if(isBetweenLength(input,NAME_MIN_LENGTH,NAME_MAX_LENGTH) && containsOnlyLetters(input)){
            isCorrect = true;
            printf("Nome corretto!\n");
            strcpy(name, input);
        } else {
            printf("Nome non corretto\n");
        }
    }
}

void insertSurname(char surname[]){
    char input[30];
    bool isCorrect = false;
    
    while(!isCorrect){
        printf("Inserisci il cognome: \n");
        scanf("%s", input);
        
        if(isBetweenLength(input,SURNAME_MIN_LENGTH,SURNAME_MAX_LENGTH) && containsOnlyLetters(input)){
            isCorrect = true;
            printf("Cognome corretto!\n");
            strcpy(surname, input);
        } else {
            printf("Cognome non corretto\n");
        }
    }
}


bool login(char name[], char surname[], char pwd[]){
    char n[20];
    char c[20];
    char p[20];
    bool condition = false;
    printf("Inserisci il tuo nome: \n");
    scanf("%s",n);
    printf("Inserisci il tuo cognome: \n");
    scanf("%s",c);
    printf("Inserisci la password: \n");
    scanf("%s",p);

    caseSensitive(n);
    caseSensitive(c);

    if((strcmp(name, n) == 0) && (strcmp(surname,c) == 0) && (strcmp(pwd,p) == 0)) 
    {
        condition = true;
    }    
    
    return condition;
}

void firstMaiuscLetter(char word[]){
    if(word[0]>=MIN_MINUSC_RANGE_ASCII&&word[0]<=MAX_MINUSC_RANGE_ASCII){
        word[0]-=32;
    }
}

void sendWelcomeEmail(char name[], char surname[], char pwd[]){
    char n[20];
    char c[20];
    strcpy(n, name);
    strcpy(c, surname);
    
    firstMaiuscLetter(n);
    firstMaiuscLetter(c);
    printf("\nCiao %s %s, benvenuto nel nostro portale.\n", n, c);
    printf("Di seguito il riepilogo delle tue credenziali di accesso:\n");
    printf("Nome: %s\n", n);
    printf("Cognome: %s\n", c);
    printf("password: %s\n", pwd);
}


int main()
{
    char nome[NAME_MAX_LENGTH+1];
    char cognome[SURNAME_MAX_LENGTH+1];
    char password[PWD_MAX_LENGTH+1];

    printf("Benvenuto!\nEffettua la registrazione se non possiedi un account, "
            "altrimenti effettua il login. Premi 0 per la registrazione, 1 per "
            "il login\n");
            
    int c; 
    scanf("%d",&c);
    switch(c){
        case 0:
            insertName(nome);
            insertSurname(cognome);
            insertPassword(password);
            printf("Registrazione completata!\n");
            caseSensitive(nome);
            caseSensitive(cognome);
            
            sendWelcomeEmail(nome, cognome, password);
            
            break;
            
        case 1:
            if(login(nome, cognome, password)){
                printf("Accesso consentito!\n");
            } else {
                printf("Accesso negato!\n");
            }
            break;
    }
    
    return 0;
}