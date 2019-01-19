#ifndef _EULER_H_
#define _EULER_H_
#include <stdint.h>
#include <string>


void printEulerProblems();
int  problem1();
int  problem2();

uint64_t problem3();
bool isPrime(uint64_t x);

int  problem4(int operandDigitCount);
int  countDigits(unsigned long long num);
bool isPalindrome(int num);

int  problem5(int maxDivisor);

double problem6(int max);

uint64_t problem7(int nthPrime);
int64_t getRandomNumber(int64_t min, int64_t max);
uint64_t modExp(uint64_t base, uint64_t power, uint64_t mod);
bool millerRabin(const uint64_t n, const int k);
bool checkPrime(uint64_t number);

uint64_t problem8(int numDigits);


template <typename T>
void validateAnswer(std::string problem, T answer, T expected);

#endif /* _EULER_H_ */