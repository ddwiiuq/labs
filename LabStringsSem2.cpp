#include <iostream>
#include <fstream>
#include <cstring>
#include <climits>
#include <windows.h>

using namespace std;

const int MAX_INPUT_STR = 100;      
const int MAX_WORD_LEN = 256;       
const int MAX_RAW_WORD_LEN = 1024;  
const int MAX_WORDS = 1000;         

const char* VOWELS = "аеёиоуъыьэюя";
const char* CONSONANTS = "бвгджзйклмнпрстфхцчшщ";
const char* PUNCTUATION = ".,!?:;-\"'()[]{}<>";

bool isVowel[256] = { false };
bool isConsonant[256] = { false };
bool isRussian[256] = { false };

void initTables() {
    const char* vowels_lower = VOWELS;
    const char* vowels_upper = "АЕЁИОУЪЫЬЭЮЯ";
    for (const char* p = vowels_lower; *p; ++p) {
        unsigned char c = static_cast<unsigned char>(*p);
        isVowel[c] = true;
        isRussian[c] = true;
    }
    for (const char* p = vowels_upper; *p; ++p) {
        unsigned char c = static_cast<unsigned char>(*p);
        isVowel[c] = true;
        isRussian[c] = true;
    }
    const char* cons_lower = CONSONANTS;
    const char* cons_upper = "БВГДЖЗЙКЛМНПРСТФХЦЧШЩ";
    for (const char* p = cons_lower; *p; ++p) {
        unsigned char c = static_cast<unsigned char>(*p);
        isConsonant[c] = true;
        isRussian[c] = true;
    }
    for (const char* p = cons_upper; *p; ++p) {
        unsigned char c = static_cast<unsigned char>(*p);
        isConsonant[c] = true;
        isRussian[c] = true;
    }
}

void printCharTable() {
    cout << "--- Таблица символов и их кодов (десятичные) ---\n";

    cout << "Английские заглавные:\n";
    for (char c = 'A'; c <= 'Z'; ++c)
        cout << c << '=' << static_cast<int>(c) << ' ';
    cout << "\n\nАнглийские строчные:\n";
    for (char c = 'a'; c <= 'z'; ++c)
        cout << c << '=' << static_cast<int>(c) << ' ';

    cout << "\n\nРусские заглавные (А-Я):\n";
    for (int c = 192; c <= 223; ++c)
        cout << static_cast<unsigned char>(c) << '=' << c << ' ';
    cout << "\n\nРусские строчные (а-я):\n";
    for (int c = 224; c <= 255; ++c)
        cout << static_cast<unsigned char>(c) << '=' << c << ' ';

    cout << "\n\nБуквы Ё и ё:\n";
    unsigned char yo = 168; // Ё
    cout << yo << '=' << static_cast<int>(yo) << ' ';
    yo = 184; // ё
    cout << yo << '=' << static_cast<int>(yo) << '\n';

    cout << "\nЦифры:\n";
    for (char c = '0'; c <= '9'; ++c)
        cout << c << '=' << static_cast<int>(c) << ' ';

    cout << "\n\nЗнаки препинания:\n";
    for (const char* p = PUNCTUATION; *p; ++p) {
        unsigned char uc = static_cast<unsigned char>(*p);
        cout << *p << '=' << static_cast<int>(uc) << ' ';
    }
    cout << "\n-----------------------------------------\n" << endl;
}

bool isPunctuation(char c) {
    for (const char* p = PUNCTUATION; *p; ++p)
        if (c == *p) return true;
    return false;
}

bool isEnglishLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

bool isPartOfWord(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return isRussian[uc] || isEnglishLetter(c) || (c >= '0' && c <= '9') || c == '-';
}

bool isAlnumCustom(char c) {
    unsigned char uc = static_cast<unsigned char>(c);
    return isRussian[uc] || isEnglishLetter(c) || (c >= '0' && c <= '9');
}

void toLowerString(char* s) {
    for (; *s; ++s) {
        unsigned char c = static_cast<unsigned char>(*s);
        if (c >= 'A' && c <= 'Z')
            *s = c - 'A' + 'a';
        else if (c >= 192 && c <= 223)       
            *s = c + 32;                     
        else if (c == 168)                    // Ё
            *s = 184;                          // ё
    }
}

void task1() {
    cout << "========== Задача 1 ==========" << endl;
    char str[MAX_INPUT_STR + 1];
    cout << "Введите строку (не более " << MAX_INPUT_STR << " символов): ";
    cin.getline(str, MAX_INPUT_STR + 1);

    if (cin.fail()) {
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cerr << "Строка слишком длинная, будет обрезана." << endl;
    }

    int i = 0, j = 0;
    while (str[i]) {
        if (!isPunctuation(str[i]))
            str[j++] = str[i];
        ++i;
    }
    str[j] = '\0';

    cout << "Результат: " << str << "\n" << endl;
}

void task2() {
    cout << "========== Задача 2 ==========" << endl;

    ifstream fin("input.txt");
    if (!fin) {
        cerr << "Ошибка: не удалось открыть файл input.txt" << endl;
        return;
    }
    int N;
    fin >> N;
    if (fin.fail() || N <= 0) {
        cerr << "Ошибка: в файле input.txt должно быть положительное целое число" << endl;
        return;
    }
    fin.close();
    cout << "N = " << N << " (из файла input.txt)" << endl;

    ifstream ftext("text.txt");
    if (!ftext) {
        cerr << "Ошибка: не удалось открыть файл text.txt" << endl;
        return;
    }

    struct Word {
        char text[MAX_WORD_LEN + 1];
        int len;        
    };
    Word words[MAX_WORDS];
    int wordCount = 0;

    char rawWord[MAX_RAW_WORD_LEN + 1];
    int rawPos = 0;
    bool inWord = false;
    char ch;

    auto processRawWord = [&]() {
        if (rawPos == 0) return;
        rawWord[rawPos] = '\0';

        int start = -1;
        for (int i = 0; i < rawPos; ++i) {
            if (isAlnumCustom(rawWord[i])) {
                start = i;
                break;
            }
        }
        if (start == -1) return;

        int end = -1;
        for (int i = rawPos - 1; i >= start; --i) {
            unsigned char uc = static_cast<unsigned char>(rawWord[i]);
            if (isRussian[uc] || isEnglishLetter(rawWord[i])) {
                end = i;
                break;
            }
        }
        if (end == -1) return;   

        int wordLen = end - start + 1;
        if (wordLen > MAX_WORD_LEN) {
            cerr << "Предупреждение: слово слишком длинное, пропущено." << endl;
            return;
        }
        char word[MAX_WORD_LEN + 1];
        strncpy_s(word, sizeof(word), rawWord + start, wordLen);
        word[wordLen] = '\0';

        toLowerString(word);

        int vowels = 0, consonants = 0;
        for (int i = 0; word[i]; ++i) {
            unsigned char uc = static_cast<unsigned char>(word[i]);
            if (isVowel[uc])
                ++vowels;
            else if (isConsonant[uc])
                ++consonants;
        }

        if (vowels == consonants && vowels > 0) {
            for (int i = 0; i < wordCount; ++i) {
                if (strcmp(words[i].text, word) == 0)
                    return;
            }
            if (wordCount >= MAX_WORDS) {
                cerr << "Предупреждение: превышен лимит количества слов." << endl;
                return;
            }
            strcpy_s(words[wordCount].text, word);
            words[wordCount].len = wordLen;
            ++wordCount;
        }
        };

    while (ftext.get(ch)) {
        if (isPartOfWord(ch)) {
            if (!inWord) {
                inWord = true;
                rawPos = 0;
            }
            if (rawPos < MAX_RAW_WORD_LEN)
                rawWord[rawPos++] = ch;
        }
        else {
            if (inWord) {
                processRawWord();
                inWord = false;
            }
        }
    }
    if (inWord)
        processRawWord();

    ftext.close();

    if (wordCount == 0) {
        cout << "Нет слов, удовлетворяющих условию." << endl;
        ofstream fout("result.txt");
        fout.close();
        return;
    }

    for (int i = 0; i < wordCount - 1; ++i) {
        for (int j = 0; j < wordCount - i - 1; ++j) {
            if (words[j].len < words[j + 1].len) {
                Word tmp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = tmp;
            }
        }
    }

    ofstream fout("result.txt");
    if (!fout) {
        cerr << "Ошибка: не удалось создать файл result.txt" << endl;
        return;
    }
    int limit = (N < wordCount) ? N : wordCount;
    for (int i = 0; i < limit; ++i)
        fout << words[i].text << endl;
    fout.close();

    cout << "Результат записан в файл result.txt (" << limit << " слов)" << endl;
}

int main() {
    SetConsoleCP(1251);        // для ввода
    SetConsoleOutputCP(1251);  // для вывода

    initTables();          
    printCharTable();      
    task1();               
    task2();               

    return 0;
}