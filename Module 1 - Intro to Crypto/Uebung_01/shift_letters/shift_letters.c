#include <stdio.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

static const char ALPHABET[ALPHABET_SIZE] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
		'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
		'Y', 'Z'
};

/**
 * Struct that contains a given letter
 * with the frequency it appears with
 * in the cipher text
 */
struct ShiftedLetterStruct {
	char ctLetter;
	char ptLetter;
};

int indexOfCipher(const struct ShiftedLetterStruct shiftLetters[ALPHABET_SIZE], const char letter) {
	char currentLetter;
	int currentIndex = 0;
	int indexOfLetter = -1;
	int noOfLetters = sizeof(ALPHABET);
	do {
		currentLetter = shiftLetters[currentIndex].ctLetter;
		if (currentLetter == letter) {
			indexOfLetter = currentIndex;
		}
		currentIndex++;
	} while (indexOfLetter == -1 && currentIndex < noOfLetters);
	return indexOfLetter;
}

void setPlaintextAndShiftCipher(struct ShiftedLetterStruct shiftLetters[ALPHABET_SIZE], const int shift) {
	int index = 0;
	int shiftIndex = 0;
	/* loop through the alphabet to set plaintext and shifted cipher text */
	for(index = 0; index < ALPHABET_SIZE; index++) {
		shiftLetters[index].ptLetter = ALPHABET[index];
		/*
		 * set the shift-index by adding the shift to the current letter index.
		 * Since the index is increased, it might be larger than the max
		 * (e.g. index = 13, shift = 13, gives shiftIndex = 26).
		 * Therefore modulus is used (alternative: if-test on shiftIndex)
		 */
		shiftIndex = (index + shift) % 26;
		shiftLetters[index].ctLetter = ALPHABET[shiftIndex];
	}
}

void decryptCipherText(const int cipherLength, char cipherText[cipherLength],
		struct ShiftedLetterStruct shiftLetters[ALPHABET_SIZE]) {
	int index = 0;
	int cipherIndex = 0;
	/* -1 because of zero-byte */
	for(index = 0; index < cipherLength - 1; index++) {
		/* using toupper to get equal case for the letters */
		cipherIndex = indexOfCipher(shiftLetters, toupper(cipherText[index]));
		printf("%c", shiftLetters[cipherIndex].ptLetter);
	}
}

int main(int argc, char *argv[]) {
	const int shift = 13;
	char cipherText[] = "pelcgbtencul";
	struct ShiftedLetterStruct shiftLetters[ALPHABET_SIZE];
	setPlaintextAndShiftCipher(shiftLetters, shift);
	printf("Starting decryption of the ciphertext %s...\n", cipherText);
	decryptCipherText(sizeof(cipherText), cipherText, shiftLetters);

	return 0;
}
