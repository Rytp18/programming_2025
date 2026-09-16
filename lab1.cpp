#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

using namespace std;

int categoryOf(wchar_t c) {
    static const wstring vowels = L"аеёиоуыэюяАЕЁИОУЫЭЮЯ";
    static const wstring consonants = L"бвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШЩ";
    if (c == L'@') return -1;
    if (vowels.find(c) != wstring::npos) return 0;
    if (consonants.find(c) != wstring::npos) return 1;
    if (c >= L'0' && c <= L'9') return 2;
    return 3;
}

int main() {
    _setmode(_fileno(stdin), _O_U16TEXT);
    _setmode(_fileno(stdout), _O_U16TEXT);

    wstring input;
    wcout << L"Введите строку (не более 50 символов): ";
    getline(wcin, input);
    if (input.size() > 50) input = input.substr(0, 50);

    vector<vector<wchar_t>> arr(4);
    for (wchar_t c : input) {
        int cat = categoryOf(c);
        if (cat == -1) continue;
        bool found = false;
        for (wchar_t x : arr[cat]) {
            if (x == c) {
                found = true;
                break;
            }
        }
        if (!found) arr[cat].push_back(c);
    }

    const wstring names[4] = { L"Гласные: ", L"Согласные: ", L"Цифры: ", L"Знаки и символы: " };
    for (int i = 0; i < 4; i++) {
        wcout << names[i];
        for (wchar_t c : arr[i]) {
            if (c == L' ') wcout << L"[пробел] ";
            else wcout << c << L' ';
        }
        wcout << endl;
    }

    wstring result = input + L"+123АБВ";

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hConsole, &info);
    WORD defaultAttr = info.wAttributes;

    WORD red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    WORD blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    WORD green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    WORD yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

    for (wchar_t c : result) {
        if (c == L'@') {
            SetConsoleTextAttribute(hConsole, defaultAttr);
            wcout << c;
            continue;
        }
        int cat = categoryOf(c);
        WORD color = defaultAttr;
        if (cat == 0) color = red;
        else if (cat == 1) color = blue;
        else if (cat == 2) color = green;
        else if (cat == 3) color = yellow;
        SetConsoleTextAttribute(hConsole, color);
        wcout << c;
    }
    SetConsoleTextAttribute(hConsole, defaultAttr);
    wcout << endl;

    return 0;
}
