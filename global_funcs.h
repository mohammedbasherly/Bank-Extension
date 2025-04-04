#pragma once

#include <iostream>
#include <limits>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

vector<char> vAlphabets = {
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

vector<char> vNumbers = {
    '0', '1', '2', '3', '4',
    '5', '6', '7', '8', '9'
};

namespace global_funcs {
    
    int readIntNumber(string msg = "")
    {
        int num;

        cout << msg;
        cin >> num;

        while(cin.fail())
        {
            cout << "[invalid input!]: ";

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cout << msg;
            cin >> num;

            if (!cin.fail())
                return num;
        }
        
        return num;
    }

    float readFloatNumber(string msg = "")
    {
        float num;

        cout << msg;
        cin >> num;

        while(cin.fail())
        {
            cout << "[invalid input!]: ";

            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            cout << msg;
            cin >> num;

            if (!cin.fail())
                return num;
        }
        return num;
    }

    int readIntNumberInRange(int from, int to, string msg = "")
    {
        int num;

        do
        {
            num = readIntNumber(msg);
        } while (num < from || num > to);
        
        return num;
    }

    int getRandomNumber(int from, int to)
    {
        return rand() % (to - from + 1) + from;
    }

    string getSpace(short spaces = 1)
    {
        string space = "";
        for (short i = 0; i < spaces; i++)
        {
            space += " ";
        }
        return space;
    }

    void printArray(int arr[], short length)
    {
        for (short i = 0; i < length; i++)
        {
            cout << arr[i] << " "; 
        }
    }

    bool isArrayPalindrom(int arr[100], short length)
    {
        for (short i = 0; i < length; i++)
        {
            if (arr[i] != arr[length - 1 - i])
                return false;
        }
        return true;
    }

    void printFabonacciSeries(short length)
    {
        if (length <= 0) return;
        if (length == 1) {cout << "1"; return;}
        if (length == 2) {cout << "1 1 "; return;}

        int num1 = 1, num2 = 1;
        int sum = 0;
        string space = " ";
        cout << num1 << space << num2;

        length -= 2;
        for (short i = 0; i < length; i++)
        {
            sum = num1 + num2;
            cout << space << sum;
            num1 = num2;
            num2 = sum;
        }
    }

    void fillArrayWithFabonacciSeries(int arr[100], short length)
    {
        if (length <= 0) return;
        if (length == 1) {arr[0] = 1; return;}
        if (length == 2) {arr[0] = 1; arr[1] = 1; return;}

        int num1 = 1, num2 = 1;
        int sum = 0;
        arr[0] = 1;
        arr[1] = 1;

        for (short i = 2; i < length; i++)
        {
            sum = num1 + num2;
            arr[i] = sum;
            num1 = num2;
            num2 = sum;
        }
    }

    void printFabonacciSeriesUsingRecursion(short length, int num1 = 0, int num2 = 1)
    {
        if (length <= 0) return;
        // length = 10, 9, 8, 7, 6, 5,  4,  3,  2,  1, 0
        // num1   =  0, 1, 1, 2, 3, 5,  8, 13, 21, 34,
        // num2   =  1, 1, 2, 3, 5, 8, 13, 21, 34, 55,
        // output =  1, 1, 2, 3, 5, 8, 13, 21, 34, 55,

        cout << num2 << " ";
        printFabonacciSeriesUsingRecursion(length - 1, num2, num1+num2);

        // int sum = 1;
        // num1 + num2 <= sum? sum = 1 : sum = num1 + num2;
        // if (length > 0)
        // {
        //     cout << sum << " ";
        //     length--;
        // }

        // if (length > 0)
        // {
        //     num1 = num2;
        //     num2 = sum;
        //     printFabonacciSeriesUsingRecursion(length, num1, num2);
        // }
    }

    string readString(string msg = "")
    {
        string text;

        cout << msg;
        getline(cin, text);

        return text;
    }

    char getFirstLetterOfWord(string word)
    {
        return word[0];
    }

    string geFirstWordFromText(string text)
    {
        short start = 0;

        for (char &character : text)
        {
            if (character == ' ')
                start++;
            else
                break;
        }

        for (short i = start; i < text.length(); i++)
        {
            if (text[i] == ' ')
                return text.substr(start, i - start);
        }

        return text.substr(start);
    }

    void printFirstCharacterOfEachWordInText(string text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                if (i == 0 || text[i - 1] == ' ')
                    cout << text[i] << " "; 
            }
        }
        cout << endl;
    }

    void fillVectorWithFirstCharacterOfEachWordInText(string &text, vector<char> &vArr)
    {
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                if (i == 0 || text[i - 1] == ' ')
                    vArr.push_back(text[i]); 
            }
        }
    }

    void uppercaseFirstLetterOfEachWordInText(string &text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                if (i == 0 || text[i - 1] == ' ')
                    text[i] = toupper(text[i]);
            }
        }
    }

    void lowercaseFirstLetterOfEachWordInText(string &text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                if (i == 0 || text[i - 1] == ' ')
                    text[i] = tolower(text[i]);
            }
        }
    }

    string uppercaseAllLetters(string text)
    {
        for (char &letter : text)
        {
            letter = toupper(letter);
        }
        return text;
    }

    string lowercaseAllLetters(string text)
    {
        for (char &letter : text)
        {
            letter = tolower(letter);
        }
        return text;
    }

    char readCharacter(string msg = "")
    {
        char character;
        
        cout << msg;
        cin >> character;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        return character;
    }

    char invertLetterCase(char character)
    {
        return isupper(character)? tolower(character) : toupper(character);
    }

    string invertAllLettersCase(string &text)
    {
        for (char &letter : text)
        {
            letter = invertLetterCase(letter);
        }
        return text;
    }

    short countCapitalLetters(string &text)
    {
        short count = 0;
        for (char &letter : text)
        {
            if (isupper(letter))
                count++;
        }
        return count;
    }

    short countSmallLetters(string &text)
    {
        short count = 0;
        for (char &letter : text)
        {
            if (islower(letter))
                count++;
        }
        return count;
    }

    short countCharacterInString(string text, char character, bool matchCase = true)
    {
        short count = 0;
        if (!matchCase)
        {
            text = lowercaseAllLetters(text);
            character = tolower(character);
        }
        for (char &letter : text)
        {
            if (letter == character)
                count++;
        }
        return count;
    }

    bool isVowelLetter(char letter)
    {
        letter = tolower(letter);
        return ((letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u'));
    }

    short countVowelLettersInString(string &text)
    {
        short count = 0;
        for (char &letter : text)
        {
            if (isVowelLetter(letter))
                count++;
        }
        return count;
    }

    void printAllVowelsInString(string &text)
    {
        for (char &letter : text)
        {
            if (isVowelLetter(letter))
                cout << letter << " ";
        }
    }

    void printEachWordSeperatlyInText(string text)
    {
        char lastChar = ' ';
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
            {
                cout << text[i];
                lastChar = text[i];
            }
            else
            {
                if (lastChar != ' ')
                {
                    cout << endl;
                    lastChar = ' ';
                }
            }
        }

        /* Another way of solution
            string delim = " ";
            short pos = 0;
            string word = "";
            while ((pos = text.find(delim)) != std::string::npos)
            {
                word = text.substr(0, pos);
                if (word != "")
                {
                    cout << word << endl;
                }
                text.erase(0, pos + delim.length());
            }
            
            if (text != "")
                cout << text << endl;
        */
    }

    short countWordsInText(string text)
    {
        short count = 0;
        char lastChar = ' ';
        for (char &letter : text)
        {
            if (letter != ' ' && lastChar == ' ')
                count++;
            lastChar = letter;
        }
        return count;
    }

    short CountWordsInText(string text)
    {
        short count = 0;
        string delim = " ";
        string word = "";
        short pos = 0;
        while ((pos = text.find(delim)) != std::string::npos)
        {
            word = text.substr(0, pos);
            if (word != "") count++;
            text.erase(0, pos + 1);
        }
        if (text != "")
            count++;

        return count;
    }

    bool isLetter(char letter)
    {
        letter = tolower(letter);

        for (char &alphabet : vAlphabets)
        {
            if (letter == alphabet)
                return true;
        }
        
        return false;
    }

    bool isLetter(string letter)
    {
        if (letter.length() == 1)
        {
            letter = lowercaseAllLetters(letter);
            for (char &alphabet : vAlphabets)
            {
                if (letter[0] == alphabet)
                    return true;
            }
        }
        
        return false;
    }

    bool isNumber(char n)
    {
        for (char &number : vNumbers)
        {
            if (n == number)
                return true;
        }
        return false;
    }

    bool isNumber(string n)
    {
        if (n.length() == 0)
            return false;

        for (char character : n)
        {
            if (!isNumber(character))
                return false;
        }
        
        return true;
    }

    vector<string> splitStringIntoVector(string text, char delim)
    {
        vector<string> vTokens;
        string word = "";
        for (char &letter : text)
        {
            if (letter != delim)
            {
                if ((letter == ' ' && word != ""))
                    word += letter;
                else if (letter != ' ')
                    word += letter;
            }
            else if (letter == delim && word != "")
            {
                vTokens.push_back(word);
                word = "";
            }
        }
        if (word != "")
            vTokens.push_back(word);
        return vTokens;
    }

    vector<string> splitStringIntoVector(string text, string delim)
    {
        vector<string> vTokens;
        short pos = 0;
        string word = "";
        
        while((pos = text.find(delim)) != std::string::npos)
        {
            word = text.substr(0, pos);
            if (word != "")
                vTokens.push_back(word);
            text.erase(0, pos + delim.length());
        }
        if (text != "")
            vTokens.push_back(text);

        return vTokens;
    }

    vector<string> splitStringIntoVector(string text)
    {
        vector<string> vTokens;
        string word = "";
        string space = " ";
        
        for (char &character : text)
        {
            if (isLetter(character) || isNumber(character))
            {
                if (word != "")
                {
                    vTokens.push_back(word);
                    word = "";
                }
                word += character;
            }
            else if (character == ' ')
            {
                if (word != "")
                    vTokens.push_back(word);
                vTokens.push_back(space);
                word = "";
            }
            else 
            {
                if (word != "")
                {
                    vTokens.push_back(word);
                    word = "";
                }
                word += character;
            }
        }
        if (word != "")
            vTokens.push_back(word);

        return vTokens;
    }

    string trim_left(string text)
    {
        for (short i = 0; i < text.length(); i++)
        {
            if (text[i] != ' ')
                return text.substr(i);
        }
        return "";
    }

    string trim_right(string text)
    {
        for (short i = text.length() - 1; i >= 0; i--)
        {
            if (text[i] != ' ')
                return text.substr(0, i + 1);
        }
        return "";
    }

    string trim_(string text)
    {
        return trim_left(trim_right(text));
    }

    string joinString(vector<string> &vTokens, string delim = "")
    {
        string text = "";
        for (short i = 0; i < vTokens.size(); i++)
            text += (vTokens[i] + delim);
        return text.substr(0, text.length() - delim.length());
    }

    string joinString(string arr[100], short length, string delim = "")
    {
        string text = "";
        for (short i = 0; i < length; i++)
            text += (arr[i] + delim);
        return text.substr(0, text.length() - delim.length());
    }

    void printVector(vector<string> &vTexts, bool includeSpaces = true)
    {
        if (includeSpaces)
        {
            for (string &text : vTexts)
                cout << text << endl;
        }
        else
        {
            for (string &text : vTexts)
            {
                if (text != " ")
                    cout << text << endl;
            }
        }
    }

    void printArray(string arr[], short length)
    {
        for (short i = 0; i < length; i++)
            cout << arr[i] << endl;
    }

    string reverseWordsInString(string text, string delim = " ")
    {
        vector<string> vText = splitStringIntoVector(text, delim);
        text = "";

        vector<string>::iterator itr = vText.end();
        while (itr != vText.begin())
        {
            itr--;
            text += (*itr + delim);
        }
        
        return text.substr(0, text.length() - delim.length());
    }

    string replaceWordInString(string text, string old_word, string new_word, bool matchCase = true)
    {
        vector<string> vText = splitStringIntoVector(text);
        if (matchCase)
        {
            for (string &word : vText)
            {
                if (word == old_word)
                    word = new_word;
            }
        }
        else
        {
            old_word = lowercaseAllLetters(old_word);
            for (string &word : vText)
            {
                if (lowercaseAllLetters(word) == old_word)
                    word = new_word;
            }
        }
        return joinString(vText);
    }

    string replaceWordInString2(string text, string old_word, string new_word)
    {
        // there is a bug in this func, for example old_word == "cat" and new_word is "Dog"
        // it will change even "catalog" into "dogalog", and that is wrong
        short pos = 0;
        string word1 = "", word2 = "";
        while ((pos = text.find(old_word)) != std::string::npos)
        {
            word1 = text.substr(0, pos);
            word2 = text.substr((pos + old_word.length()));
            text = word1 + new_word + word2;
            /*
                or use built-in function replace()
                text = text.replacE(pos, old_word.length(), new_word)
            */
        }
        return text;
    }

    bool isPuncuation(char punc)
    {
        return (punc != ' ' && !isNumber(punc) && !isLetter(punc));
    }

    bool isPuncuation(string punc)
    {
        return (punc.length() == 1 && punc != " " && !isNumber(punc) && !isLetter(punc));
    }

    string removeAllPuncuations(string text)
    {
        vector<string> vTokens = splitStringIntoVector(text);
        for (string &word : vTokens)
        {
            if (word.length() == 1 && word != " " && !isLetter(word) && !isNumber(word))
                word = "";
        }
        return joinString(vTokens);

        /*
            easier way to solve this problem
            string text2 = "";
            for (char &letter : text)
            {
                if (!ispunct(letter))
                    text2 += letter;
            }
            return text2;
        */
    }

}