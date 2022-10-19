// Lab2_OS_Kursovoi.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include<Windows.h>
//#include <heapapi.h>
#include <vector>

PROCESS_HEAP_ENTRY entry{}; // структура для прохода по куче
//vector<void*> blocks;
using namespace std;
size_t overhead;
size_t tot_free;
size_t max_free;
size_t total;
size_t size_a;
HANDLE heap;

void task1()
{
    cout << "\n1\n";
    heap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, (SIZE_T)(24 * 1024)); // создание кучи 24 кбайт
    if (!heap) {
        return exit(0);
    }
    system("pause");
}

void task2() 
{
    cout << "\n2\n";
    while (HeapAlloc(heap, HEAP_ZERO_MEMORY, rand() % 992 + 32));
    system("pause");
}

void task3()
{
    cout << "\n3\n";
    total = 0;
    overhead = 0;
    while (HeapWalk(heap, &entry))
    {
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) // блок
        {
            total += entry.cbData;
            overhead += entry.cbOverhead;
        }
    }
    auto tot_sum = total + overhead;
    cout << "total - " << total << "\n";
    cout << "overhead - " << overhead << "\n";
    cout << "total summ - " << tot_sum << "\n";
    cout << "rest - " << (24 * 1024) - tot_sum << "\n";
    system("pause");
}

void task4() 
{
    cout << "\n4\n";
    LPVOID free = nullptr; // ссылка на блок который будет освобождаться
    entry.lpData = nullptr; // для нового прохода по блокам кучи
    while (HeapWalk(heap, &entry)) 
    {
        if (free)
        {
            HeapFree(heap, 0, free); // освобождение
            free = nullptr;
        }
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
        {
            free = rand() % 3 == 0 ? entry.lpData : nullptr; // если выпала 0, то запоминаем указатель для освобождения
        }
    }
    if (free)
    {
        HeapFree(heap, 0, free); // освобождение
        free = nullptr;
    }

    system("pause");
}

void task5()
{
    cout << "\n5\n";
    total = 0;
    overhead = 0;
    tot_free = 0;
    max_free = 0;
    entry.lpData = nullptr;
    while(HeapWalk(heap, &entry))
    {
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY) 
        {
            total += entry.cbData;
            overhead += entry.cbOverhead;
        }
        else if (!entry.wFlags)  // свободный блок
        {
            tot_free += entry.cbData; // обьем свобоных блоков
            if (max_free < entry.cbData) 
            {
                max_free = entry.cbData;
            }
        }
    }
    auto tot_sum = total + overhead;
    cout << "total  -" << total << "\n";
    cout << "overhead  -" << overhead << "\n";
    cout << "tottal_summ  -" << tot_sum << "\n";
    cout << "rest  -" << (24 * 1024) - tot_sum << "\n";
    cout << "total free - " << tot_free << "\n";
    cout << "max free - " << max_free << "\n";

    system("pause");
}

void task6()
{
    cout << "\n6\n";
    LPVOID p = nullptr;
    size_a = max_free - 16 > 0 ? max_free - 16 : max_free;
    cout << "size - " << size_a << "\n";
    if (p = HeapAlloc(heap, 0, size_a)) // пытаемся выделить блок
    {
        cout << "SUCCESS" << "\n";
        HeapFree(heap, 0, p);
    }
    else
    {
        cout << "FAILED" << "\n";
    }
    cout << "-----" << "\n";
    size_a = tot_free - 16 > 0 ? tot_free - 16 : tot_free;
    cout << "size - " << size_a << "\n";
    if (p = HeapAlloc(heap, 0, size_a))
    {
        cout << "SUCCESS" << "\n";
        HeapFree(heap, 0, p);
    }
    else
    {
        cout << "FAILED" << "\n";
    }
    system("pause");
}

void task7() 
{
    cout << "\n7\n";
    HeapDestroy(heap);
    system("pause");
}

void task8() 
{
    cout << "\n8\n";
    heap = HeapCreate(HEAP_NO_SERIALIZE, 0, (24 * 1024));
    if (!heap)
    {
        exit(0);
    }
    size_a = 1;
    while (HeapAlloc(heap, 0, size_a++));
    entry.lpData = nullptr;
    while (HeapWalk(heap, &entry)) 
    {
        if (entry.wFlags & PROCESS_HEAP_ENTRY_BUSY)
        {
            cout << entry.cbData << " | " << (unsigned)entry.cbOverhead << "\n";
        }
    }
    system("pause");
}

void task9() 
{
    cout << "\n9 heap destroy\n";
    HeapDestroy(heap);
    system("pause");
}

int main()
{
    srand(time(NULL));
    system("pause");
    task1();
    task2();
    task3();
    task4();
    task5();
    task6();
    task7();
    task8();
    task9();
}