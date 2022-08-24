/***********
* Artiom Berengard
* ass03
***********/

#include <stdio.h>
#include <math.h>

/*Function declarations*/
int menu();
int isPrime(int,int);
void goldbach();
int revNum(int);
void lychrel(int);
int isPalindrom(int);
void printNumPalindrom(int);
void maxSet(void);
int max(int, int);
int endingHere(int arr[], int);
int longestSub(int arr[], int);

//Introduction of the variables for primes function.
int digit;
int primeNum = 1;
int countingSpaces = 0;



int main() {
#if SIZE>=0 && LIMIT>=0
	menu();
	return 0;
#endif
}

/*This is the menu function*/
int menu() {
	int choice;
		printf("1: primes\n");
		printf("2: goldbach\n");
		printf("3: lychrel\n");
		printf("4: max set\n");
		scanf("%d", &choice);

		switch (choice) {//This loop will navigate the user to the choosen task.
		case 1:
			//This loop will send the numbers to the function, from 2 to Size. 2 is the smallest prime number.
			for (digit = 2; digit < SIZE; digit++) {
				primeNum = isPrime(digit, digit / 2);
				if (primeNum == 1) {//If primeNum == 1 it means that this number is prime number.
					if (countingSpaces>0){
						printf(" ");
					}
					countingSpaces++;
					printf("%d", digit);
				}
			}
			break;
		case 2:goldbach();
			break;
		case 3: lychrel(LIMIT);
			break;
		case 4: maxSet();
			break;
		default: printf("Wrong option!\n");
			return 0;
			break;
		}
	}


/******************
* Function Name: isPrime
* Input: Takes an input of 2 integers. One is the tested number and the other is the divider.
* Output: 1 or 0.
* Function Operation: Using recursion to test if each number is a prime number.
* If the suspected number is a prime number, than the return value will be 1. Otherwise, it will be 0.
******************/
int isPrime(int number, int divider) {
	if (divider ==1){//In this case, the number is a prime number and we want to print it.
		return 1;
	}
	else{
		if (number%divider==0){//If the modulo = 0, then the number is not a prime number.
			return 0;
		}
		else{//Continue the process until we test all of the dividers.Recursively.
			isPrime(number,divider-1);
		}
	}
}

/******************
* Function Name: goldbach
* Input: This function recieves the SIZE value.
* Output: Addition of all the posible prime numbers from an array.
* Function Operation: First, declaring an array and gathering all the possible prime numbers in that array.
* Later, the function takes each prime number from that array and adds it to another prime number and prints the output.
******************/
void goldbach() {
	//Variables declaration for goldbach function.
	int primeCounter = 0;
	int primesList[SIZE] = {0} ;//Size is always bigger than the number of prime number.
	int spotInArray = 0, result = 4, firstPrime, secondPrime = 0, summary;
	for (digit = 2; digit < SIZE; digit++) {
		primeNum = isPrime(digit, digit / 2);
		if (primeNum == 1) {//If primeNum == 1 it means that this number is prime number.
			primeCounter++;
			primesList[spotInArray] = digit;
			spotInArray++;
		}
	}

	while (result<=primesList[primeCounter -1]*2){//This loop runs on the prime numbers of the array.
			for (firstPrime = 0; firstPrime < primeCounter; firstPrime++) {//Addition of the first prime
				for (secondPrime = 0; secondPrime < primeCounter; secondPrime++) {//Addition of the second prime
					if (firstPrime <= secondPrime) {
						summary = primesList[firstPrime] + primesList[secondPrime];
						if (summary == result) {//If the addition gives a valid value of even numbers, we will print it.
							printf("%d = %d + %d\n", summary, primesList[firstPrime], primesList[secondPrime]);
						}
					}
				}
			}
		result = result + 2;//Moving to the next even number.
	}
}

/******************
* Function Name: revNum
* Input: A number.
* Output: A reversed number.
* Function Operation: A helper function. This function is reversing the given number.
******************/
int revNum(int num) {
	int revNum = 0;
	while (num>0){
		revNum = (revNum*10)+(num%10);
		num = num / 10;
	}
	return revNum;
}

/******************
* Function Name: isPalindrom
* Input: A number.
* Output: 1 if the number is palindrom. 0 if the number is not a palindrom.
* Function Operation: A helper function. This function returns 1 if the number is palindrom and 0 if it isn't.
******************/
int isPalindrom(int num) {
	if (num==revNum(num)){
		return 1;
	}
	else{
		return 0;
	}
}

/******************
* Function Name: printNumPalindrom
* Input: A number.
* Output: Adittion of numbers unlit they become a palindrome.
* Function Operation: A helper function. This function is printing the proof that a number is a palindrom,
* using the two helper functions above.
******************/
void printNumPalindrom(int num) {
	if (isPalindrom(num)==1){
		printf("%d\n",num);
		return;
	}
	int sumOfNums = num + revNum(num);
	printf("%d:%d+%d=",num,num,revNum(num));
	printNumPalindrom(sumOfNums);
}

/******************
* Function Name: lychrel
* Input: A number.
* Output: Adittion of numbers unlit they become a palindrome.
* Function Operation: This is the proof for lychrel numbers, using the helper functions above.
******************/
void lychrel(int limit) {
	limit = LIMIT;
	int currNum = 1;
	while (currNum<limit){
		printNumPalindrom(currNum);
		currNum++;
	}
}

/******************
* Function Name: max
* Input: Two numbers.
* Output: The maximal number.
* Function Operation: A helper function. This function returns the maximum between two numbers.
******************/
int max(int num1, int num2) {
	return (num1 >= num2) ? num1 : num2;
}

/******************
* Function Name: endingHere
* Input: An array and a the current index of the array.
* Output: The possible longest increasing subsequence.
* Function Operation: A helper function. This function returns the possible maximal length of an increasing subsequence,
* for a specific index of the array.
******************/
int endingHere(int arr[], int curr) {
	int answer = 1;
	if (curr == 0){// The shortest possible sequence is 1;
		return 1;
	}
	for (int j = (curr -1) ;  j >= 0; j--){
		if (arr[j] < arr[curr]){
			answer = max(answer,1 + endingHere(arr,j));
		}
	}
	return answer;
}

/******************
* Function Name: longestSub
* Input: An array and a the number of elements in the sequence.
* Output: The possible longest increasing subsequence, from all of the options.
* Function Operation: A helper function. This function canculated recursively and returns the
* possible maximal length of an increasing subsequence, from all of the options.
******************/
int longestSub(int arr[],int numOfElements) {
	int maxAns = 1;
	for (int i = 0; i <= numOfElements-1; i++){
		maxAns = max(maxAns,endingHere(arr,i));
	}
	return maxAns;
}

/******************
* Function Name: maxSet
* Input: The defined Size, number of elements and the elements themselves.
* Output: The number of elements in the longest increasing subsequence.
* Function Operation: This function recieves the elements and sorts them in an array.
* Then, using the helper functions above, this function prints the number of elements in the longest increasing subsequence.
******************/
void maxSet() {
	//Introduction of the variables.
	int numOfElements;
	int elements;
	int givenSet[SIZE] = {0};

	//Asking for the number of elements to determine how many times the next loop will run.
	printf("Enter the number of elements\n");
	scanf("%d",&numOfElements);

	for (int j = 0; j < numOfElements; j++){//This loop is sorting the elements in an array.
		scanf("%d",&elements);
		givenSet[j] = elements;
	}
	//Using the helper functions above.
	printf("%d",longestSub(givenSet,numOfElements));
}
