#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//TODO determine if need to print out original string
//Displays lines from a file which begin with a certain string. 
int main(int argc, char *argv[])
{   

    int length_Max = 255; //sets max value of acceptable chars
    char file_Name[length_Max]; //filename
    char userInput[length_Max]; //user input word to search

    char loadedFile[length_Max]; //array to hold contents of file
    char list_Of_Strings[length_Max][length_Max]; //array or array of individual words
    char list_Of_ParsedStrings[length_Max][length_Max]; //length of parsed array
    
    char* returnWord;

    int i = 0;
    
    //mallocs length_Max of char (char only 1) 
    returnWord = malloc( length_Max );

    //this function reads command line arguments, provides suitable response. 
    if(argc != 3 )
    {
        printf("wordle: invalid number of args\n");
        exit(1);
    }

    strcpy(file_Name, argv[argc-2]); //sets file to last value user intered 
    strcpy(userInput,argv[argc-1]);  //sets user input to the argv to user input

    if(file_Name == NULL)
    {
        printf("no file found");
    }
    
    strcpy(userInput, argv[argc-1]);

    FILE *file = fopen(file_Name, "r");
    if (!file) {
        printf("wordle: cannot open file\n");
        exit(1);
    }

    if( fgets (loadedFile, length_Max, file)!=NULL ) {
        //README testing only remove once i know file is correctly parsed. 
        puts(loadedFile);
    }

    //splits the file into different words
    strcpy( list_Of_Strings[i], strtok(loadedFile, " ") );
    while(loadedFile != NULL || loadedFile != '\0')
    {
        i++;
        strcpy( list_Of_Strings[i], strtok(NULL, " ") );
    }

    

    //copy values of loaded file into parsed list 
    for(i = 0; i < length_Max; i++)
    {
        for( int x = 0; x < length_Max; x ++)
        {
            list_Of_ParsedStrings[i][x] = list_Of_Strings[i][x]; 
        }
    }

    i = 0;

    //removes all non alphabetical from the word
    //TODO check strlen
    for( int j = 0; j < length_Max ; j++ )
    {
        if(list_Of_ParsedStrings[j] == NULL)
        {
            continue;
        }
        for(int x = 0; list_Of_ParsedStrings[j][x] != '\0'; x++)
        {
            while (! (( ( list_Of_ParsedStrings[j][x]>='a'&& list_Of_ParsedStrings[j][x]<='z' ) ) || 
            ( ( list_Of_ParsedStrings[j][x]>='A' && list_Of_ParsedStrings[j][x]<='Z' ) || list_Of_ParsedStrings[j][x]=='\0')))
            {
                for(i = x; list_Of_ParsedStrings[j][i] !='\0'; ++i)
                {
                    list_Of_ParsedStrings[j][i] = list_Of_ParsedStrings[j][i + 1];
                }

                list_Of_ParsedStrings[j][i]='\0';
            }
        }
    }

    
    //this for loop iterates through the list of strings and prints strings that are done
    for(int x = 0; x < length_Max; x++)
    {
        //exits program upon null or empty string, ask ta if i can use ! to check for null
        if(list_Of_Strings[x] == NULL)
        {
            //TODO close memory
            fclose(file);
            exit(0);
        }

        else if(*list_Of_Strings[x] == '\0')
        {
            printf("reached end of stuff");
            break;
        }

        if(strlen(list_Of_Strings[x]) > 5)
        {
            continue;
        }

        
        returnWord = strstr(list_Of_ParsedStrings[x], userInput);
        //TODO print original list of strings

        if(returnWord)
        {
            printf("%s", list_Of_Strings[x]);
        }

    }

    free (returnWord);
    fclose(file);

}
