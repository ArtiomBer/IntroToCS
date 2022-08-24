/***********
* Artiom Berengard
* ass04
***********/

#include <stdio.h>
#include <string.h>

//Defining the sizes of the arrays as given in the instructions.
#define MAX_WORDS_NUMBER 16
#define MAX_WORD_LENGTH 21
#define MAX_CLUE_LENGTH 21
#define MAX_FAILED_GUESSES 5
#define MAX_USED_LETTERS 64

char allWords[MAX_WORDS_NUMBER + 1][MAX_WORD_LENGTH + 1] = { '\0' };
char gussedTillNow[MAX_WORD_LENGTH] = { '\0' };
char lettersAlreadyTried[MAX_USED_LETTERS] = { '\0' };
char word[MAX_WORD_LENGTH] = { '\0' };
char clue[MAX_CLUE_LENGTH] = { '\0' };
int currNumOfStarsTried = 0;//Global variable for the number if used stars.

//Defining the functions.
void game();
void initGame();
void initGussedTillNow();
int splitAllWordsAndSort(char inputAllWords[]);
int playGame(char* word, char* clue);
int gameRound(
	int roundNumber,
	char chosenChar,
	int *printClueAskMsg,
	int *numberOfFailedGuesses);
int isLetter(char c);
int isStar(char c);
int isFirstTimeStar();
int isLetterAlreadyChosen(char letter);
int isCharExistsInWord(char* w, char c);
void replaceLetterInGussedTillNow(char letter);
int isWordFullyGuessed();
void addLetterAlreadyTried(char letter);
void printFace(int numberOfFailedGuesses);
void printScreen(
	int numberOfFailedGuesses,
	int printUsedLetterMsg,
	int printClueAskMsg,
	int printClue,
	int printWinMsg,
	int printLooseMsg);
void printClueScreen(int numberOfFailedGuesses);
void printAlreadyTriedThatLetterMsg(int numberOfFailedGuesses, int printClueAskMsg);
void printWinningMsg(int numberOfFailedGuesses);
void printLooseMsg(int numberOfFailedGuesses);

//The main function..
int main() {
	game();
	return 0;
}

/******************
* Function Name: game
* Input: This function doesn't take any input.
* Output: Void.
* Function Operation: This function is responsible of the main flow of the game, it controlls each game round.
******************/
void game() {
	initGame();
	playGame(word, clue);
}

/******************
* Function Name: initGame
* Input: The user's bank of words, clue and choosen word to play.
* Output: A sorted "ready to play" array using helper functions.
* Function Operation: This function, with the aid of helper functions, sorts the input.
* // It separates the clue from the options and puts it in a string array. Same with the options.
* Then, it takes the user's choosen word to play and saves it.
******************/
void initGame() {

	char input[350] = { '\0' };
	char copyInput[350] = { '\0' };
	char inputWords[350] = { '\0' };
	int strInputLength = 0;
	int strLenInputClue = 0;
	int strLenWords = 0;
	char* ps = NULL;
	int selectedOption = 0;
	int numOfWords = 0;
	//Getting the users input.
	printf("Enter your words:\n");
	scanf("%[^\n]", input);
	strInputLength = strlen(input);
	strcpy(copyInput, input);
	//Saving the clue in an array.
	strcpy(clue, strtok(copyInput, ":"));
	strLenInputClue = strlen(clue);
	strLenWords = strInputLength - strLenInputClue - 1;
	//Saving the input words in an array.
	ps = input + strLenInputClue + 1;
	strcpy(inputWords, ps);
	inputWords[strLenWords + 1] = '\0';
	//Sorting the words in lexicographic order.
	numOfWords = splitAllWordsAndSort(inputWords);
	//Printing the options menu and saving the input.
	printf("choose an option:\n");

	for (int i = 0; i < numOfWords; i++) {//This loop prints the options of the words to guess.
		printf("%d: %s\n", i + 1, allWords[i]);
	}
	//Saving the decision.
	scanf("%d", &selectedOption);
	strcpy(word, allWords[selectedOption - 1]);
	//Printing the "guessing line".
	initGussedTillNow();
}

/******************
* Function Name:initGussedTillNow
* Input: The length of the choosen word to guess.
* Output: The "guessing line".
* Function Operation: This function prints the guessing line. If there is space in the word,
* then the funtion will print the space, else '_' will be printed.
******************/
void initGussedTillNow() {
	int wordLength = strlen(word);
	for (int i = 0; i < wordLength; i++) {
		if (word[i] == ' ') {
			gussedTillNow[i] = ' ';
		}
		else {
			gussedTillNow[i] = '_';
		}
	}
}

/******************
* Function Name: splitAllWordsAndSort
* Input: A string of words sapereted with ',' , in a random order.
* Output: The total number of words. An array with the words sorted in lexicographic order.
* Function Operation: This function uses sortes the wordes in lexicographic order with
* the aid of some functions from string.h library. Also, the number of total wordes is returned to print the options menu afterwards.
******************/
int splitAllWordsAndSort(char inputAllWords[]) {

	char* token = strtok(inputAllWords, ",");
	int index = 0;
	int i = 0;
	int j = 0;
	char temp[21];
	//Saving the optional words in an array and separating them by the ','.
	while (token != NULL) {
		strcpy(allWords[index++], token);
		token = strtok(NULL, ",");
	}
	//Sorting the words by lexicographical order.
	for (i = 0; i < index; i++) {
		for (j = i + 1; j < index; j++) {
			if (strcmp(allWords[i], allWords[j]) > 0) {
				strcpy(temp, allWords[i]);
				strcpy(allWords[i], allWords[j]);
				strcpy(allWords[j], temp);
			}
		}
	}

	return index;
}

/******************
* Function Name: playGame.
* Input: The boolean value of game rounds. As long as the game round value is smaller then 2 - the game will contine.
* If the user chosen the correct or incorect char, the boolean number is effected by the use of helper functions,
* as will be described below. Then, the function is saving the next char the user enters.
* Output: If the game flow should continue - another game wound will appear. else - the game will end.
* Function Operation: This function is responsible for the flow of the rounds in the game.
******************/
int playGame(char* word, char* clue) {
	int gameRoundRet = 0;
	int roundNumber = 0;
	int printClueAskMsg = 1;
	int numberOfFailedGuesses = 0;
	char chosenChar = '\0';

	while (gameRoundRet < 2) {//As long as this loop is active, the game runs. If the user wins or looses, the loop will stop.
		gameRoundRet = gameRound(
			roundNumber,
			chosenChar,
			&printClueAskMsg,
			&numberOfFailedGuesses);

		if (gameRoundRet == 1) {//Taking the input char if the user can play another game round.
			scanf(" %c", &chosenChar);
		}

		roundNumber++;
	}
	return 0;
}

/******************
* Function Name: gameRound.
* Input: The user's choosen char.
* Output: Depends on the usere's entered char, the function will choose the path of the game round.
* If the char exists in the word, then the correct char path will be activeted. accordingly if the char is wrong.
* If the user's input char already was chosen, the path will be different. Same if the user will ask for a clue.
* Function Operation: Using several loops, the function will effect the path of the game.
* If the returned value from the helper functions will be 1 - the game will continue. If the value is 2 - then the game will end.
* More described below.
* Also, all of the helper function that are used in the function will be described below this function.
******************/
int gameRound(
	int roundNumber,
	char chosenChar,
	int* printClueAskMsg,
	int* numberOfFailedGuesses) {

	int printClueAskMsgVal = (int)(*printClueAskMsg);
	int numberOfFailedGuessesVal = (int)(*numberOfFailedGuesses);

	if (roundNumber > 0) {//This loop will be activeted only after the first round is over.
		if (isLetter(chosenChar)) {//This loop tests the chossen char. if the char is a letter, the loop is activeted.

			if (isLetterAlreadyChosen(chosenChar)) {//If the concrete char was already choosen, then a distinct message will appear.
				printAlreadyTriedThatLetterMsg(numberOfFailedGuessesVal, printClueAskMsgVal);
				return 1;
			}
			//Adding the char to the already used array.
			addLetterAlreadyTried(chosenChar);

			/*This loop is activeted only if the concrete char is part of the choosen word.
			* If the char exists, than the output of the "already choosen" line will be changed accordingly.
			*/
			if (isCharExistsInWord(word, chosenChar)) {
				replaceLetterInGussedTillNow(chosenChar);

				if (isWordFullyGuessed()) {//If the last char is guessed, than the user has won and the game path is over.
					printWinningMsg(numberOfFailedGuessesVal);
					return 2;
				}

				printScreen(//Printing the output, more described in the function description below.
					numberOfFailedGuessesVal,
					0,
					printClueAskMsgVal,
					0,
					0,
					0);
			}
			else {//This loop is activeted if the choosen char isn't part of the word.
				if ((numberOfFailedGuessesVal + 1) == MAX_FAILED_GUESSES) {//If the total wrong guesses number is 5 - the user has lost.
					printLooseMsg(numberOfFailedGuessesVal);
					return 2;
				}
				else {//If the user didn't lose, the next round starts and the number of wrong guesses grows.
					*numberOfFailedGuesses = numberOfFailedGuessesVal + 1;
					numberOfFailedGuessesVal = (int)(*numberOfFailedGuesses);
					printScreen(
						numberOfFailedGuessesVal,
						0,
						printClueAskMsgVal,
						0,
						0,
						0);
				}
			}
		}
		else if (isStar(chosenChar)) {//If the concrete char is a star this loop is activated.
			currNumOfStarsTried++;
			if (isFirstTimeStar()) {// If the user is asking for a clue for the first time - the clue will appear.
				printClueScreen(numberOfFailedGuessesVal);
				*printClueAskMsg = 0;
			}
			else {// If the user has olready asked for a clue, then the clue won't show and the game will continue.
				printScreen(
					numberOfFailedGuessesVal,
					0,
					0,
					0,
					0,
					0);
			}
		}
		else {//This loop will be activated if the user will input a wrong char that isn't a letter of a star.
			printScreen(
				numberOfFailedGuessesVal,
				0,
				printClueAskMsgVal,
				0,
				0,
				0);
		}
	}
	else {//This loop will be activated only on the first round.
		printScreen(
			numberOfFailedGuessesVal,
			0,
			1,
			0,
			0,
			0);
	}

	return 1;//If the user didn't lose, the game continues and the "gameRound" value is 1.
}

/******************
* Function Name: isLetter.
* Input: A char.
* Output: 0 or 1.
* Function Operation: This function will determine whether the entered char is a letter or not. The returned value accordingly.
******************/
int isLetter(char c) {
	if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z') {
		return 1;
	}
	return 0;
}

/******************
* Function Name: isStar.
* Input: A char.
* Output: 0 or 1.
* Function Operation: This function will determine whether the entered char is a star or not. The returned value accordingly.
******************/
int isStar(char c) {
	if (c == '*') {
		return 1;
	}
	return 0;
}

/******************
* Function Name: isFirstTimeStar.
* Input: A variable - "currNumOfStarsTried".
* Output: 0 or 1.
* Function Operation: This function will determine whether this is the first time that the user asks for a clue or not.
*The returned value accordingly.
******************/
int isFirstTimeStar() {
	if (currNumOfStarsTried == 1) {
		return 1;
	}
	return 0;
}

/******************
* Function Name: isLetterAlreadyChosen.
* Input: A variable - the chosen char.
* Output: 0 or 1.
* Function Operation: This function will determine whether this is the first time that the user uses the concrete letter or not.
*The returned value accordingly.
******************/
int isLetterAlreadyChosen(char letter) {
	int numOfLettersUsed = strlen(lettersAlreadyTried);
	for (int i = 0; i < numOfLettersUsed; i++) {
		if (letter == lettersAlreadyTried[i]) {
			return 1;
		}
	}
	return 0;
}

/******************
* Function Name: isCharExistsInWord.
* Input: A variable - the chosen char.
* Output: 0 or 1.
* Function Operation: This function will determine whether the user's entered char is part of the word or not.
*The returned value accordingly.
******************/
int isCharExistsInWord(char* w, char c) {
	if (strchr(w, c) != NULL) {
		return 1;
	}
	return 0;
}

/******************
* Function Name: replaceLetterInGussedTillNow.
* Input: A variable - the chosen char.
* Output: Void.
* Function Operation: This function will replace the guessed letter in the printed "already guessed" line.
******************/
void replaceLetterInGussedTillNow(char letter) {
	int wordLength = strlen(word);

	for (int i = 0; i < wordLength; i++) {
		if (word[i] == letter) {
			gussedTillNow[i] = letter;
		}
	}
}

/******************
* Function Name: addLetterAlreadyTried.
* Input: A variable - the chosen char.
* Output: Void.
* Function Operation: This function will add the tried letter to an array of tried letters.
******************/
void addLetterAlreadyTried(char letter) {
	char addition[2] = { '\0' };
	sprintf(addition, "%c", letter);
	strcat(lettersAlreadyTried, addition);
}

/******************
* Function Name: isWordFullyGuessed.
* Input: A variable - the already guessed letters.
* Output: 0 or 1.
* Function Operation: This function will determine whether the word is fully guessed or not.
* The returned value accordingly.
******************/
int isWordFullyGuessed() {
	if (isCharExistsInWord(gussedTillNow, '_')) {
		return 0;
	}
	return 1;
}

/******************
* Function Name: printFace.
* Input: A variable - the number of failed guesses.
* Output: Void.
* Function Operation: This function will print the face accordingly to the number of failed guesses.
******************/
void printFace(int numberOfFailedGuesses) {

	char line0[64] = " _________________\n";
	char line1[64] = "|  %c%c        %c%c  |\n";
	char line2[64] = "|  %c%c        %c%c  |\n";
	char line3[64] = "|  %c%c        %c%c  |\n";
	char line4[64] = "|                |\n";
	char line5[64] = "| %s  |\n";
	char line6[64] = "|________________|\n";


	printf(line0);

	if (numberOfFailedGuesses >= 4) {
		printf(line1, '-', '-', '-', '-');
	}
	else if (numberOfFailedGuesses == 3)
	{
		printf(line1, '-', '-', ' ', ' ');
	}
	else {
		printf(line1, ' ', ' ', ' ', ' ');
	}

	if (numberOfFailedGuesses == 0) {
		printf(line2, ' ', ' ', ' ', ' ');
		printf(line3, ' ', ' ', ' ', ' ');
	}
	else if (numberOfFailedGuesses == 1) {
		printf(line2, '*', '*', ' ', ' ');
		printf(line3, '*', '*', ' ', ' ');
	}
	else {
		printf(line2, '*', '*', '*', '*');
		printf(line3, '*', '*', '*', '*');
	}

	printf(line4);

	if (numberOfFailedGuesses == 5) {
		printf(line5, "\\/\\/\\/\\/\\/\\/\\");
	}
	else {
		printf(line5, "             ");
	}
	printf(line6);

}

/******************
* Function Name: printScreen.
* Input: Multiple variables.
* Output: Void.
* Function Operation: This function will print the user interface lines accordingly to the value of the variables.
* If the value is 0 - then the line will not be printed.
* If the value is 1 - then the line will be printed.
* More dersribed below.
******************/
void printScreen(
	int numberOfFailedGuesses,
	int printAlreadyTriedThatLetterMsg,
	int printClueAskMsg,
	int printClue,
	int printWinMsg,
	int printLooseMsg) {
	// Defining the printed lines.
	char clueAskMsg[64] = "do you want a clue? press -> *";
	char clueIsMsg[64] = "the clue is: ";
	char alreadyTriedThatLetterMsg[64] = "You've already tried that letter.";
	char triedLettersMsg[64] = "The letters that you already tried:";
	char chooseLetteMsg[64] = "please choose a letter:";

	int lettersTriedLength = strlen(lettersAlreadyTried);

	if (printClue == 1) {//This loop is responsible of printing the clue.
		printf("%s%s.\n", clueIsMsg, clue);
	}

	if (printAlreadyTriedThatLetterMsg == 1) {//This loop is responsible of printing the already tried error.
		printf("%s\n", alreadyTriedThatLetterMsg);
	}

	printFace(numberOfFailedGuesses);//Printing the face acording to the number of failed attempts.

	if (printWinMsg == 1) {//This loop is responsible of printing the winning message.
		printf("The word is %s, good job!\n", word);
	}
	else if (printLooseMsg == 1) {//This loop is responsible of printing the losing message.
		printf("The word is %s, GAME OVER!\n", word);
	}
	else {//This loop is responsible of printing the guessed letters and the '_' chars.
		printf("%s\n", gussedTillNow);

		if (printClueAskMsg == 1) {//This loop is responsible of printing the clue question.
			printf("%s\n", clueAskMsg);
		}

		printf("%s", triedLettersMsg);

		for (int index = 0; index < lettersTriedLength; index++) {//This loop is responsible of printing the Tried letters.
			if (index == 0) {
				printf("%c", ' ');
			}
			printf("%c", lettersAlreadyTried[index]);
			if (index < (lettersTriedLength - 1)) {
				printf("%s", ", ");
			}
		}

		printf("\n");

		printf("%s\n", chooseLetteMsg);
	}
}

/******************
* Function Name:printClueScreen.
* Input: 0 or 1, acording to the value of the variables.
* Output: The clue.
* Function Operation: This function prints the clue.the other variables according to the structure of the printed
* user interface.
******************/
void printClueScreen(int numberOfFailedGuesses) {
	printScreen(
		numberOfFailedGuesses,
		0,
		0,
		1,
		0,
		0);
}

/******************
* Function Name:printAlreadyTriedThatLetterMsg.
* Input: 0 or 1, acording to the value of the variables.
* Output: The already tried that letter error message.
* Function Operation: This function prints the error messege, the other variables according to the structure of the printed
* user interface.
******************/
void printAlreadyTriedThatLetterMsg(int numberOfFailedGuesses, int printClueAskMsg) {
	printScreen(
		numberOfFailedGuesses,
		1,
		printClueAskMsg,
		0,
		0,
		0);
}

/******************
* Function Name:printWinningMsg.
* Input: 0 or 1, acording to the value of the variables.
* Output: The winning message.
* Function Operation: This function prints the winning messege, the other variables according to the structure of the printed
* user interface.
******************/
void printWinningMsg(int numberOfFailedGuesses) {
	printScreen(
		numberOfFailedGuesses,
		0,
		0,
		0,
		1,
		0);
}

/******************
* Function Name:printLooseMsg.
* Input: 0 or 1, acording to the value of the variables.
* Output: The losing message.
* Function Operation: This function prints the losing messege, the other variables according to the structure of the printed
* user interface.
******************/
void printLooseMsg(int numberOfFailedGuesses) {
	printScreen(
		numberOfFailedGuesses + 1,
		0,
		0,
		0,
		0,
		1);
}
