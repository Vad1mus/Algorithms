#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <chrono>

using namespace std;

#define N 6

int NewIndex(int x, int y)     //пересчет индексов
{
    int j = 0;
    for (int i = 0; i < x; i++) j += N - i;
    return j + y - x;
}
void Put(int vec[], int x, int y, int v)  // Запись в вектор (сжатие) 
{
    if (y >= x) vec[NewIndex(x, y)] = v;
}
int Get(int vec[], int x, int y) // Чтение из вектора 
{
    if (y >= x) return vec[NewIndex(x, y)];
    else return 0;
}
void RandArray(int a[N][N]) //формирование исходного массива
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (j == 0)
            {
                a[i][j] = rand() % 50;
                continue;
            }
            if (j%2 ==0) 
            {
                a[i][j] = rand() % 50;
            }
            else 
            {
                a[i] [j] = 0;
            }
        }
    }
}
void PrintArray(int a[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%3i", a[i][j]);
        printf("\n");
    }
}
void main()
{
    setlocale(LC_ALL, "RUS");

    int num1 = 0;
    int num2 = 0;
    int vec[N * N / 2 + N / 2];
    int array[N][N];
    RandArray(array);
    PrintArray(array);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            Put(vec, i, j, array[i][j]);	 //сжатие массива
    cout << "\n Массив после сжатия \n";
    for (int i = 0; i < N * N / 2 + N / 2; i++)	 //выдача результата сжатия
        printf("%3i", vec[i]);
    printf("\n\nПолучение елемента матрицы:\n\n");
    printf("Введите i координату\n");
    scanf_s("%d", &num1);
    printf("Введите  j координату\n");
    scanf_s("%d", &num2);
    int elem;
    auto begin = chrono::steady_clock::now();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (i == num1 && j == num2)
                elem = array[i][j];
        }
    }
    printf("Значение элемента - %d\n\n", elem);
    auto end = chrono::steady_clock::now();
    auto elapsed_ms = chrono::duration_cast<chrono::nanoseconds>(end - begin);
    cout << "Время доступа к элементу без сжатия: " << elapsed_ms.count() << "ns" << endl << endl << endl;
    printf("Получить значение с економного массива\n\n");
    printf("Введите i координату\n");
    scanf_s("%d", &num1);
    printf("Введите  j координату\n");
    scanf_s("%d", &num2);
    auto begin2 = chrono::steady_clock::now();
    printf("Значение элемента - %d\n\n", Get(vec, num1, num2));
    auto end2 = chrono::steady_clock::now();
    auto elapsed_ms2 = chrono::duration_cast<chrono::nanoseconds>(end2 - begin2);
    cout << "Время доступа к элементу одномерного массива: " << elapsed_ms2.count() << "ns" << endl;
    printf("\n\n");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)	//чтение из сжатого представления
            printf("%3i", Get(vec, i, j));
        printf("\n");
    }
    

}