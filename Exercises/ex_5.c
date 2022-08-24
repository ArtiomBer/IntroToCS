/***********
* Artiom Berengard
* ass05
***********/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//Defining the given struct of a word in the dictionary.
typedef struct Word {
	char** translations;
	struct Word* next;
} Word;

//Defining the given struct of a Dictionary.
typedef struct {
	char** languages;
	int numOfLanguages;
	Word* wordList;
} Dictionary;

//Defining the functions.
void menu(Dictionary* dictionaries, int* numOfDictionaries);
Dictionary* processCreateNewDictionary(char* strLangs, Dictionary* pDictionaries, int* numOfDictionaries);
Dictionary* addNewLangToDictionary(char* lang, Dictionary* dict);
Word* initWordInstance(char* strTranslationsy);
Word* addNewTranslations(char* token, Word* word, int numOfTranslations);
char* readInputLine();
char* readInputChar(char c, int i, char* pAccumStr);
void processAddWordToDictionary(Dictionary* dictionaries, int* numOfDictionaries);
void printListOfLanguages(char** languages, int numOfLanguages);
void processFindWordInDictionary(Dictionary* dictionaries, int* numOfDictionaries);
Word* findWordInDictionary(char* word, Dictionary* dictionary);
void processDeleteWordFromDictionary(Dictionary* dictionaries, int* numOfDictionaries);
void freeWordMem(Word* word);
int deleteWordFromDictionary(char* word, Dictionary* dictionary);
int deleteDictionary(int chosenDictionaryIndex, Dictionary* dictionaries, int* numOfDictionaries);
void freeDictionaryMem(Dictionary* dictionary);
void processExit(Dictionary* dictionaries, int* numOfDictionaries);
void processDeleteDictionary(Dictionary* dictionaries, int* numOfDictionaries);

void freeAllStrings(char** stringArray, int num);
void freeWordList(Word* word, int num);
void freeWord(Word* word, int num);

/******************
* Function Name: main
* Input: This function has the menu function inside, which contains the whole flow of the dictionary,
* as will be described below.
* Output: none.
* Function Operation: This function is responsible of the main flow of the dictionary.
* The program starts with the menu and endes when the menu is exited.
******************/
int main() {
	Dictionary* dictionaries = NULL;
	int numOfDictionaries = 0;
	menu(dictionaries, &numOfDictionaries);
}

/******************
* Function Name: menu
* Input: An intiger.
* Output: The function will send the user to each helper function as will be dexcripted below.
* Each choice bwtween 1-6 has a different path in the dictionary's flow.
* Function Operation: This function contains the whole flow of the Dictionary's manager.
******************/
void menu(Dictionary* dictionaries, int* numOfDictionaries) {
	int choice;

	do {//This loop prints the manu's options for to user to read and then takes the chosen option.
		int numOfDictionariesVal = *numOfDictionaries;
		printf("Welcome to the dictionaries manager!\n"
			"Choose an option:\n"
			"1. Create a new dictionary.\n"
			"2. Add a word to a dictionary.\n"
			"3. Delete a word from a dictionary.\n"
			"4. Find a word in a dictionary.\n"
			"5. Delete a dictionary.\n"
			"6. Exit.\n");
		scanf("%d", &choice);

		//If the user tries to use a dictionary before creating one, an error is printed.
		while ((numOfDictionariesVal == 0) && (choice == 2 || choice == 3 || choice == 4 || choice == 5)) {
			printf("This option is not available right now, try again:\n");
			scanf("%d", &choice);
		}

		switch (choice) {//Each choice has a helper function, all of those functions are describes below.
		case 1:
			printf("Define a new dictionary:\n");
			dictionaries = processCreateNewDictionary(readInputLine(), dictionaries, numOfDictionaries);
			break;
		case 2:
			processAddWordToDictionary(dictionaries, numOfDictionaries);
			break;
		case 3:
			processDeleteWordFromDictionary(dictionaries, numOfDictionaries);
			break;
		case 4:
			processFindWordInDictionary(dictionaries, numOfDictionaries);
			break;
		case 5:
			processDeleteDictionary(dictionaries, numOfDictionaries);
			break;
		case 6:
			processExit(dictionaries, numOfDictionaries);
			break;
		default: printf("Wrong option, try again:\n");
			break;
		}
	} while (choice != 6);
}

/******************
* Function Name: processCreateNewDictionary
* Input: The users input of the dictionary he wants to create.
* Output: A pointer to the created dictionary.
* Function Operation: This function takes the users input via a helper function(readInputLine),
* and devides it into languages using the strtok.
* Afterwards, is allocates memory to the new dictionary and assambles it using more helper functions,
* all of them will be described below.
******************/
Dictionary* processCreateNewDictionary(char* strLangs, Dictionary* pDictionaries, int* numOfDictionaries) {

	char* token = strtok(strLangs, ",");
	int numOfLanguages = 0;
	Dictionary* pTmp = NULL;
	Dictionary* newDict = NULL;

	newDict = (Dictionary*)malloc(sizeof(Dictionary));
	newDict->languages = NULL;
	newDict->numOfLanguages = 0;
	newDict->wordList = NULL;

	while (token != NULL) {
		newDict = addNewLangToDictionary(token, newDict);

		token = strtok(NULL, ",");
	}

	pTmp = pDictionaries;
	pDictionaries = (Dictionary*)realloc(pDictionaries, (*numOfDictionaries + 1) * sizeof(Dictionary));
	if (pDictionaries == NULL) {
		free(pTmp);
		printf("The creation of the dictionary has failed!\n");
		return NULL;
	}
	pDictionaries[*numOfDictionaries] = *newDict;

	*numOfDictionaries += 1;
	printf("The dictionary has been created successfully!\n");
	free(newDict);
	return pDictionaries;
}

/******************
* Function Name: addNewTranslations
* Input: The users input of the translations to the dictionary, word after word,
* using a loop in the initWordInstance function.
* Output: A pointer to the created translations.
* Function Operation: This function allocates memory to the new translations or reallocates it in case,
* there are already translations in the dictionary.
******************/
Word* addNewTranslations(char* token, Word* word, int numOfTranslations) {
	char** pTmp = word->translations;

	if (numOfTranslations == 0) {
		word->translations = malloc(sizeof(char*));
	}
	else {
		word->translations = realloc(word->translations, (numOfTranslations + 1) * sizeof(char*));
	}

	if (word->translations == NULL) {
		free(pTmp);
		return 0;
	}
	word->translations[numOfTranslations] = token;
	return word;
}

/******************
* Function Name: addNewLangToDictionary
* Input: The users input of the languages to the dictionary, word after word,
* using a loop in the processCreateNewDictionary function.
* Output: A pointer to the recieved dictionary with the languages configured.
* Function Operation: This function allocates memory to the new languages or reallocates it in case,
* there are already languages in the dictionary.
******************/
Dictionary* addNewLangToDictionary(char* lang, Dictionary* dict) {
	char** pTmp = NULL;
	pTmp = dict->languages;

	if (dict->languages == NULL) {
		dict->languages = malloc(sizeof(char*));
	}
	else {
		dict->languages = realloc(dict->languages, (dict->numOfLanguages + 1) * sizeof(char*));
	}

	if (dict->languages == NULL) {
		free(pTmp);
		return NULL;
	}
	dict->languages[dict->numOfLanguages] = lang;
	dict->numOfLanguages++;
	return dict;
}

/******************
* Function Name: initWordInstance
* Input: The users input of the words to be added to the dictionary.
* Output: A pointer to the new added word with all of its translations.
* Function Operation: A helper function that adds the words to the dictionary.
******************/
Word* initWordInstance(char* strTranslations) {

	char* token = strtok(strTranslations, ",");
	int numOfTranslations = 0;
	Word* newWord = NULL;

	newWord = (Word*)malloc(sizeof(Word));
	newWord->translations = NULL;
	newWord->next = NULL;

	while (token != NULL) {
		newWord = addNewTranslations(token, newWord, numOfTranslations);
		numOfTranslations++;
		token = strtok(NULL, ",");
	}
	free(token);

	return newWord;
}

/******************
* Function Name: printChooseDictionaryMessage
* Input: The user's dictionaries.
* Output: All of the users dictionaries, numbered.
* Function Operation: A helper function that prints all of the user's dictionaries.
******************/
int printChooseDictionaryMessage(Dictionary* dictionaries, int* numOfDictionaries) {

	int numOfDictionariesInt = *numOfDictionaries;
	int numOfLanguages = 0;
	int index1 = 0, index2 = 0;
	char** languages = NULL;

	if (numOfDictionariesInt > 0) {
		printf("Choose a dictionary:\n");
		for (index1 = 0; index1 < numOfDictionariesInt; index1++)
		{
			if ((&dictionaries[index1])->numOfLanguages > 0) {
				numOfLanguages = (&dictionaries[index1])->numOfLanguages;
				languages = (&dictionaries[index1])->languages;
				printf("%d. ", index1 + 1);
				printListOfLanguages(languages, numOfLanguages);
				printf("\n");
			}
			else {
				printf("Error: No languages found!\n");
				return 0;
			}
		}
	}
	else {
		printf("This option is not available right now, try again:\n");
		return 0;
	}
	return 1;
}

/******************
* Function Name: processAddWordToDictionary
* Input: The user's dictionaries.
* Output: Prints a "Failed/succeeded" message.
* Function Operation: This function uses helper functions to ask the user for the dictionary he wants to add
* word to, ask for the word's translation and add them using dynamic memmory.
******************/
void processAddWordToDictionary(Dictionary* dictionaries, int* numOfDictionaries) {

	int index1 = 0;
	int index2 = 0;
	int chosenDictionaryIndex;
	Dictionary* chosenDictionary = NULL;
	char* enteredWord = NULL;
	char* token = NULL;
	int isSuccessfully = 0;
	int numOfDictionariesInt = *numOfDictionaries;
	Word* newWord = NULL;
	Word* currWord = NULL;

	if (numOfDictionariesInt == 0) {
		printf("This option is not available right now, try again:\n");
		return;
	}

	if (numOfDictionariesInt > 0) {
		if (dictionaries->numOfLanguages > 0) {
			if (printChooseDictionaryMessage(dictionaries, numOfDictionaries) > 0) {

				scanf("%d", &chosenDictionaryIndex);
				chosenDictionary = &(dictionaries[chosenDictionaryIndex - 1]);
				char** languages = chosenDictionary->languages;

				printf("Enter a word in ");
				printListOfLanguages(languages, chosenDictionary->numOfLanguages);
				printf(":\n");

				enteredWord = readInputLine();
				newWord = initWordInstance(enteredWord);

				if (chosenDictionary->wordList == NULL) {
					chosenDictionary->wordList = newWord;
				}
				else {
					currWord = chosenDictionary->wordList;

					while (currWord->next != NULL) {
						currWord = currWord->next;
					}
					currWord->next = newWord;
				}

				printf("The word has been added successfully!\n");
				isSuccessfully = 1;
			}
		}
	}

	if (isSuccessfully == 0) {
		printf("The addition of the word has failed!\n");
	}

}

/******************
* Function Name: processDeleteDictionary
* Input: The user's dictionaries.
* Output: Prints a "Failed/succeeded" message.
* Function Operation: This function uses helper functions to ask the user for the dictionary he wants delete
* and deletes the dictionary.
******************/
void processDeleteDictionary(Dictionary* dictionaries, int* numOfDictionaries) {
	int chosenDictionaryIndex;
	Dictionary* chosenDictionary = NULL;
	char** languages = NULL;
	char sureAnswer;

	if (*numOfDictionaries == 0) {
		printf("This option is not available right now, try again:\n");
		return;
	}

	if (printChooseDictionaryMessage(dictionaries, numOfDictionaries) > 0) {

		scanf("%d", &chosenDictionaryIndex);

		scanf("%*[^\n]");
		printf("Are you sure? (y/n)\n");
		scanf(" %c", &sureAnswer);

		if (sureAnswer != 'y') {
			printf("The deletion of the dictionary has been canceled.\n");
			return;
		}

		if (deleteDictionary(chosenDictionaryIndex, dictionaries, numOfDictionaries) > 0) {
			printf("The dictionary has been deleted successfully!\n");
			return;
		}

		printf("The deletion of the dictionary has failed!\n");
	}

}

/******************
* Function Name: processDeleteWordFromDictionary
* Input: The user's dictionaries.
* Output: Prints a "Failed/succeeded" message.
* Function Operation: This function uses helper functions to ask the user for the dictionary he wants delete
* a word from, ask for the word the user wants to delete and delete the word if it exists,
* using the helper functions.
******************/
void processDeleteWordFromDictionary(Dictionary* dictionaries, int* numOfDictionaries)
{
	int chosenDictionaryIndex;
	Dictionary* chosenDictionary = NULL;
	char** languages = NULL;
	char* enteredWord = NULL;
	Word* word = NULL;
	char sureAnswer;

	if (*numOfDictionaries == 0) {
		printf("This option is not available right now, try again:\n");
		return;
	}

	if (printChooseDictionaryMessage(dictionaries, numOfDictionaries) > 0) {
		scanf("%d", &chosenDictionaryIndex);
		chosenDictionary = &(dictionaries[chosenDictionaryIndex - 1]);
		languages = chosenDictionary->languages;

		printf("Enter a word in %s:\n", languages[0]);

		enteredWord = readInputLine();

		printf("Are you sure? (y/n)\n");
		scanf("%c", &sureAnswer);

		if (sureAnswer != 'y') {
			printf("The deletion of the word has been canceled.\n");
			return;
		}

		if (deleteWordFromDictionary(enteredWord, chosenDictionary) > 0) {
			printf("The word has been deleted successfully!\n");
		}
		else {
			printf("The deletion of the word has failed!\n");
		}
	}
	free(enteredWord);
}

/******************
* Function Name: processFindWordInDictionary
* Input: The user's dictionaries.
* Output: Prints a "Failed/succeeded" message.
* Function Operation: This function uses helper functions to ask the user for the dictionary he wants find
* a word from, ask for the word the user wants to find and serches for the word. if it exists,
* the translations will be printed using the helper functions. Else, if there is no such word,
* an error messege will occur.
******************/
void processFindWordInDictionary(Dictionary* dictionaries, int* numOfDictionaries) {
	int chosenDictionaryIndex;
	Dictionary* chosenDictionary = NULL;
	char** languages = NULL;
	char* enteredWord = NULL;
	Word* word = NULL;

	if (*numOfDictionaries == 0) {
		printf("This option is not available right now, try again:\n");
		return;
	}

	if (printChooseDictionaryMessage(dictionaries, numOfDictionaries) > 0) {
		scanf("%d", &chosenDictionaryIndex);
		chosenDictionary = &(dictionaries[chosenDictionaryIndex - 1]);
		languages = chosenDictionary->languages;

		printf("Enter a word in %s:\n", languages[0]);

		enteredWord = readInputLine();
		word = findWordInDictionary(enteredWord, chosenDictionary);

		if (word != NULL) {
			printf("The translations are:\n");

			for (int index = 1; index < chosenDictionary->numOfLanguages; index++) {
				printf("%s: %s", languages[index], word->translations[index]);
				if (index + 1 < chosenDictionary->numOfLanguages) {
					printf(", ");
				}
			}
		}
		else {
			printf("There are no translations for \"%s\" in this dictionary.", enteredWord);
		}

		printf("\n");
	}
	free(enteredWord);
}

/******************
* Function Name: processExit
* Input: The user's dictionaries.
* Output: Prints bye messege if the dictionaries have been freed successfully.
* Function Operation: This function deletes all of the dictionaries and frees the memmory.
******************/
void processExit(Dictionary* dictionaries, int* numOfDictionaries) {
	for (int index = 0; index < *numOfDictionaries; index++) {
		freeDictionaryMem(&(dictionaries[index]));
	}
	printf("Bye!\n");
	free(dictionaries);
	dictionaries = NULL;
}

/******************
* Function Name: findWordInDictionary
* Input: The user's entered word and dictionary.
* Output: If the word is found, the pointer to the word is returned. else, NULL is returned.
* Function Operation: This function searches for of the word the user has entered in the chosen dictionary.
* If the word has been found, the word's pointer is returned. else, NULL will be returned.
******************/
Word* findWordInDictionary(char* word, Dictionary* dictionary) {

	Word* currWord = dictionary->wordList;
	int found = 0;

	while ((currWord != NULL) && (found == 0)) {
		if (strcmp(currWord->translations[0], word) != 0) {
			currWord = currWord->next;
		}
		else {
			found = 1;
		}
	}

	if (found == 0) {
		return NULL;
	}
	else {
		return currWord;
	}
}

/******************
* Function Name: deleteDictionary
* Input: The user's choosen dictionary to delete.
* Output: A boolean variable.
* Function Operation: This function recieves the choosen dictionary to delete, frees the memory and deletes the dictionary.
******************/
int deleteDictionary(int chosenDictionaryIndex, Dictionary* dictionaries, int* numOfDictionaries) {

	Dictionary* pTmp = NULL;
	Dictionary dictionaryToDelete;
	int index1 = 0; int index0 = 0;
	pTmp = dictionaries;

	for (; index0 < *numOfDictionaries; index0++) {
		if (index0 == (chosenDictionaryIndex - 1)) {
			dictionaryToDelete = dictionaries[index0];
			continue;
		}

		dictionaries[index1] = dictionaries[index0];
		index1++;
	}

	freeDictionaryMem(&dictionaryToDelete);

	*numOfDictionaries -= 1;
	if (*numOfDictionaries == 0) {
		dictionaries = NULL;
	}

	return 1;
}


/******************
* Function Name: deleteWordFromDictionary
* Input: The user's choosen word to delete and the origin dictionary.
* Output: Returnes a boolean variable.
* Function Operation: A helper function that compares the user's choosen word to delete with other existing words,
* if the word is found, it is being deleted, the memory is being freed and the boolean variable's value is 1.
* Else, if the word doesn't exist, the boolean variable's value will be zero.
******************/
int deleteWordFromDictionary(char* word, Dictionary* dictionary) {
	Word* currWord = dictionary->wordList;
	Word* prevWord = currWord;
	int found = 0;
	int isFirstWord = 1;

	while ((currWord != NULL) && (found == 0)) {
		if (currWord->translations != NULL) {
			if (strcmp(currWord->translations[0], word) == 0) {
				if (isFirstWord == 1) {
					dictionary->wordList = currWord->next;
				}
				else {
					prevWord = currWord->next;
				}

				freeAllStrings(currWord->translations,0);
				free(prevWord);
				currWord->translations = NULL;
				currWord->next = NULL;
				found = 1;
			}
			else {
				prevWord = currWord;
				currWord = currWord->next;
				isFirstWord = 0;
			}
		}
	}

	return found;
}

/******************
* Function Name: printListOfLanguages
* Input: All of the dictionaries.
* Output: prints a list of dictionaries.
* Function Operation: A helper function that prints the languages of each dictionary.
******************/
void printListOfLanguages(char** languages, int numOfLanguages) {
	for (int index = 0; index < numOfLanguages; index++)
	{
		printf("%s", languages[index]);
		if (index + 1 < numOfLanguages) {
			printf("%c", ',');
		}
	}
}

/******************
* Function Name: readInputLine
* Input: User's string.
* Output: Saves the user's string using dynamic allocation.
* Function Operation: A helper function that recieves the user's input and with the aid of another helper function,
* realocates memory for the string for each char. Thus, unlimited input is available.
******************/
char* readInputLine() {
	char c, * pAccumStr = NULL, * pTmp = NULL;
	int i = 0;

	scanf(" %c", &c);

	while (c != '\n')
	{
		i++;
		pAccumStr = readInputChar(c, i, pAccumStr);
		c = getchar();
	}

	if (c == '\n') {
		i++;
		pAccumStr = readInputChar('\0', i, pAccumStr);
	}

	return pAccumStr;
}

/******************
* Function Name: readInputChar
* Input: User's string, char after char.
* Output: The user's string using dynamic allocation.
* Function Operation: A helper function that recieves the user's input, a char after char,
* and realocates memory for the string for each char. Thus, unlimited input is available.
******************/
char* readInputChar(char c, int i, char* pAccumStr) {
	char* pTmp = NULL;
	pTmp = pAccumStr;
	pAccumStr = realloc(pAccumStr, i * sizeof(char));
	if (pAccumStr == NULL) {
		free(pTmp);
		return NULL;
	}
	pAccumStr[i - 1] = c;

	return pAccumStr;
}

/******************
* Function Name: freeWordMem
* Input: A word.
* Output: None.
* Function Operation: A helper function that deletes a word from a dictionary and frees the memory.
******************/
void freeWordMem(Word* word) {
	free(word->translations);
	word->translations = NULL;
	word->next = NULL;
}

/******************
* Function Name: freeDictionaryMem
* Input: A dictionary.
* Output: None.
* Function Operation: A helper function that deletes a dictionary and frees the memory.
******************/
void freeDictionaryMem(Dictionary* dictionary) {
	Word* currWord = dictionary->wordList;
	freeWordList(currWord, dictionary->numOfLanguages);
	freeAllStrings(dictionary->languages,dictionary->numOfLanguages);

}

/******************
* Function Name: freeAllStrings
* Input: An Array.
* Output: None.
* Function Operation: A helper function that deletes all of the arrays.
******************/
void freeAllStrings(char** stringArray, int num) {
	if (stringArray != NULL) {
		free(stringArray[0]);
	}

	free(stringArray);
}

/******************
* Function Name: freeWordList
* Input: A word.
* Output: None.
* Function Operation: A helper function that frees all of the wordList.
******************/
void freeWordList(Word* word,int num) {
	if (word!= NULL){
		freeWordList(word->next,num);
		freeWord(word,num);
	}

}

/******************
* Function Name: freeWord
* Input: A word.
* Output: None.
* Function Operation: A helper function that frees a specific word.
******************/
void freeWord(Word* word,int num) {
	freeAllStrings(word->translations, num);
	free(word);
 }
