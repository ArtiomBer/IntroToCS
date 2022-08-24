/***********
* Artiom Berengard
* ass02
***********/

#include <stdio.h>
#include <math.h>

/*Introduction of the functions*/
int menu();
void hexToDec(void);
void decToBase(void);
void baseToDec(void);
void plus(void);
void shape(void);
void countBits(void);

int main() {
	menu();
	return 0;
}

/*This is the menu function.*/
int menu() {
	int choice;
	do {
		printf("Choose an option:\n");
		printf("\t1. hexadecimal to Decimal\n");
		printf("\t2. Decimal to Base\n");
		printf("\t3. Base to Decimal\n");
		printf("\t4. PLUS\n");
		printf("\t5. Shape\n");
		printf("\t6. Count bits\n");
		printf("\t7. Exit\n");
		scanf("%d", &choice);

		switch (choice) {
		case 1: hexToDec();
			break;
		case 2: decToBase();
			break;
		case 3: baseToDec();
			break;
		case 4: plus();
			break;
		case 5: shape();
			break;
		case 6: countBits();
			break;
		case 7:
			return(0);
			break;
		default: printf("Wrong option!\n");
			break;
		}
	} while (choice != 7);
}



void hexToDec(void) { //This function breaks the input to char and converts each char from hexadecimal to decimal base
	//introduction of the veriables. also, colculated the ASCII table from a-f or A-F
	int zeroInAscii = 48;
	int nineInAscii = 57;
	int capitalAInAscii = 65;
	int capitalFInAscii = 70;
	int aInAscii = 97;
	int fInAscii = 102;
	int asciiNumberSub = 48;
	int asciiCapitalSub = 55;
	int asciiLowerCaseSub = 87;
	char input;
	int numOfPower = 0;
	int decimalNum = 0;
	int inputInt = 0;
	int hexBase = 16;

	//Ask for a hex number
	printf("Enter a reversed number in base 16:\n");
	scanf(" ");
	scanf("%c", &input);

	//The conculation with ASCII table in each case
	while (input != '\n') {
		inputInt = ((int)input);
		if ((inputInt >= zeroInAscii && inputInt <= nineInAscii) || (inputInt >= capitalAInAscii && inputInt <= capitalFInAscii) \
			|| (inputInt >= aInAscii && inputInt <= fInAscii)) {
			if (inputInt >= capitalAInAscii && inputInt <= capitalFInAscii) {
				inputInt -= asciiCapitalSub;
			}
			else if (inputInt >= zeroInAscii && inputInt <= nineInAscii) {
				inputInt -= asciiNumberSub;
			}
			else if (inputInt >= aInAscii && inputInt <= fInAscii) {
				inputInt -= asciiLowerCaseSub;
			}
			decimalNum += pow(hexBase, numOfPower) * inputInt;
			numOfPower++;
			scanf("%c", &input);
		}
		else {
			printf("Error!\n");
			getchar();
			return(0);
		}
	}
	printf("%d\n", decimalNum);
}


void decToBase(void) {// This function prints your number in the wanted base
	// Introduction of the veriables
	int choosenBase;
	unsigned long numInDec;
	int remainder = 0;
	int divideResult = 0;
	int accumulatedResult = 0;
	int currentPower = 0;

	printf("Enter base and a number:\n"); // Recieving the base and a decimal number
	scanf("%d %d", &choosenBase, &numInDec);
	remainder = (numInDec % choosenBase);
	divideResult = (numInDec / choosenBase);

	while (divideResult > 0){ //This loop conculates the the given decimal number in the wanted base
		accumulatedResult += remainder * pow(10, currentPower);
		currentPower++;
		remainder = divideResult % choosenBase;
		divideResult = divideResult / choosenBase;
	}

	accumulatedResult += remainder * pow(10, currentPower);// adding the last remainder that doesent went inside the loop
	printf("%d\n",accumulatedResult);
}

void baseToDec(void) {
	int choosenBase;
	unsigned long nextDivide;
	int accumulatedResult = 0;
	int currentPower = 0;
	int remainder = 0;

	printf("Enter base and a number:\n"); // Recieving the base and the number in the same base
	scanf("%d %ld", &choosenBase, &nextDivide);

	if (nextDivide <= 0) {
		printf("Error!\n");
		return;
	}

	while (nextDivide > 0) {//conculating the selected number in decimal base
		remainder = nextDivide % 10;
		accumulatedResult += remainder * pow(choosenBase, currentPower);
		currentPower++;
		nextDivide = nextDivide / 10;
	}
	printf("%d\n", accumulatedResult);
}

void plus(void) {//This function will ask you for 2 binary numbers and conculate the sum.
	//Introduction of the veriables.
	//'b' stands for "binary. "cur" = "current". "div" = "divider". "accum" = "accumulated". "rem" = "reminder"
	unsigned long b1;
	unsigned long b2;

	unsigned long curDivBig = 0;
	unsigned long curDivSmall = 0;

	int curPower = 0;

	unsigned long accumRes = 0;
	unsigned long accumCarry = 0;

	int curRem1 = 0;
	int curRem2 = 0;
	int curCarry = 0;
	int prevCarry = 0;
	int sumOfBits = 0;
	int numOfZerosToPad = 0;
	int numOfZerosToPadCarry = 0;

	int firstBigger = 0;

	printf("Enter 2 binary numbers:\n");
	scanf("%ld%ld",&b1,&b2);

	curDivBig = b1;
	curDivSmall = b2;

	if (b2 > b1) {//This loop finds out which number is bigger.
		curDivBig = b2;
		curDivSmall = b1;
		firstBigger++;
	}

	while (curDivBig > 0 || curDivSmall > 0) {
		// This loop takes each of the last digits and adds it to the other. Including carry.

		if (curDivSmall == 0) {// Counting the number of zeros to add to the smaller number.
			numOfZerosToPad++;
		}

		curRem1 = curDivBig % 10;
		curRem2 = curDivSmall % 10;

		curDivBig = curDivBig / 10;
		curDivSmall = curDivSmall / 10;

		// Adding the bits.
		sumOfBits = curCarry + curRem1 + curRem2;

		if (sumOfBits >= 2) { // Conculating the carry and adding it later.
			curCarry = 1;
		}
		else {
			curCarry = 0;
		}

		accumCarry = accumCarry + curCarry * pow(10, curPower);

		if (curCarry == 0) {// conculating the number of zeros to add to the carry.
			numOfZerosToPadCarry++;
		}
		else {
			numOfZerosToPadCarry = 0;
		}

		accumRes += (sumOfBits % 2) * pow(10, curPower);

		curPower++;
	}

	if (curCarry == 1) {//Adding the carry to the bits.
		accumRes += curCarry * pow(10, curPower);
	}

	if (accumCarry == 0) {//Adding the zeros.
		for (int i = 0; i < curPower - 2; i++) {
			printf("%c", '0');
		}
	}
	else {

		for (int i = 0; i < numOfZerosToPadCarry; i++) {
			printf("%c", '0');
		}
	}

	printf("%ld0\n", accumCarry);//The last bit of the carry is always zero.


	if (curCarry == 1) {
		printf("%c", '0');
	}

	printf("%ld\n", ((firstBigger == 0) ? b1 : b2));//Printing the bigger number first.
	printf("%c\n", '+');

	if (curCarry == 1) {
		printf("%c", '0');
	}

	for (int i = 0; i < numOfZerosToPad; i++) {
		printf("%c", '0');
	}
	printf("%ld\n", ((firstBigger == 0) ? b2 : b1));//Printing the samller number.

	for (int i = 0; i < curPower; i++) {
		printf("%c", '-');
	}

	if (curCarry == 1) {//Printing the number of '-'
		printf("%c", '-');
	}

	printf("\n");
	printf("%ld\n", accumRes);//Printing the result.
}

void shape(void) {

	//int i;//The row
	int j;//The column
	int n;//The entered number

	printf("Enter a number:\n");
	scanf("%d", &n);

	int widthOfRow = (((n-2)*2));//Conculating the length of the first and last row.
	int numOfAsterix = 2 * n;
	if (n>2){//Printing the first row.
		printf("###%*c###\n",widthOfRow,' ');
	}
	else if (n ==1 ){
		printf("####\n");
	}
	else if(n == 2) {
		printf("######\n");
	}
	else{
		printf("##\n");
	}

	if (n>1){
		for ( int i = 2; i <= n; i++) {//This is the loop for printing the upper part of the butterfly.
			printf("#");
			for (j = 1; j <=i-1 ; j++){
				printf("*");
			}
			printf("#");
			for (j = i; j <= n-1; j++){
				printf(" ");
			}
			for (j = i; j <= n-1; j++){
				printf(" ");
			}
			printf("#");

			for (j = 1; j <=i-1; j++){
				printf("*");
			}
			printf("#\n");
		}

		//Printing the middle line for n>1.
		printf("#");
		for (int k = 1; k <= numOfAsterix; k++){
			printf("*");
		}
		printf("#\n");

		for (int i = 2; i <= n; i++) {//This is the loop for the bottom part of the butterfly.
			printf("#");
			for (j = i; j <= n ; j++) {
				printf("*");
			}
			printf("#");
			for (j = 2; j <= i - 1; j++) {
				printf(" ");
			}
			for (j = 2; j <= i - 1; j++) {
				printf(" ");
			}
			printf("#");

			for (j = i; j <= n; j++) {
				printf("*");
			}
			printf("#\n");
		}
	}

	if (n==1){//Printing the middle line for n=1.
		printf("#");
		for (int k = 1; k <= numOfAsterix; k++) {
			printf("*");
		}
		printf("#\n");
	}


	if (n > 2) {//Printing the last row.
		printf("###%*c###\n", widthOfRow, ' ');
	}
	else if (n == 1) {
		printf("####\n");
	}
	else if (n == 2) {
		printf("######\n");
	}
	else {
		printf("##\n");
	}



}

void countBits(void) {// This function will count the turned on bits in a binary number
	unsigned long numInDec;
	int choosenBase = 2;//base 2 for binary
	int remainder = 0;
	int divideResult = 0;
	int accumulatedResult = 0;
	int currentPower = 0;
	int numOfBits = 0;

	printf("enter a number:\n"); // Recieving the decimal number
	scanf("%d", &numInDec);
	remainder = (numInDec % choosenBase);
	divideResult = (numInDec / choosenBase);

	while (divideResult > 0){ //This loop conculates the the given decimal number in the wanted base
		accumulatedResult += remainder * pow(10, currentPower);
		currentPower++;
		remainder = divideResult % choosenBase;
		divideResult = divideResult / choosenBase;
	}

	accumulatedResult += remainder * pow(10, currentPower);// adding the last remainder that doesent went inside the loop

	while (accumulatedResult >0){
		 unsigned long currentBit = (accumulatedResult%10);
		 if (currentBit>0){
			 numOfBits++;
		 }
		 accumulatedResult = accumulatedResult / 10;
	}
	printf("no of bits those are 1 in its binary representation: %d\n",numOfBits);

}
