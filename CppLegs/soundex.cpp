
#include <cctype>
#include <fstream>
#include <string>
#include <map>
#include "console.h"
#include "strlib.h"
#include "filelib.h"
#include "simpio.h"
#include "vector.h"
#include <vector>
#include "SimpleTest.h"
#include "soundex.h"
using namespace std;

/* This function is intended to return a string which
 * includes only the letter characters from the original
 * (all non-letter characters are excluded)

 * Previous code added the first character of the string without checking if it's a letter character.
 * I fixed this.
 */
string lettersOnly(string s) {
    string result;
    for (int i = 0; i < s.length(); i++) {
        if (isalpha(s[i])) {
            result += s[i];
        }
    }
    if (result.empty()) {
        // Throw an exception to indicate an error (empty string)
        throw std::invalid_argument("Invalid characters or string empty.");
    }
    return result;
}


// Encoding the result into digit characters:

string result_digits(string s_without_digits) {
    string character_to_digits = "";
    map<char, char> dd = {{ 'E', '0' }, { 'A', '0'}, { 'O', '0'}, { 'I', '0'}, { 'U', '0'}, { 'W', '0'}, { 'H', '0'}, { 'Y', '0'}, { 'R', '6'}, { 'M', '5'},
                          { 'N', '5'}, { 'L', '4'}, { 'D', '3'}, { 'T', '3'}, { 'B', '1'}, { 'F', '1'}, { 'P', '1'}, { 'V', '1'}, { 'C', '2'}, { 'G', '2'},
                          { 'J', '2'}, { 'K', '2'}, { 'Q', '2'}, { 'S', '2'}, { 'Q', '2'}, { 'Z', '2'}  };


    string uppercase = toUpperCase(s_without_digits);
    if (s_without_digits.empty()) {
        // Throw an exception to indcate an error (empty string)
        throw std::invalid_argument("Invalid characters or string empty.");
    }
    for (int i = 0; i < uppercase.length(); i++) {
        character_to_digits += dd[uppercase[i]];
    }
    return character_to_digits;
}

// Coalescing adjacent numbers

string coalesced (string digits) {
    string new_str = "";
    for (int i = 0; i < digits.length(); i++) {
        if (digits[i] != digits[i+1]) {
            new_str += digits[i];
        }
    }
    return new_str;
}


// Replacing the 1st character and discarding 0s

string final(string s, string digits) {
    digits.erase(0,1);

    string final_string;

    for (int i = 0; i < digits.length(); i++) {
        if (digits[i] != '0') {
            final_string += digits[i];
        }
    }

    final_string.insert(0, 1, toupper(s[0]));
    if (final_string.length() > 4) {
        return final_string.substr(0, 4);
    }
    else if (final_string.length() < 4) {
        while (final_string.length() != 4) {
            final_string += "0";
        }
    }
    return final_string;
}



/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
string soundex(string s) {
    /* TODO: Fill in this function. */
    string first_iteration = lettersOnly(s);

    string digit_iteration = result_digits(first_iteration);
    string second_digit_iteration = coalesced(digit_iteration);

    string final_version = final(s, second_digit_iteration);

    return final_version;
}


/* TODO: Replace this comment with a descriptive function
 * header comment.
 */
void soundexSearch(string filepath) {
    // This provided code opens the specified file
    // and reads the lines into a vector of strings
    ifstream in;
    Vector<string> allNames;

    if (openFile(in, filepath)) {
        allNames = readLines(in);
    }
    cout << "Read file " << filepath << ", "
         << allNames.size() << " names found." << endl;

    // The names read from file are now stored in Vector allNames

    /* TODO: Fill in the remainder of this function. */

    // prompt user for an input
    Vector<string> matchedCodes;
    string surname = "starting point";




    while (true) {
        cout << "Enter a surname (RETURN to quit): ";
        getline(cin, surname);

        if (surname == "\n" || surname.empty()) {
            cout << "All done!";
            return;
        }
        string result = soundex(surname);
        cout << "Soundex code is " << result << endl;

        matchedCodes.clear();

        for (const string& name : allNames) {
            string result2 = soundex(name);
            if (result2 == result) {
                matchedCodes += name;
            }
        }


        if (!matchedCodes.isEmpty()) {
            matchedCodes.sort();
            cout << "Matches from database: ";
            cout << matchedCodes << endl;

        } else {
            cout << "No matches in the database." << endl;
        }

    }

}
    // compute the code for a surname

    // iterate through a vector, if the same code found, store in an array

    // print a sorted array


/* * * * * * Test Cases * * * * * */

// TODO: add your STUDENT_TEST test cases here!

STUDENT_TEST("If 1st character is digit:") {
    string s = "7Kazanska";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "Kazanska");
}

STUDENT_TEST("If second character is digit:") {
    string s = "K7azanska";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "Kazanska");
}

STUDENT_TEST("If string s is numberical:") {
    string s = "786490";
    string result = lettersOnly(s);
    EXPECT_ERROR("786490");
}


STUDENT_TEST("Test to turn surname into a number") {
    string s_without_digits = "kazanska";
    auto final_digits = result_digits(s_without_digits);
    EXPECT_EQUAL(final_digits, "20205220");
}


STUDENT_TEST("Test coalesce digits") {
    string digits = "20205220";
    string final_digits = coalesced(digits);
    EXPECT_EQUAL(final_digits, "2020520");
}


STUDENT_TEST("Padding with 0s:") {
    string s = "Liu";
    string digits = "4";
    string final_string = final(s, digits);
    EXPECT_EQUAL(final_string, "L000");
}



/* Please not add/modify/remove the PROVIDED_TEST entries below.
 * Place your student tests cases above the provided tests.
 */

PROVIDED_TEST("Test exclude of punctuation, digits, and spaces") {
    string s = "O'Hara";
    string result = lettersOnly(s);
    EXPECT_EQUAL(result, "OHara");
    s = "Planet9";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "Planet");
    s = "tl dr";
    result = lettersOnly(s);
    EXPECT_EQUAL(result, "tldr");
}

PROVIDED_TEST("Sample inputs from handout") {
    EXPECT_EQUAL(soundex("Curie"), "C600");
    EXPECT_EQUAL(soundex("O'Conner"), "O256");
}

PROVIDED_TEST("hanrahan is in lowercase") {
    EXPECT_EQUAL(soundex("hanrahan"), "H565");
}

PROVIDED_TEST("DRELL is in uppercase") {
    EXPECT_EQUAL(soundex("DRELL"), "D640");
}

PROVIDED_TEST("Liu has to be padded with zeros") {
    EXPECT_EQUAL(soundex("Liu"), "L000");
}

PROVIDED_TEST("Tessier-Lavigne has a hyphen") {
    EXPECT_EQUAL(soundex("Tessier-Lavigne"), "T264");
}

PROVIDED_TEST("Au consists of only vowels") {
    EXPECT_EQUAL(soundex("Au"), "A000");
}

PROVIDED_TEST("Egilsdottir is long and starts with a vowel") {
    EXPECT_EQUAL(soundex("Egilsdottir"), "E242");
}

PROVIDED_TEST("Jackson has three adjcaent duplicate codes") {
    EXPECT_EQUAL(soundex("Jackson"), "J250");
}

PROVIDED_TEST("Schwarz begins with a pair of duplicate codes") {
    EXPECT_EQUAL(soundex("Schwarz"), "S620");
}

PROVIDED_TEST("Van Niekerk has a space between repeated n's") {
    EXPECT_EQUAL(soundex("Van Niekerk"), "V526");
}

PROVIDED_TEST("Wharton begins with Wh") {
    EXPECT_EQUAL(soundex("Wharton"), "W635");
}

PROVIDED_TEST("Ashcraft is not a special case") {
    // Some versions of Soundex make special case for consecutive codes split by hw
    // We do not make this special case, just treat same as codes split by vowel
    EXPECT_EQUAL(soundex("Ashcraft"), "A226");
}
