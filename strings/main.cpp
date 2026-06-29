#include <iostream>
#include <string>
#include <sstream> 
#include <vector>  
#include <algorithm>
#include <Windows.h>

using namespace std;

string toLowerCase(string str) {
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = tolower((unsigned char)str[i]);
    }
    return str;
}

int main() {
    
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    
    // 1) ѕоиск символа в строке, его индексов и количества совпадений
    
    cout << "=== 1 ===\n";
    string text1;
    char targetChar;

    cout << "¬ведите строку текста: ";
    getline(cin, text1); 

    cout << "¬ведите символ дл€ поиска: ";
    cin >> targetChar;
    cin.ignore(); 

    int countMatches = 0;
    cout << "»ндексы совпадений: ";
    for (size_t i = 0; i < text1.length(); ++i) {
        if (text1[i] == targetChar) {
            cout << i << " ";
            countMatches++;
        }
    }

    if (countMatches == 0) {
        cout << "совпадений не найдено";
    }
    cout << "\n оличество совпадений: " << countMatches << "\n\n";


    // 2) ѕодсчет средней длины слова в предложении
   
    cout << "=== 2 ===\n";
    string text2;
    cout << "¬ведите предложение: ";
    getline(cin, text2);

    stringstream ss2(text2);
    string word2;
    int totalLetters = 0;
    int wordCount2 = 0;

    while (ss2 >> word2) {
        
        while (!word2.empty() && ispunct((unsigned char)word2.back())) word2.pop_back();
        while (!word2.empty() && ispunct((unsigned char)word2.front())) word2.erase(0, 1);

        if (!word2.empty()) {
            totalLetters += word2.length();
            wordCount2++;
        }
    }

    if (wordCount2 > 0) {
        double averageLength = (double)totalLetters / wordCount2;
        cout << "—редн€€ длина слова: " << averageLength << " букв(ы)\n\n";
    }
    else {
        cout << "—лова не найдены.\n\n";
    }


    // 3) —колько раз определенное слово содержитс€ в строке текста
    
    cout << "=== 3 ===\n";
    string text3, targetWord;
    cout << "¬ведите строку текста: ";
    getline(cin, text3);
    cout << "¬ведите искомое слово: ";
    cin >> targetWord;
    cin.ignore();

    string lowerText3 = toLowerCase(text3);
    string lowerTarget = toLowerCase(targetWord);

    stringstream ss3(lowerText3);
    string word3;
    int targetWordCount = 0;

    while (ss3 >> word3) {
       
        while (!word3.empty() && ispunct((unsigned char)word3.back())) word3.pop_back();
        while (!word3.empty() && ispunct((unsigned char)word3.front())) word3.erase(0, 1);

        if (word3 == lowerTarget) {
            targetWordCount++;
        }
    }
    cout << "—лово \"" << targetWord << "\" встречаетс€ " << targetWordCount << " раз(а).\n\n";


    // 4) —пам-фильтр
    
    cout << "=== 4 ===\n";
    string spamText;
    cout << "¬ведите текст дл€ проверки на спам: ";
    getline(cin, spamText);

    vector<string> badWords = { "viagra", "xxx", "buy", "free" };

    string lowerSpamText = toLowerCase(spamText);
    bool isSpam = false;

    for (const string& badWord : badWords) {
        if (lowerSpamText.find(badWord) != string::npos) {
            isSpam = true;
            break;
        }
    }

    if (isSpam) {
        cout << "=> Ё“ќ —ѕјћ!\n\n";
    }
    else {
        cout << "=> это не спам\n\n";
    }


    // 5) ѕроверка, €вл€етс€ ли строка палиндромом
    
    cout << "=== 5 ===\n";
    string text5;
    cout << "¬ведите строку дл€ проверки на палиндром:\n";
    getline(cin, text5);

    string cleanText = "";
    string lowerText5 = toLowerCase(text5);

    for (char c : lowerText5) {
        
        if (isalnum((unsigned char)c) || (c >= 'а' && c <= '€') || c == 'Є') {
            cleanText += c;
        }
    }

    bool isPalindrome = true;
    int len = cleanText.length();
    for (int i = 0; i < len / 2; ++i) {
        if (cleanText[i] != cleanText[len - 1 - i]) {
            isPalindrome = false;
            break;
        }
    }

    if (isPalindrome && !cleanText.empty()) {
        cout << "=> —трока я¬Ћя≈“—я палиндромом!\n";
    }
    else {
        cout << "=> —трока Ќ≈ я¬Ћя≈“—я палиндромом.\n";
    }

    return 0;
}