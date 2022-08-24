/***********
* Artiom Berengard
* ass06
***********/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

/******************
* Function Name: comparePersonByFirstName
* Input: An array of persons, the chosen indexes to compare.
* Output: An integer that resembles the comparison.
* Function Operation: Using strcmp, this function compares two strings, the first names and returnes
* the value of the comparison.
******************/
int comparePersonByFirstName(void* person, int i, int j) {
	Person* personToCopmare = (Person*)person;
	return strcmp(personToCopmare[j].firstName, personToCopmare[i].firstName);
}

/******************
* Function Name: comparePersonByLastName
* Input: An array of persons, the chosen indexes to compare.
* Output: An integer that resembles the comparison.
* Function Operation: Using strcmp, this function compares two strings, the last names and returnes
* the value of the comparison.
******************/
int comparePersonByLastName(void* person, int i, int j) {
	Person* personToCopmare = (Person*)person;
	return strcmp(personToCopmare[j].lastName, personToCopmare[i].lastName);
}

/******************
* Function Name: comparePersonByWeight
* Input: An array of persons, the chosen indexes to compare.
* Output: An integer that resembles the comparison.
* Function Operation: This function compares two numbers, the weights of two persons, and returnes
* -1 if the returned value needs to be negative, +1 if the value is positive or 0 if the value
* of the comparison is identical.
******************/
int comparePersonByWeight(void* person, int i, int j) {
	Person* personToCopmare = (Person*)person;
	if ((personToCopmare[j].weight - personToCopmare[i].weight) < 0) {
		return -1;
	}
	else if (((personToCopmare[j].weight - personToCopmare[i].weight) > 0)){
	return 1;
	}
	return 0;
}

/******************
* Function Name: comparePersonByHeight
* Input: An array of persons, the chosen indexes to compare.
* Output: An integer that resembles the comparison.
* Function Operation: This function compares two numbers, the heights of two persons, and returnes
* the value of the comparison.
******************/
int comparePersonByHeight(void* person, int i, int j) {
	Person* personToCopmare = (Person*)person;
	return (personToCopmare[j].height - personToCopmare[i].height);
}

/******************
* Function Name: comparePersonByDate
* Input: An array of persons, the chosen indexes to compare.
* Output: An integer that resembles the comparison.
* Function Operation: This function compares two persons by their age. If the year is different,
* the function will compare months. If the months are identical, then the function will preceed
* and compare the days. The returned value is respectively.
******************/
int comparePersonByDate(void* person, int i, int j) {
	Person* personToCompare = (Person*)person;
	if ((personToCompare[j].dateOfBirth.year - personToCompare[i].dateOfBirth.year) > 0) {
		return 1;
	}
	else if ((personToCompare[j].dateOfBirth.year - personToCompare[i].dateOfBirth.year) < 0){
		return -1;
	}
	else{
		if ((personToCompare[j].dateOfBirth.month - personToCompare[i].dateOfBirth.month) > 0) {
			return 1;
		}
		else if ((personToCompare[j].dateOfBirth.month - personToCompare[i].dateOfBirth.month) < 0) {
			return -1;
		}
		else {
			if ((personToCompare[j].dateOfBirth.day - personToCompare[i].dateOfBirth.day) > 0) {
				return 1;
			}
			else if ((personToCompare[j].dateOfBirth.day - personToCompare[i].dateOfBirth.day) < 0) {
				return -1;
			}
			else{
				return 0;
			}
		}
	}

}

/******************
* Function Name: comparePersonByBMI
* Input: An array of persons, the chosen indexes to compare.
* Output: An integer that resembles the comparison.
* Function Operation: This function compares two persons by their BMI. First the function conculates
* the BMI of each person and then compares it and returnes positive, negative or zero value.
******************/
int comparePersonByBMI(void* person, int i, int j) {
	int cmInMeter = 100;
	Person* personToCopmare = (Person*)person;
	float firstPersonHeightInCm = (((float)(personToCopmare[j].height)) / cmInMeter);
	float secondPersonHeightInCm = (((float)(personToCopmare[i].height)) / cmInMeter);
	float firstBMI = (((float)(personToCopmare[j].weight)) / (firstPersonHeightInCm * firstPersonHeightInCm));
	float secondBMI = (((float)(personToCopmare[i].weight)) / (secondPersonHeightInCm * secondPersonHeightInCm));

	if ((firstBMI-secondBMI)<0){
		return -1;
	}
	else if ((firstBMI - secondBMI) > 0) {
		return 1;
	}
	else{
		return 0;
	}
}

/******************
* Function Name: swapPersons
* Input: An array of persons, the chosen indexes to compare.
* Output: None.
* Function Operation: This function swapps between two persons.
******************/
void swapPersons(void* person, int i, int j) {
	Person* personToSwap = (Person*)person;
	Person tmp = personToSwap[i];
	personToSwap[i] = personToSwap[j];
	personToSwap[j] = tmp;
}

/******************
* Function Name: load
* Input: A file, the array of persons and number of total persons.
* Output: None.
* Function Operation: This function loads all of the data from the file and converts
* it to persons by the valid data type, Using the srttok.
******************/
void load(const char* inputFile, Person persons[], int* numOfPersonsPtr) {
	int numOfPersons = *numOfPersonsPtr;
	FILE* input = fopen(inputFile, "r");
	if (!input) {
		printf("File not found: %s\n", inputFile);
		return;
	}

	char buffer[MAX_STR_LEN];

	while (fgets(buffer, MAX_STR_LEN, input)) {
		char* token = strtok(buffer, DELIM);
		strcpy(persons[numOfPersons].firstName,token);
		token = strtok(NULL, DELIM);
		strcpy(persons[numOfPersons].lastName,token);
		token = strtok(NULL, DELIM);
		persons[numOfPersons].dateOfBirth.day=atoi(token);
		token = strtok(NULL, DELIM);
		persons[numOfPersons].dateOfBirth.month = atoi(token);
		token = strtok(NULL, DELIM);
		persons[numOfPersons].dateOfBirth.year = atoi(token);
		token = strtok(NULL, DELIM);
		persons[numOfPersons].height = atoi(token);
		token = strtok(NULL, DELIM);
		persons[numOfPersons].weight = atof(token);
		token = strtok(NULL, DELIM);
			*numOfPersonsPtr = ++numOfPersons;
	}
	if (fclose(input)) {
		printf("Error with closing file: %s\n", inputFile);
		return;
	}

}

/******************
* Function Name: save
* Input: A file, the array of persons and number of total persons.
* Output: None.
* Function Operation: This function loads all of the data from the array of persons and converts
* it to a string and puts it in a new output file.
******************/
void save(const char* outputFile, Person persons[], int numOfPersons) {

	FILE* output = fopen(outputFile, "a");
	if (!output) {
		printf("Error with file: %s\n", outputFile);
		return;
	}

	for (int i = 0; i < numOfPersons; i++){
		fprintf(output, "%s,%s,%d,%d,%d,%d,%.2lf\n", persons[i].firstName, persons[i].lastName, persons[i].dateOfBirth.day,
			persons[i].dateOfBirth.month, persons[i].dateOfBirth.year, persons[i].height, persons[i].weight);
	}

	if (fclose(output)) {
		printf("Error with closing file: %s\n", outputFile);
		return;
	}
}
