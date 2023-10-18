#include <stdio.h>
#include <iostream>>
#include <stdint.h>
#include <string.h>
#include <string>>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#define MAX_BYTES 64

typedef struct {
    uint8_t data[MAX_BYTES]; // Массив байтов для хранения числа
    int length; // Длина числа в байтах
} MyBigInt;

void initMyBigInt(MyBigInt* num) {
    memset(num->data, 0, sizeof(num->data));
    num->length = 0;
}

void setHex(MyBigInt* num, const char* hex_string) {
    initMyBigInt(num);
    int len = strlen(hex_string);
    int start = len % 2;
    if (start != 0) {
        sscanf(hex_string, "%1hhx", &num->data[0]);
        num->length++;
        hex_string += 1;
    }
    while (sscanf(hex_string, "%2hhx", num->data + num->length) == 1) {
        num->length++;
        hex_string += 2;
    }
}

void getHex(const MyBigInt* num, char* hex_string, int size) {
    int index = 0;
    for (int i = 0; i < num->length; i++) {
        snprintf(hex_string + index, size - index, "%02" PRIx8, num->data[i]);
        index += 2;
    }
}

void XOR(MyBigInt* result, const MyBigInt* num1, const MyBigInt* num2) {
    initMyBigInt(result);
    int max_length = num1->length > num2->length ? num1->length : num2->length;
    result->length = max_length;
    for (int i = 0; i < max_length; i++) {
        result->data[i] = num1->data[i] ^ num2->data[i];
    }
}

void INV(MyBigInt* result, const MyBigInt* num) {
    initMyBigInt(result);
    result->length = num->length;

    for (int i = 0; i < num->length; i++) {
        result->data[i] = ~num->data[i];
    }
}

void OR(MyBigInt* result, const MyBigInt* num1, const MyBigInt* num2) {
    initMyBigInt(result);
    result->length = num1->length > num2->length ? num1->length : num2->length;

    for (int i = 0; i < result->length; i++) {
        result->data[i] = num1->data[i] | num2->data[i];
    }
}

void AND(MyBigInt* result, const MyBigInt* num1, const MyBigInt* num2) {
    initMyBigInt(result);
    result->length = num1->length > num2->length ? num1->length : num2->length;

    for (int i = 0; i < result->length; i++) {
        result->data[i] = num1->data[i] & num2->data[i];
    }
}

void shiftR(MyBigInt* result, const MyBigInt* num, int n) {
    initMyBigInt(result);
    result->length = num->length;

    for (int i = 0; i < num->length; i++) {
        result->data[i] = (i >= n) ? num->data[i - n] : 0;
    }
}

void shiftL(MyBigInt* result, const MyBigInt* num, int n) {
    initMyBigInt(result);
    result->length = num->length;

    for (int i = 0; i < num->length; i++) {
        result->data[i] = (i + n < MAX_BYTES) ? num->data[i + n] : 0;
    }
}

void get_results(const char* numA, const char* numB){
	MyBigInt numberA, numberB;
    setHex(&numberA, numA);
    setHex(&numberB, numB);

    char Ahex_string[1024], Bhex_string[1024], hex_string[1024];
    getHex(&numberA, Ahex_string, sizeof(Ahex_string));
    printf("NumberA in hex: %s\n", Ahex_string);
    getHex(&numberB, Bhex_string, sizeof(Bhex_string));
    printf("NumberB in hex: %s\n", Bhex_string);

    MyBigInt result;
    XOR(&result, &numberA, &numberB);
    getHex(&result, hex_string, sizeof(hex_string));
    printf("Result of XOR: %s\n", hex_string);

    INV(&result, &numberA);
    getHex(&result, hex_string, sizeof(hex_string));
    printf("Result of INV: %s\n", hex_string);

    OR(&result, &numberA, &numberB);
    getHex(&result, hex_string, sizeof(hex_string));
    printf("Result of OR: %s\n", hex_string);

    AND(&result, &numberA, &numberB);
    getHex(&result, hex_string, sizeof(hex_string));
    printf("Result of AND: %s\n", hex_string);

    shiftR(&result, &numberA, 1);
    getHex(&result, hex_string, sizeof(hex_string));
    printf("Result of shiftR: %s\n", hex_string);

    shiftL(&result, &numberA, 1);
    getHex(&result, hex_string, sizeof(hex_string));
    printf("Result of shiftL: %s\n", hex_string);
}

int main() {
	std::string numberC("33ced2c76b26cae94e162c4c0d2c0ff7c13094b0185a3c122e732d5ba77efebc");
	std::string numberD("22e962951cb6cd2ce279ab0e2095825c141d48ef3ca9dabf253e38760b57fe03");
	const char *cnumberC = numberC.c_str();
	const char *cnumberD = numberD.c_str();
	
	printf("Example:");
    get_results(cnumberC, cnumberD);
    
    std::string numberA;
	std::string numberB;
	std::cout << "Enter numberA:";
	std::cin >> numberA;
	std::cout << "Enter numberB:";
	std::cin >> numberB;
    const char *cnumberA = numberA.c_str();
	const char *cnumberB = numberB.c_str();
    get_results(cnumberA, cnumberB);

    return 0;
}
