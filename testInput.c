#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>


//Displays lines from a file which begin with a certain string. 
//https://www.programiz.com/c-programming/examples/remove-characters-string used this source
    
    const int length_Max = 255;
    static char* file_Name = NULL; 
    const int wanted_String_Char = 5; //length of string to return, cannot be over 5


    //instead of using booleans, I used these two to store t/f values
    static int isCompareable = 1;
    static int specifiedUserValue = 1;



void RemoveNonAlphabet(char* inputToParse, char* inputToReturnTo)
{
    int x = 0;

    strcpy(inputToReturnTo, inputToParse);

    for(int i; inputToReturnTo[i] != '\0'; ++i)
    {
        while (!(inputToReturnTo[i] >= 'a' && inputToReturnTo[i] <= 'z') && 
        !(inputToReturnTo[i] >= 'A' && inputToReturnTo[i] <= 'Z') && !(inputToReturnTo[i] == '\0')) 
        {
            for (x = i; inputToReturnTo[x] != '\0'; ++x) {

                // if xth element of line is not an alphabet,
                // assign the value to be line[x + 1]
                inputToReturnTo[x] = inputToReturnTo[x + 1];
            }
            inputToReturnTo[x] = '\0';
        }
    }
}


void ReturnStringFromFileInput(char* wordToSearchFor, char* loadedFile, char* list_Of_Strings[], char* list_Of_Strings_Only_Alphabetical[])
{
    
    //tokonize the string, only put into the list if large enough
    int currentLocation = 0;
    list_Of_Strings[currentLocation] = strtok(loadedFile, " ");

    while(loadedFile != NULL)
    {
        currentLocation ++;
        list_Of_Strings[currentLocation] = strtok(NULL, " ");
    }

    for(int i = 0; i < length_Max; i++)
    {
        RemoveNonAlphabet(list_Of_Strings[i], list_Of_Strings_Only_Alphabetical[i]);
    }
    

    //this for loop iterates through the list of strings and prints strings that are done
    //TODO make this store values later. 
    for(int x = 0; x < length_Max; x++)
    {   
        int temp = 1;

        if(strlen(list_Of_Strings[x]) > wanted_String_Char )
        {
            temp = 0;
            continue;
        }

        for(int n = 0; n < wanted_String_Char; n++)
        {
            if( !( list_Of_Strings_Only_Alphabetical[x][n] == wordToSearchFor[n]) )
            {
                temp = 0;
                continue;
            }
        }

        if(temp == 1)
        {
            puts(list_Of_Strings[x]);
        }
 
    }

    
}

void ReturnStringFromwordToSearchFor(char* wordToSearchFor, char* userWordSearch, char* userWordSearchParsed)
{
    //todo check if argument is 2 and second one is a string
    while( scanf("%254s", userWordSearch) != EOF)
    {
        isCompareable = 1;

        if(strlen(userWordSearch) > wanted_String_Char)
        {
            isCompareable = 0;
            continue;
        }

        RemoveNonAlphabet(userWordSearch, userWordSearchParsed);

        for(int i = 0; i < strlen(wordToSearchFor); i++)
        {
            if((wordToSearchFor[i] != userWordSearchParsed[i]) )
            {
                isCompareable = 0;
            }
            printf("%s", wordToSearchFor);
        }

        if(isCompareable == 1)
        {
            puts(userWordSearch);
        }
    }
}

int main(int argc, char *argv[])
{   
    char *list_Of_Strings[length_Max];
    char *list_Of_Strings_Only_Alphabetical[length_Max];

    char *userWordSearch;
    char *userWordSearchParsed;

    char loadedFile[length_Max]; //name of file (if applicable)
    char wordToSearchFor[length_Max]; //word to search for

    int get_Opt;
    FILE *file;


    for(int i = 0; i < length_Max; i++)
    {
        list_Of_Strings[i] = malloc(length_Max);
        list_Of_Strings_Only_Alphabetical[i] = malloc(length_Max);
    }

    userWordSearch = malloc(length_Max);
    userWordSearchParsed = malloc(length_Max);

    //TODO make sure prefix is specified. 
    //this function reads command line arguments, provides suitable response. 
    while(( get_Opt = getopt(argc, argv, "Vhf")) != -1){ 
        switch(get_Opt)
        {
            case 'V': //information of utility, should print exactly what is said exit(0) after
                printf("my-look from CS537 Spring 2022");
                exit(0);
            break;
            
            case 'h': //prints help about utility, then exit(0) 
                printf("this does stuff, fill in later");
                exit(0);
            break;

            case 'f': 
            //uses filename as input dictionary
            //if this is not specified, my-look will read from stdin. 

            if(argc > 5 || argc < 3)
            {
                //TODO whatever is expected to print
                printf("incorrect number of arguments");
                exit(1);
            }
            file_Name = argv[argc-2]; 
            specifiedUserValue = 0;

            //checks if file is null, if it is return error
            if(file_Name != NULL)
            {
                file = fopen(file_Name, "r");
        
                if (!file) {
                printf("my-look: cannot open file\n");
                exit(1);
                }

                //sets loadedFile with the file contents
                if( fgets (loadedFile, length_Max, file) == NULL ) {
                    //TODO change this 
                    printf("put in whatever the assignment tells me ehre");
                    exit(1);
                }
            }
            break;

            default:
                printf("error, unrecognized command line argument, exiting program");
                exit(0);
            break;
        }
    }


    //this is where the wordToSearchFor is set as the argument
    strcpy(wordToSearchFor, argv[argc - 1]);  

    
    if(specifiedUserValue == 1 )
    {
        if(argc != 2)
        {
            //TODO change to what assignments wants to be printed
            printf("too many arguments, ");
            exit(1);
        }
        ReturnStringFromwordToSearchFor(wordToSearchFor, userWordSearch, userWordSearchParsed);
    }

    else{
        ReturnStringFromFileInput(wordToSearchFor, loadedFile, list_Of_Strings, list_Of_Strings_Only_Alphabetical);
    }

    for(int i = 0; i < length_Max; i++)
    {
        free(list_Of_Strings[i]);
        free(list_Of_Strings_Only_Alphabetical[i]);
    }
    free(userWordSearch);
    free(userWordSearchParsed ); 

    fclose(file);

}
