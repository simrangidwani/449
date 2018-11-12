//Simran Gidwani srg61

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void makeCode(char secretCode[4][10])
{
    int i, randColor;
    for(i=0; i<4; i++)  
    {
        randColor = 1 + rand() % 6;     //creates a number 
        switch(randColor)       //converts number created to a string
        {
            case 1: strcpy(secretCode[i], "r");     break;
            case 2: strcpy(secretCode[i], "g");     break;
            case 3: strcpy(secretCode[i], "b");     break;
            case 4: strcpy(secretCode[i], "y");     break;
            case 5: strcpy(secretCode[i], "o");     break;
            case 6: strcpy(secretCode[i], "p");     break;
        }
    }   
}

void guess(char guessCode[4][10])
{
    printf("\nEnter your guess:\n");
    for(int i=0; i<4; i++)
    {
        scanf("%s", guessCode[i]);  
    }
}

void checkUserGuess(char secretCode[4][10], char guessCode[4][10], int *blackPeg, int *whitePeg, int *notCorrect)
{
    int i, j, checkSecret[4] = {1,1,1,1}, checkGuess[4] = {1,1,1,1};
    *blackPeg = *whitePeg = 0;

    for(i=0; i<4; i++){ 
            //for(i=0; i<4; i++)
        for(j=0; j<4; j++)   
        {    
            if(strcmp(secretCode[i],guessCode[j]) == 0  &&  checkGuess[i]  &&  checkSecret[j]  &&  i != j)        
            { 
                ++*whitePeg;
                checkSecret[j] = checkGuess[i] = 0;
            }
            if(strcmp(guessCode[i], secretCode[i]) == 0)   
            {
                ++*blackPeg;
                checkSecret[i] = checkGuess[i] = 0;
            }  
            else 
            {
                ++*notCorrect;
            } 

        }

    }
}

void displayGuess(char guessCode[4][10], int blackPeg, int whitePeg, int notCorrect)
{   
    int i;
    printf("\nYour Guess: \n");   
    for(i=0; i<4; i++) 
        printf("%s ", guessCode[i]); 
    printf("\t\t");        
    for(i=0; i<blackPeg; i++) 
        printf(" -black- ");
    for(i=0; i<whitePeg; i++)
        printf(" -white- ");    
    for (i=0; i<notCorrect; i++)
        printf(" -x- ");   
    printf("\n\n");
}

int main()
{
    srand((unsigned int)time(NULL));
    int i, option=1, blackPeg, whitePeg, wrongGuess, notCorrect, colorNum;
    char secretCode[4][10], guessCode[4][10];
    while(1)
    {
        printf("Would you like to play Mastermind?: \nPress 1 to start game \n");
        scanf("%d", &option);        
        printf("How many colors would you like to use? (3-6): \n");
        scanf("%d", &colorNum);
        if(option == 1)
        {
            makeCode(secretCode);
            for(wrongGuess=1; wrongGuess<=10; wrongGuess++)  
            {
                guess(guessCode);
                checkUserGuess(secretCode, guessCode, &blackPeg, &whitePeg, &notCorrect);
                displayGuess(guessCode, blackPeg, whitePeg, notCorrect);
                if(blackPeg == 4)           
                {
                    printf("You Won!");  break;
                }
            }
        if(wrongGuess == 11)      
            printf("\nYou Lost!\nSecret Code: %s %s %s %s\n\n\n\n\n", secretCode[0], secretCode[1], secretCode[2], secretCode[3]);  
        }
        else
            exit(1);
    }
}