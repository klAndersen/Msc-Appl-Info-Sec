#include <stdio.h>

#define ALPHABET_SIZE 26

static const char ALPHABET[ALPHABET_SIZE] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z'
};

static const float ALPHABET_CIPHER_FREQUENCY[ALPHABET_SIZE] = {
		8.16,
		1.49,
		2.78,
		4.23,
		12.70,
		2.22,
		2.01,
		6.09,
		6.96,
		0.15,
		0.77,
		4.02,
		2.40,
		6.74,
		7.50,
		1.92,
		0.09,
		5.98,
		6.32,
		9.05,
		2.75,
		0.97,
		2.36,
		0.15,
		1.97,
		0.07
};

/**
 * Struct that contains a given letter
 * with the frequency it appears with
 * in the cipher text
 */
struct CipherLetterFrequency {
	char ctLetter;
	char ptLetter;
	int amount;
	float frequency;
};

/**
 * Initialize an array that contains a
 * CipherLetterFrequency struct
 *
 * @param cipherFrequency[] - (struct CipherLetterFrequency):
 * Array containing the struct CipherLetterFrequency, which
 * is to be initialized
 *
 */
void initializeCipherStructWithLetters(
		struct CipherLetterFrequency cipherFrequency[ALPHABET_SIZE]) {
	int index = 0;
	for (index = 0; index < sizeof(ALPHABET); index++) {
		cipherFrequency[index].ctLetter = ALPHABET[index];
		cipherFrequency[index].ptLetter = '\0';
		cipherFrequency[index].amount = 0;
		cipherFrequency[index].frequency = 0;
	}
}

/**
 * Loops through the letters in the ALPHABET,
 * and returns the index of the letter if found.
 * If the letter was not found (e.g. symbol, space, etc)
 * -1 is returned.
 *
 * @param letter - char: The letter to find the index of
 * @returns int: Index of letter in ALPHABET || -1
 *
 */
int findCharacterInAlphabet(char letter) {
	char currentLetter;
	int currentIndex = 0;
	int indexOfLetter = -1;
	int noOfLetters = sizeof(ALPHABET);
	do {
		currentLetter = ALPHABET[currentIndex];
		if (currentLetter == letter) {
			indexOfLetter = currentIndex;
		}
		currentIndex++;
	} while (indexOfLetter == -1 && currentIndex < noOfLetters);
	return indexOfLetter;
}

int findCipherCharacterInStruct(char letter,
		struct CipherLetterFrequency cipherFrequency[ALPHABET_SIZE]) {
	char currentLetter;
	int currentIndex = 0;
	int indexOfLetter = -1;
	int noOfLetters = sizeof(ALPHABET);
	do {
		currentLetter = cipherFrequency[currentIndex].ctLetter;
		if (currentLetter == letter) {
			indexOfLetter = currentIndex;
		}
		currentIndex++;
	} while (indexOfLetter == -1 && currentIndex < noOfLetters);
	return indexOfLetter;
}

/**
 * Bubble sorts the letters based on the amount found in the
 * cipher text. The sorting is descending.
 *
 * @param cipherFrequency[] - (struct CipherLetterFrequency):
 * Array containing the struct CipherLetterFrequency to
 * bubble sort
 *
 */
void bubbleSortBasedOnAmount(
		struct CipherLetterFrequency cipherFrequency[ALPHABET_SIZE]) {
	int outerIndex = 0,
			innerIndex = 0;
	struct CipherLetterFrequency tempContainer;
	for(outerIndex = 0; outerIndex < ALPHABET_SIZE; outerIndex++) {
		for(innerIndex = 0; innerIndex < ALPHABET_SIZE; innerIndex++) {
			if (cipherFrequency[innerIndex].amount < cipherFrequency[outerIndex].amount) {
				tempContainer = cipherFrequency[innerIndex];
				cipherFrequency[innerIndex] = cipherFrequency[outerIndex];
				cipherFrequency[outerIndex] =  tempContainer;
			}
		}
	}
}

/**
 * Bubble sorts the letters based on the frequency found in the
 * cipher text. The sorting is descending.
 *
 * @param cipherFrequency[] - (struct CipherLetterFrequency):
 * Array containing the struct CipherLetterFrequency to
 * bubble sort
 *
 */
void bubbleSortBasedOnFrequency(
		struct CipherLetterFrequency cipherFrequency[ALPHABET_SIZE]) {
	int outerIndex = 0,
			innerIndex = 0;
	struct CipherLetterFrequency tempContainer;
	for(outerIndex = 0; outerIndex < ALPHABET_SIZE; outerIndex++) {
		for(innerIndex = 0; innerIndex < ALPHABET_SIZE; innerIndex++) {
			if (cipherFrequency[innerIndex].frequency < cipherFrequency[outerIndex].frequency) {
				tempContainer = cipherFrequency[innerIndex];
				cipherFrequency[innerIndex] = cipherFrequency[outerIndex];
				cipherFrequency[outerIndex] =  tempContainer;
			}
		}
	}
}

/**
 * Fill a struct with the pre-set frequeny of english alphabet letter use
 */
void getBuchstabenhaufigkeitStruct(
		struct CipherLetterFrequency buchstabenHaufigkeit[ALPHABET_SIZE]) {
	int index = 0;
	for (index = 0; index < sizeof(ALPHABET); index++) {
		buchstabenHaufigkeit[index].ctLetter = '\0';
		buchstabenHaufigkeit[index].ptLetter = ALPHABET[index];
		buchstabenHaufigkeit[index].amount = 0;
		buchstabenHaufigkeit[index].frequency = ALPHABET_CIPHER_FREQUENCY[index];
	}
}


int main(int argc, char *argv[]) {
	FILE *fp;
	fp = fopen ("chiffrat.txt" , "r");
	if (fp == NULL) {
		perror ("Error opening file");
	} else {
		int index = 0;
		char currentLetter;
		int indexOfLetter = -1;
		int cipherTextSize = 0;
		int amountOfLetters = 0;
		struct CipherLetterFrequency cipherFrequency[ALPHABET_SIZE];

		initializeCipherStructWithLetters(cipherFrequency);

		/* get the file-size */
		fseek(fp, 0L, SEEK_END);
		cipherTextSize = ftell(fp) + 1;
		fseek(fp, 0L, SEEK_SET);
		/* define an array to keep the filecontent */
		char cipherText[cipherTextSize];
		printf("Reading cipher text from file.\n");
		fread(cipherText, cipherTextSize, 1, fp);
		fclose(fp);
		/* count up the amount of characters in the file */
		printf("Counting the letters in the cipher text.\n\n");
		for (index = 0; index < sizeof(cipherText); index++) {
			currentLetter = cipherText[index];
			indexOfLetter = findCharacterInAlphabet(currentLetter);
			if (indexOfLetter > -1) {
				cipherFrequency[indexOfLetter].amount++;
				/* counter for the ALPHABETic characters in the cipher text */
				amountOfLetters++;
			}
		}
		struct CipherLetterFrequency tempContainer;
		/* print the amount of letters that were found */
		printf("Frequency of alphabetic letters in ciphertext: \n");
		for (index = 0; index < sizeof(ALPHABET); index++) {
			tempContainer = cipherFrequency[index];
			tempContainer.frequency = (float) tempContainer.amount * 100 / amountOfLetters;
			/* store the frequency in the struct array */
			cipherFrequency[index].frequency = tempContainer.frequency;

			printf("%c's absolute frequency: %d.\n%c's relative frequency: %.2f%%.\n\n",
					tempContainer.ctLetter, tempContainer.amount,
					tempContainer.ctLetter, tempContainer.frequency);
			/* print-out for LaTex tabular */
			/*
			printf("%c & %d & %.2f\\%%. \\\\ \\hline\n",
					tempContainer.ctLetter, tempContainer.amount,
					tempContainer.frequency);
			 */
		}

		bubbleSortBasedOnAmount(cipherFrequency);
		/* print the amount of letters that were found - p2 */
		printf("Frequency of alphabetic letters in ciphertext - descending: \n");
		for (index = 0; index < sizeof(ALPHABET); index++) {
			tempContainer = cipherFrequency[index];
			/* store the frequency in the struct array */
			printf("%c's absolute frequency: %d.\n%c's relative frequency: %.2f%%.\n\n",
					tempContainer.ctLetter, tempContainer.amount,
					tempContainer.ctLetter, tempContainer.frequency);
		}
		/* create a struct for English Letter frequency, and sort by frequency */
		struct CipherLetterFrequency buchstabenHaufigkeitStruct[ALPHABET_SIZE];
		getBuchstabenhaufigkeitStruct(buchstabenHaufigkeitStruct);
		bubbleSortBasedOnFrequency(buchstabenHaufigkeitStruct);
		/* map based on frequency comparison */
		printf("Mapping characters based on frequency sorting: \n");
		for (index = 0; index < sizeof(ALPHABET); index++) {
			/* store the frequency in the struct array
			printf("The cipher letter %c is probably equal to the letter %c\n",
					cipherFrequency[index].ctLetter,
					buchstabenHaufigkeitStruct[index].ptLetter
			);
			*/
			cipherFrequency[index].ptLetter = buchstabenHaufigkeitStruct[index].ptLetter;

			/**/
			printf("%c & $\\rightarrow$ & %c \\\\ \\hline \n",
					cipherFrequency[index].ptLetter,
					cipherFrequency[index].ctLetter
			);

		}

		/* attempting to decrypt the text based on frequency mapping */
		for (index = 0; index < sizeof(cipherText)-1; index++) {
			currentLetter = cipherText[index];
			indexOfLetter = findCipherCharacterInStruct(currentLetter, cipherFrequency);
			if (indexOfLetter > -1) {
				currentLetter = cipherFrequency[indexOfLetter].ptLetter;
			}
			printf("%c", currentLetter);
		}
	}
	return 0;
}
