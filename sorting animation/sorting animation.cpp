    #include <iostream>
    #include <Windows.h>
    #include <conio.h>

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

    using namespace std;

    void drawArrow(int length, int minPos, int curPos, int *arr)
    {
        for (int i = 0; i < length; i++)
        {
            if (i == minPos || i == curPos)
            {
                if(i == curPos)
                    cout << "\b";
                cout << "|";
                if (i == minPos)
                {
                    if (arr[i] < 10 && arr[i] > -10)
                        cout << "_";
                    else if (arr[i] < 100 && arr[i] > -100)
                        cout << "__";
                    else if (arr[i] < 1000 && arr[i] > -1000)
                        cout << "___";
                    cout << "_";
                }
            }
            else if (i > minPos && i < curPos)
            {
                if (arr[i] < 10 && arr[i] > -10)
                    cout << "_";
                else if (arr[i] < 100 && arr[i] > -100)
                    cout << "__";
                else if (arr[i] < 1000 && arr[i] > -1000)
                    cout << "___";
                cout << "_";
            }
            else
            {
                if (arr[i] < 10 && arr[i] > -10)
                    cout << " ";
                else if (arr[i] < 100 && arr[i] > -100)
                    cout << "  ";
                else if (arr[i] < 1000 && arr[i] > -1000)
                    cout << "   ";
                cout << " ";
            }
            Sleep(100);
        }
        cout << endl;
        cout << endl;
    }

    void sortingBySelection(int n, int* arr)
    {
        int minPos = 0, currentPos = 0, length = 0;

        while (minPos != n)
        {
            int tmp = arr[minPos];

            for (int i = minPos; i < n; i++)
            {
                if (tmp > arr[i])
                {
                    tmp = arr[i];
                    currentPos = i;

                    for (int k = 0; k < n; k++)
                    {
                        if (k < minPos)
                        {
                            cout << arr[k] << " ";
                        }
                        else if (k == minPos)
                        {
                            SetConsoleTextAttribute(console, FOREGROUND_RED);
                            cout << arr[k] << " ";
                            SetConsoleTextAttribute(console, 15);
                        }
                        else if (k == currentPos)
                        {
                            SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                            cout << arr[k] << " ";
                            SetConsoleTextAttribute(console, 15);
                        }
                        else
                            cout << arr[k] << " ";
                        Sleep(150);
                    }
                    cout << endl;
                    Sleep(500);
                }
            }

            if (tmp != arr[minPos])
            {
                drawArrow(n, minPos, currentPos, arr);
                Sleep(2000);
                system("cls");
                cout << endl;

                for (int k = 0; k < n; k++)
                {
                    if (k < minPos)
                    {
                        cout << arr[k] << " ";
                    }
                    else if (k == minPos)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_RED);
                        cout << arr[k] << " ";
                        SetConsoleTextAttribute(console, 15);
                    }
                    else if (k == currentPos)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        cout << arr[k] << " ";
                        SetConsoleTextAttribute(console, 15);
                    }
                    else
                        cout << arr[k] << " ";
                }
                Sleep(1000);
                system("cls");

                for (int j = 0; j < n; j++)
                {
                    if (j == (minPos + currentPos) / 2 + 1)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_RED);
                        cout << " " << arr[minPos];
                        SetConsoleTextAttribute(console, 15);
                    }
                    else
                        cout << " ";
                }
                cout << endl;
                for (int j = 0; j < n; j++)
                    if (j != minPos && j != currentPos)
                        cout << arr[j] << " ";
                    else
                        cout << " " << " ";
                cout << endl;
                for (int j = 0; j < n; j++)
                {
                    if (j == (minPos + currentPos) / 2 + 1)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        cout << " " << arr[currentPos];
                        SetConsoleTextAttribute(console, 15);
                    }
                    else
                        cout << " ";
                }
                cout << endl;
                Sleep(1000);
                system("cls");
                cout << endl;

                tmp = arr[minPos];
                arr[minPos] = arr[currentPos];
                arr[currentPos] = tmp;
            }

            for (int k = 0; k < n; k++)
            {
                if (k < minPos)
                {
                    cout << arr[k] << " ";
                }
                else if (k == minPos)
                {
                    SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                    cout << arr[k] << " ";
                    SetConsoleTextAttribute(console, 15);
                }
                else if (k == currentPos)
                {
                    SetConsoleTextAttribute(console, FOREGROUND_RED);
                    cout << arr[k] << " ";
                    SetConsoleTextAttribute(console, 15);
                }
                else
                    cout << arr[k] << " ";
            }
            cout << endl;
            Sleep(1500);
            system("cls");

            minPos++;

            for (int k = 0; k < n; k++)
            {
                if (k < minPos)
                {
                    cout << arr[k] << " ";
                }
                else
                    cout << arr[k] << " ";
                Sleep(150);
            }
            cout << endl;
            cout << endl;
        }
    }

    void sotringByInsertion(int n, int* arr)
    {
        int currentPos = 0;

        for (int i = 1; i < n; i++)
        {
            system("cls");
            for (int l = 0; l < n; l++)
            {
                if (l < currentPos + 1)
                {
                    cout << arr[l] << " ";
                }
                else
                    cout << arr[l] << " ";
            }
            cout << endl;

            if (arr[i - 1] > arr[i])
            {
                SetConsoleTextAttribute(console, FOREGROUND_RED);
                cout << arr[i - 1];
                SetConsoleTextAttribute(console, 15);
                Sleep(150);
                cout << " > ";
                SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                Sleep(150);
                cout << arr[i];
                SetConsoleTextAttribute(console, 15);
                cout << ":\n";
                currentPos = i;
            }
            else
            {
                SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                Sleep(150);
                cout << arr[i - 1];
                SetConsoleTextAttribute(console, 15);
                Sleep(150);
                cout << " < ";
                Sleep(150);
                cout << arr[i];
            }
            Sleep(1500);
            system("cls");
            cout << endl;

            for (int j = i; j > 0 && arr[j - 1] > arr[j]; j--)
            {
                for (int k = 0; k < n; k++)
                {
                    if (k < j - 1)
                    {
                        cout << arr[k] << " ";
                    }
                    else if (k == j - 1)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_RED);
                        cout << arr[k] << " ";
                        SetConsoleTextAttribute(console, 15);
                    }
                    else if (k == j)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        cout << arr[k] << " ";
                        SetConsoleTextAttribute(console, 15);
                    }
                    else
                        cout << arr[k] << " ";
                }
                Sleep(1000);
                system("cls");

                int tmp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = tmp;

                for (int k = 0; k < n; k++)
                {
                    if (k == (j + j - 1) / 2 + 1)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_RED);
                        cout << " " << arr[j - 1];
                        SetConsoleTextAttribute(console, 15);
                        break;
                    }
                    else
                        cout << " ";
                }
                cout << endl;
                for (int k = 0; k < n; k++)
                {
                    if (k < j - 1)
                    {
                        cout << arr[k] << " ";
                    }
                    else if (k != j - 1 && k != j)
                        cout << arr[k] << " ";
                    else
                        cout << " " << " ";
                }
                cout << endl;

                for (int k = 0; k < n; k++)
                {
                    if (k == (j + j - 1) / 2 + 1)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        cout << arr[j];
                        SetConsoleTextAttribute(console, 15);
                        break;
                    }
                    else
                        cout << " ";
                }
                cout << endl;
                Sleep(1000);
                system("cls");

                cout << endl;

                for (int k = 0; k < n; k++)
                {
                    if (k < j - 1)
                    {
                        cout << arr[k] << " ";
                    }
                    else if (k == j - 1)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        cout << arr[k] << " ";
                        SetConsoleTextAttribute(console, 15);
                    }
                    else if (k == j)
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_RED);
                        cout << arr[k] << " ";
                        SetConsoleTextAttribute(console, 15);
                    }
                    else
                        cout << arr[k] << " ";
                }

                cout << endl;
                Sleep(150);
                cout << endl;

                for (int l = j - 1; l > 0 && arr[l] < arr[l - 1]; l--)
                {
                    if (arr[l - 1] > arr[l])
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_RED);
                        cout << arr[l - 1];
                        SetConsoleTextAttribute(console, 15);
                        Sleep(150);
                        cout << " > ";
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        Sleep(150);
                        cout << arr[l];
                        SetConsoleTextAttribute(console, 15);
                        cout << ":\n";
                    }
                    else
                    {
                        SetConsoleTextAttribute(console, FOREGROUND_GREEN);
                        Sleep(150);
                        cout << arr[l - 1];
                        SetConsoleTextAttribute(console, 15);
                        Sleep(150);
                        cout << " < ";
                        Sleep(150);
                        cout << arr[l];
                    }
                }
            }
            Sleep(2000);
        }
    }

    int main()
    {
        setlocale(LC_ALL, "Rus");

        int chose = 0, n = 0;

        cout << "введите размер массива\n";
        cin >> n;

        int* arr = new int[n];

        for (int i = 0; i < n; i++)
        {
            cout << "Введите " << i+1 << " элемент массива: ";
            cin >> arr[i];
        }

        int minPos = 0, currentPos = 0, length = 0;

        for (int i = 0; i < n; i++)
        {
            if (arr[i] < 10 && arr[i] > -10)
                length++;
            else if (arr[i] < 100 && arr[i] > -100)
                length += 2;
            else if (arr[i] < 1000 && arr[i] > -1000)
                length += 3;
            if(i < n - 1)
                length++;
        }

        cout << "1. Сортировка выбором\n2. Сортировка вставкой" << endl;
        cin >> chose;
        system("cls");

        switch (chose)
        {
        case 1:
            sortingBySelection(n, arr);
            break;
        case 2:
            sotringByInsertion(n, arr);
            break;
        default:
            cout << "Ошибка!\n";
            break;
        }

        system("cls");
        for (int i = 0; i < n; i++)
            cout << arr[i] << " ";
        cout << endl;
        delete[] arr;
        system("pause");
    }