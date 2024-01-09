/*
 * TODO: remove and replace this file header comment
 * This is a .cpp file you will edit and turn in.
 * Remove starter comments and add your own
 * comments on each function and on complex code sections.
 */
#include "console.h"
#include <iostream>
#include "SimpleTest.h"
#include <cmath>
#include "perfect.h"
using namespace std;

/* The divisorSum function takes one argument `n` and calculates the
 * sum of proper divisors of `n` excluding itself. To find divisors
 * a loop iterates over all numbers from 1 to n-1, testing for a
 * zero remainder from the division using the modulus operator %
 *
 * Note: the C++ long type is a variant of int that allows for a
 * larger range of values. For all intents and purposes, you can
 * treat it like you would an int.
 */
long divisorSum(long n) {
    long total = 0;
    for (long divisor = 1; divisor < n; divisor++) {
        if (n % divisor == 0) {
            total += divisor;
        }
    }
    return total;
}

/* The isPerfect function takes one argument `n` and returns a boolean
 * (true/false) value indicating whether or not `n` is perfect.
 * A perfect number is a non-zero positive number whose sum
 * of its proper divisors is equal to itself.
 */
bool isPerfect(long n) {
    return (n != 0) && (n == divisorSum(n));
}

/* The findPerfects function takes one argument `stop` and performs
 * an exhaustive search for perfect numbers over the range 1 to `stop`.
 * Each perfect number found is printed to the console.
 */
void findPerfects(long stop) {
    for (long num = 1; num < stop; num++) {
        if (isPerfect(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long smarterSum(long n) {
    /* TODO: Fill in this function. */

    long total = 0;
    for (long divisor = 1; divisor <= sqrt(n); divisor++) {
        if (n % divisor == 0) {
            total += divisor;
            long divisor2 = n/divisor;
            if (divisor2 != divisor) {
                total += divisor2;
            }
        }
    }
    total = total - n;
    return total;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
bool isPerfectSmarter(long n) {
    /* TODO: Fill in this function. */
    return (n != 0) && n == smarterSum(n);
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void findPerfectsSmarter(long stop) {
     /* TODO: Fill in this function. */
    for (long num = 1; num < stop; num++) {
        if (isPerfectSmarter(num)) {
            cout << "Found perfect number: " << num << endl;
        }
        if (num % 10000 == 0) cout << "." << flush; // progress bar
    }
    cout << endl << "Done searching up to " << stop << endl;
}

/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
long findNthPerfectEuclid(long n) {
    /* TODO: Fill in this function. */
    if (n < 1) {
        return -1;
    }
    int count = 0;
    long k = 1;
    long perfectNumber;
    while (count < n) {
        int m = pow(2, k) - 1;
        if (smarterSum(m) == 1) {
            perfectNumber = pow(2, k-1)*m;
        count++;
        }
    k++;
    }
    return perfectNumber;
}


/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!

/*
 * Here is sample test demonstrating how to use a loop to set the input sizes
 * for a sequence of time trials.
 */


STUDENT_TEST("Testing 3rd Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(3), 496);
}

STUDENT_TEST("Testing 0 Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(-100), -1);
}


STUDENT_TEST("Testing 2nd Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(2), 28);
}

STUDENT_TEST("Testing 1st Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(1), 6);
}

STUDENT_TEST("Testing 4th Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(4), 8128);
}

STUDENT_TEST("Testing 5th Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(5), 33550336);
}


STUDENT_TEST("Testing 6th Perfect number") {
    EXPECT_EQUAL(findNthPerfectEuclid(6), 8589869056);
}

STUDENT_TEST("Test smarterSum and divisorSum of small inputs") {
    EXPECT_EQUAL(smarterSum(1), 0);
}


STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {
    int smallest = 10, largest = 5000;
    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfectsSmarter(size));
   }
}

STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {
    int smallest = 10, largest = 4000;
    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfectsSmarter(size));
    }
}



STUDENT_TEST("Multiple time trials of findPerfects on increasing input sizes") {
    int smallest = 10, largest = 50000;
    for (int size = smallest; size <= largest; size *= 2) {
        TIME_OPERATION(size, findPerfects(size));
    }
}



STUDENT_TEST("Test negative numbers: -1000, -50 and -500 are not perfect") {
    EXPECT(!isPerfect(-1000));
    EXPECT(!isPerfect(-500));
    EXPECT(!isPerfect(-50));
}


STUDENT_TEST("Test smarterSum and divisorSum of small inputs") {
    EXPECT_EQUAL(smarterSum(25) == divisorSum(25), 6);
    EXPECT_EQUAL(smarterSum(6) == divisorSum(6), 6);
    EXPECT_EQUAL(smarterSum(12) == divisorSum(12), 16);
    EXPECT_EQUAL(smarterSum(28) == divisorSum(28), 28);
    EXPECT_EQUAL(smarterSum(1000) == divisorSum(1000), 1340);

}


STUDENT_TEST("Test smarterSum and divisorSum of small inputs") {
    EXPECT_EQUAL(smarterSum(25), 6);
    EXPECT_EQUAL(smarterSum(1), 0);
    EXPECT_EQUAL(smarterSum(28), 28);
    EXPECT_EQUAL(smarterSum(6), 6);
    EXPECT_EQUAL(smarterSum(12), 16);
}


STUDENT_TEST("Test smarterSum and divisorSum of small inputs") {
    EXPECT_EQUAL(smarterSum(6), 6);
}


STUDENT_TEST("Test smarterSum and divisorSum of small inputs") {
    EXPECT_EQUAL(smarterSum(28), 28);
}


STUDENT_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(10000, findPerfects(10000));
}


STUDENT_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(10000, findPerfectsSmarter(10000));
}


STUDENT_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(10000, findPerfectsSmarter(10000));
}

/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("Confirm divisorSum of small inputs") {
    EXPECT_EQUAL(divisorSum(1), 0);
    EXPECT_EQUAL(divisorSum(6), 6);
    EXPECT_EQUAL(divisorSum(12), 16);
}

PROVIDED_TEST("Confirm 6 and 28 are perfect") {
    EXPECT(isPerfect(6));
    EXPECT(isPerfect(28));
}

PROVIDED_TEST("Confirm 12 and 98765 are not perfect") {
    EXPECT(!isPerfect(12));
    EXPECT(!isPerfect(98765));
}

PROVIDED_TEST("Test oddballs: 0 and 1 are not perfect") {
    EXPECT(!isPerfect(0));
    EXPECT(!isPerfect(1));
}

PROVIDED_TEST("Confirm 33550336 is perfect") {
    EXPECT(isPerfect(33550336));
}

PROVIDED_TEST("Time trial of findPerfects on input size 1000") {
    TIME_OPERATION(1000, findPerfects(1000));
}
