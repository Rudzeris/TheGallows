#include <iostream>
#include <fstream>
#include <vector>
#include <Windows.h>
#include <random>
#include <ctime>

using namespace std;

const string name = "Rudzeris: ";
const string gameName = "Виселица: ";

vector<string>* words(vector<string>* wordList) { // Собирает информацию из файла и добавляет в вектор
    ifstream file;
    char* fileName = new char[15];
    fileName = (char*)"words.txt";
    file.open(fileName);
    if (!file.is_open()) cout <<name<< "\"Чтобы продолжить игру, следуй по инструкции: \n\
        1) Нужно создать файл с названием \"words.txt\" около .exe файла.\n\
        2) Осталось заполнить файл \"words.txt\" любыми словами для нашей игры.\"\n";
    while (!file.is_open()) {
        file.open(fileName);
        Sleep(2000);
    }
    cout << name<<"\"Файл нашелся. Продолжаем.\"\n";
    if (file.peek() == EOF)
        cout << name<<"\"Ваш файл \"words.txt\" пуст. Пожалуйста, заполните его.\"\n";
    while (file.peek() == EOF){
        file.close();
        Sleep(2000);
        file.open(fileName);
    }
    string a;
    while (!file.eof()) {
        file >> a;
        (*wordList).push_back(a);
    }
    file.close();
    return wordList;
}

string search(string y,string x,char w) { // Поиск и открытие нужных букв
    unsigned short q = 0;
    for (unsigned short i = 0; i < y.length(); i++)
    {
        if (y[i] == w) {
            x[i] = w;
            q++;
        }
    }
    cout << gameName << "\"";
    if (q) {
        if (q % 10 >= 1 && q % 10 <= 4 and !(q >= 10 && q <= 20))
            cout << "Открылась " << q << " буква.";
        else
            cout << "Открылось " << q << " букв.";
    }
    else {
        cout << "Буква не нашлась.";
    }
    cout << "\"";
    return x;
}

char* replay(char y,unsigned short x) { // Повторить в выводе '-' несколько раз
    x++;
    char* q;
    q = new char[x+2];
    q[0] = '\n';
    for (unsigned short i = 1; i <= x; i++)
    {
        q[i] = y;
    }
    q[x] = '\0';
    return q;
}

void vectorshow(vector<string> list) { // Вывод вектора (только для админа)
    cout << name << "\"\n\\*\nВ файле такие слова: ";
    for (unsigned short i = 0; i < list.size(); i++)
        cout << list[i] << ((i<list.size()-1)?(", "):("\n*\\"));
}

void game(string y) { // Сама игра, которая повторяет ввод и проверку
    cout << gameName << "\"Игра началась!\"\n\n";
    cout << gameName << "\"Дано слово, оно состоит из " << y.length() << " букв:\"";
    string x=y;
    char q;
    for (unsigned short i = 0; i < y.length(); i++)
    {
        x[i] = '#';
    }
    cout << replay('-',x.length()) << endl << x << replay('-',x.length()) << endl;

    while (x != y) {
        cout << "Какую букву открыть? - "; cin >> q;
        x=search(y, x, q);
        cout << replay('-',x.length()) << endl << x << replay('-',x.length()) << endl;
    }
    cout << gameName << "\"Победа!\"";
}

int main()
{
    char buffer[256]; // буфер
    DWORD size; // размер
    size = sizeof(buffer); // размер буфера
    GetComputerNameA(buffer, &size); // Берем имя компьютера
    string userName = buffer;
    string Admin = "RUDZERIS";
    srand(time(NULL));
    setlocale(LC_ALL, "rus");
    cout << name << "\"Привет. Я создал для тебя маленькую игру под названием \'Виселица\'.\"\n";
    vector<string>* a=new vector<string>;
    try {
        a=words(a);
        unsigned short q;
        unsigned short x;

        do {
            cout << replay('\n', 4);
            x = rand() % a->size();
            game((*a)[x]);
            cout << replay('\n', 2);
            cout << name << "\"Хочешь повторить игру? (1 - \'да\',2 - \'нет\',3 \'собрать с файла новые слова\')\" >> ";
            cin >> q;
            if (q == 3) {
                q = 1;
                a = words(a);
                a->resize(unique(a->begin(), a->end()) - a->begin());
                if (userName == Admin) vectorshow(*a);
            }
        } while (q==1);
    }
    catch (string as) {
        cout << "Error: " + as << endl;
    }
}