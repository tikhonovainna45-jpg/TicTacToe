#include <iostream>
#include <string>
#include <cctype> // для tolower
using namespace std;

// Функция для отрисовки игрового поля
void drawBoard(char brd[9]) {
    cout << "\n " << brd[0] << " | " << brd[1] << " | " << brd[2] << " \n";
    cout << "-----------\n";
    cout << " " << brd[3] << " | " << brd[4] << " | " << brd[5] << " \n";
    cout << "-----------\n";
    cout << " " << brd[6] << " | " << brd[7] << " | " << brd[8] << " \n";
}

// Функция для отображения правил
void showRules() {
    cout << "==============================\n";
    cout << "        КРЕСТИКИ-НОЛИКИ        \n";
    cout << "==============================\n";
    cout << "Вводите числа 1-9 для хода\n";
    cout << "Поле выглядит так:\n";
    cout << " 1 | 2 | 3 \n";
    cout << "-----------\n";
    cout << " 4 | 5 | 6 \n";
    cout << "-----------\n";
    cout << " 7 | 8 | 9 \n";
    cout << "==============================\n";
}

// Функция для проверки победителя
char checkWinner(char brd[9]) {
    int lines[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // горизонтали
        {0,3,6}, {1,4,7}, {2,5,8}, // вертикали
        {0,4,8}, {2,4,6}           // диагонали
    };
    
    for (int i = 0; i < 8; ++i) {
        if (brd[lines[i][0]] != ' ' &&
            brd[lines[i][0]] == brd[lines[i][1]] &&
            brd[lines[i][1]] == brd[lines[i][2]]) {
            return brd[lines[i][0]];
        }
    }
    return 0;
}

// Функция для проверки заполненности поля
bool isFull(char brd[9]) {
    for (int i = 0; i < 9; ++i) {
        if (brd[i] == ' ') return false;
    }
    return true;
}

// Функция для сброса игрового поля
void resetBoard(char brd[9]) {
    for (int i = 0; i < 9; ++i) {
        brd[i] = ' ';
    }
}

// Функция для проверки ответа "да"
bool isYesAnswer(string answer) {
    // Приводим строку к нижнему регистру для удобства сравнения
    for (char &c : answer) c = tolower(c);
    return (answer == "да" || answer == "yes" || answer == "д" || answer == "y");
}

int main() {
    string rep;
    char brd[9];
    
    do {
        showRules();
        resetBoard(brd);
        
        char cur = 'X';
        bool ovr = false;
        int move;
        
        while (!ovr) {
            cout << "\n==============================\n";
            cout << "Сейчас ходит: " << cur << endl;
            drawBoard(brd);
            
            cout << "\nИгрок " << cur << ", ваш ход (1-9): ";
            cin >> move;
            
            // Проверка корректности ввода
            if (move < 1 || move > 9) {
                cout << "Ошибка! Только числа от 1 до 9!\n";
                continue;
            }
            
            if (brd[move - 1] != ' ') {
                cout << "Ошибка! Здесь уже занято! Выберите другое место.\n";
                continue;
            }
            
            // Делаем ход
            brd[move - 1] = cur;
            
            // Проверяем победу
            char winner = checkWinner(brd);
            bool full = isFull(brd);
            
            if (winner) {
                cout << "\n==============================\n";
                cout << "Игра окончена!\n";
                drawBoard(brd);
                cout << "\nПоздравляем! Победил игрок " << winner << "!\n";
                ovr = true;
            }
            else if (full) {
                cout << "\n==============================\n";
                cout << "Игра окончена!\n";
                drawBoard(brd);
                cout << "\nНичья! Все клетки заполнены.\n";
                ovr = true;
            }
            else {
                // Меняем игрока
                cur = (cur == 'X') ? 'O' : 'X';
            }
        }
        
        cout << "\n==============================\n";
        cout << "Сыграем еще? (да/нет): ";
        cin >> rep;
        
    } while (isYesAnswer(rep));
    
    cout << "\nСпасибо за игру! До встречи!\n";
    return 0;
}
