                                                                                            /*Данная программа создана для решения компьютером 
                                                                                            логической головоломки "Неравенство" с помощью 
                                                                                            введенных пользователем изначальных данных
                                                                                            */
#include <iostream>

using namespace std;

const int MAX_SIZE = 10;


void shuffleArray(int values[], int size) {                                                 //Функция предназначена для перемешивания элементов в массиве значений
    for (int i = size - 1; i > 0; i--) {                                                    //Цикл для перемешивания элементов случайным образом
        int j = rand() % (i + 1);                                                           //Генерация случайного числа j в диапазоне от 0 до i
        int temp = values[i];                           
        values[i] = values[j];                                                              
        values[j] = temp;
    }
}


bool fillMatrix(int matrix[][MAX_SIZE], int values[], int size, int row, int col) {         //Функция заполнения матрицы
    if (row == size) {                                                                      //Если все строки заполнены, возвращается значение true
        return true;
    }

    shuffleArray(values, size);                                                             //Вызов функции для перемешивания массива значений  

    if (matrix[row][col] != 0) {                                                            //Проверяется, заполнена ли ячейка

        if (col < size - 1) {                                                               //Проверяется, остались ли ячейки в строке для заполнения
            if (fillMatrix(matrix, values, size, row, col + 1)) {                           //Заполнение следующей ячейки в строке
                return true;
            }
        }
        else {
            if (fillMatrix(matrix, values, size, row + 1, 0)) {                             //Начало заполнения следующей строки
                return true;
            }
        }
    }
    else {                                                                                  //Если ячейка не заполнена
        for (int i = 0; i < size; i++) {                                                    //Перебор значений из массива значений
            bool isValueUsed = false;                                                       //Логическая переменная для отслеживания, было ли уже использовано 
                                                                                            //значение values[i] в текущей строке или столбце.


            for (int j = 0; j < col; j++) {                                                 //Перебор индексов столбцов
                if (matrix[row][j] == values[i]) {                                          //Проверяет, использовалось ли значение из массива значений
                    isValueUsed = true;                                                     //Если использовалось, то возвращается true
                    break;
                }
            }


            for (int j = 0; j < row; j++) {                                                 //Перебор индексов строк
                if (matrix[j][col] == values[i]) {                                          //Проверяет, использовалось ли значение из массива значений
                    isValueUsed = true;                                                     //Если использовалось, то возвращается true
                    break;
                }
            }

            if (!isValueUsed) {                                                             //Если значение не использовалось
                matrix[row][col] = values[i];                                               //Присваивает текущей ячейке значение, которое еще не было использовано.


                if (col < size - 1) {                                                       //Если текущая ячейка не последняя в строке, то заполняется следующая
                    if (fillMatrix(matrix, values, size, row, col + 1)) {
                        return true;
                    }
                }
                else {
                    if (fillMatrix(matrix, values, size, row + 1, 0)) {                     //Иначе начинает заполняться следующая строка
                        return true;
                    }
                }

                matrix[row][col] = 0;
            }
        }
    }
    return false;
}


void printMatrix(int matrix[][MAX_SIZE], int size) {                                        //Функция для вывода матрицы
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


bool checkRowUnique(int matrix[][MAX_SIZE], int size, int row, int col) {                   //Функция для проверки уникальности значения в строке
    int value = matrix[row][col];                                                           //Переменной value присваивается значение текущей ячейки
    for (int i = 0; i < size; i++) {                                                        //Перебор элементов в строке
        if (i != col && matrix[row][i] == value) {                                          //Если значение уже присутствует в строке, то возвращается false
            return false;
        }
    }
    return true;
}


bool checkColumnUnique(int matrix[][MAX_SIZE], int size, int row, int col) {                //Функция для проверки уникальности значения в столбце
    int value = matrix[row][col];                                                           //Переменной value присваивается значение текущей ячейки
    for (int i = 0; i < size; i++) {                                                        //Перебор элементов в столбце
        if (i != row && matrix[i][col] == value) {                                          //Если значение уже присутствует в столбце, то возвращается false
            return false;
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");
    int n;
    cout << "Введите размер матрицы: ";
    while (!(cin >> n) || n <= 0) {
        cout << "Ошибка ввода. Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    int matrixStart[MAX_SIZE][MAX_SIZE] = {};                                              
    int matrix[MAX_SIZE][MAX_SIZE] = {};
    int values[MAX_SIZE];
    int valuesComp[MAX_SIZE][4];


    for (int i = 0; i < n; i++) {
        values[i] = i + 1;
    }


    int initialCount;
    cout << "Введите количество начальных элементов: ";
    while (!(cin >> initialCount) || initialCount <= 0) {                                   //Ввод количества начальных элементов матрицы
        cout << "Некорректный ввод. Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < initialCount; i++) {                                                //Ввод начальных элементов матрицы
        int row, col, value;
        cout << "Введите индексы и значение элемента (строка столбец значение): ";
        while (!(cin >> row >> col >> value) || row < 0 || row >= n || col >= n || col < 0) {
            cout << "Некорректный ввод. Введите число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        matrixStart[row][col] = value;
    }


    int initialComp;                                                                        //Число сравнений в матрице
    cout << "Введите количество сравнений в матрице: ";
    while (!(cin >> initialComp) || initialComp < 0) {
        cout << "Некорректный ввод. Введите число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    for (int i = 0; i < initialComp; i++)                                                   //Задаются сравнения
    {
        cout << "Сравнение " << i + 1 << endl;
        int row, col;
        cout << "Введите индексы большего элемента (строка столбец): ";
        while (!(cin >> valuesComp[i][0] >> valuesComp[i][1]) || valuesComp[i][0] < 0 || valuesComp[i][0] >= n || valuesComp[i][1] < 0 || valuesComp[i][1] >= n) {
            cout << "Некорректный ввод. Попробуйте ещё раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cout << "Введите индексы меньшего элемента (строка столбец): ";
        while (!(cin >> valuesComp[i][2] >> valuesComp[i][3]) || valuesComp[i][2] < 0 || valuesComp[i][2] >= n || valuesComp[i][3] < 0 || valuesComp[i][3] >= n) {
            cout << "Некорректный ввод. Попробуйте ещё раз: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    while (true)
    {
        for (int i = 0; i < n; i++)                                                         //Перебор по всем строкам и столбцам матрицы
            for (int j = 0; j < n; j++)
                matrix[i][j] = matrixStart[i][j];                                           //Каждая ячейка копируется из матрицы matrixStart, чтобы начать
                                                                                            //новую попытку заполнения матрицы
        if (fillMatrix(matrix, values, n, 0, 0)) {                                          //Если матрица успешно заполнена, то происходит проверка на ее валидность

            bool isMatrixValid = true;

            for (int i = 0; i < n; i++) {                                                   //Если матрица не является уникальной по строкам и столбцам, то не валидна
                for (int j = 0; j < n; j++) {
                    if (!checkRowUnique(matrix, n, i, j) || !checkColumnUnique(matrix, n, i, j)) {
                        isMatrixValid = false;
                        break;
                    }
                }
            }

            if (isMatrixValid) {                                                            //Если матрица валидна, то проводится проверка заданных сравнений
                for (int i = 0; i < initialComp; i++)
                    if (matrix[valuesComp[i][0]][valuesComp[i][1]] < matrix[valuesComp[i][2]][valuesComp[i][3]])
                    {
                        isMatrixValid = false;                                              //Если сравнение не выполнено, то возвращается false
                        shuffleArray(values, n);                                            //и происходит перезапуск цикла с перемешиванием значений
                        break;
                    }
                if (isMatrixValid) {
                    cout << "Матрица заполнена успешно:" << endl;
                    printMatrix(matrix, n);                                                 //Если заполнение успешно, то вызывается функция вывода матрицы
                    break;
                }
            }
            else {
                shuffleArray(values, n);
                continue;
            }
        }
        else {
            cout << "Не удалось заполнить матрицу." << endl;
            break;
        }
    }
    return 0;
}