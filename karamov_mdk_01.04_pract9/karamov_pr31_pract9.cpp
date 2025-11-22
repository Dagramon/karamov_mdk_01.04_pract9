#include <iostream>
#include <Windows.h>
#include <conio.h>

volatile int countWORDS = 0;
volatile int countEXCELS = 0;
volatile int countPAINTS = 0;
volatile int countNOTEPADS = 0;

PROCESS_INFORMATION words[100];
PROCESS_INFORMATION excels[100];
PROCESS_INFORMATION paints[100];
PROCESS_INFORMATION notepads[100];

void CloseAll()
{
    for (int i = 0; i < countWORDS; i++)
    {
        TerminateProcess(words[i].hProcess, 0);
        CloseHandle(words[i].hThread);
        CloseHandle(words[i].hProcess);
    }
    for (int i = 0; i < countEXCELS; i++)
    {
        TerminateProcess(excels[i].hProcess, 0);
        CloseHandle(excels[i].hThread);
        CloseHandle(excels[i].hProcess);
    }
    for (int i = 0; i < countPAINTS; i++)
    {
        TerminateProcess(paints[i].hProcess, 0);
        CloseHandle(paints[i].hThread);
        CloseHandle(paints[i].hProcess);
    }
    for (int i = 0; i < countNOTEPADS; i++)
    {
        TerminateProcess(notepads[i].hProcess, 0);
        CloseHandle(notepads[i].hThread);
        CloseHandle(notepads[i].hProcess);
    }
    countWORDS = 0;
    countEXCELS = 0;
    countPAINTS = 0;
    countNOTEPADS = 0;
}

void Update(int count)
{
    system("cls");
    std::cout << std::endl << "counter: " << count << std::endl;
    std::cout << "1 - word\n2 - excel\n3 - paint\n4 - notepad\n5 - close word \n6 - close excel\n7 - close paint\n8 - close notepad\n9 - close all\nselect: ";
}

DWORD WINAPI Counter(LPVOID iNum)
{
    int count = 0;
    while (true)
    {
        Sleep(1000);
        count++;
        Update(count);
    }
}

int main()
{
    wchar_t appNameWord[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\WINWORD.exe";
    wchar_t appNameExcel[] = L"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.exe";
    wchar_t appNamePaint[] = L"C:\\WINDOWS\\system32\\mspaint.exe";
    wchar_t appNameNotepad[] = L"C:\\WINDOWS\\system32\\notepad.exe";
    wchar_t counterApp[255] = L"C:\\Users\\st310-03\\Source\\Repos\\karamov_mdk_01.04_pract9\\x64\\Debug\\CounterApp.exe ";
    wchar_t symHandle[20];

    DWORD idThread;

    HANDLE counter = CreateThread(NULL, 0, Counter, NULL, 0, &idThread);

    SetHandleInformation(
        counter,
        HANDLE_FLAG_INHERIT,
        HANDLE_FLAG_INHERIT
    );

    STARTUPINFO si;

    PROCESS_INFORMATION piCount;

    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);

    _itow_s((int)counter, symHandle, 10);

    wcscat_s(counterApp, symHandle);

    if (!CreateProcess(NULL, counterApp, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piCount))
    {
        std::cout << GetLastError();
    }

    int selection = 0;
    while ((countWORDS < 100 && countEXCELS < 100 && countNOTEPADS < 100 && countPAINTS < 100) && selection != 10)
    {
        system("cls");
        std::cout << "1 - word\n2 - excel\n3 - paint\n4 - notepad\n5 - close word \n6 - close excel\n7 - close paint\n8 - close notepad\n9 - close all\nselect: ";
        std::cin >> selection;
        switch (selection)
        {
            case 1:
            {
                PROCESS_INFORMATION piAppWord;
                if (CreateProcess(appNameWord, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piAppWord))
                {
                    words[countWORDS] = piAppWord;
                    countWORDS++;
                };
                break;
            }
            case 2:
            {
                PROCESS_INFORMATION piAppExcel;
                if (CreateProcess(appNameExcel, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piAppExcel))
                {
                    excels[countEXCELS] = piAppExcel;
                    countEXCELS++;
                }
                break;
            }
            case 3:
            {
                PROCESS_INFORMATION piAppPaint;
                if (CreateProcess(appNamePaint, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piAppPaint))
                {
                    paints[countPAINTS] = piAppPaint;
                    countPAINTS++;
                }
                break;
            }
            case 4:
            {
                PROCESS_INFORMATION piAppNotepad;
                if (CreateProcess(appNameNotepad, NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &piAppNotepad))
                {
                    notepads[countNOTEPADS] = piAppNotepad;
                    countNOTEPADS++;
                }
                break;
            }
            case 5:
            {
                TerminateProcess(words[countWORDS-1].hProcess, 0);
                CloseHandle(words[countWORDS -1].hThread);
                CloseHandle(words[countWORDS -1].hProcess);
                countWORDS--;
                break;
            }
            case 6:
            {
                TerminateProcess(excels[countEXCELS - 1].hProcess, 0);
                CloseHandle(excels[countEXCELS - 1].hThread);
                CloseHandle(excels[countEXCELS - 1].hProcess);
                countEXCELS--;
                break;
            }
            case 7:
            {
                TerminateProcess(paints[countPAINTS - 1].hProcess, 0);
                CloseHandle(paints[countPAINTS - 1].hThread);
                CloseHandle(paints[countPAINTS - 1].hProcess);
                countPAINTS--;
                break;
            }
            case 8:
            {
                TerminateProcess(notepads[countNOTEPADS - 1].hProcess, 0);
                CloseHandle(notepads[countNOTEPADS - 1].hThread);
                CloseHandle(notepads[countNOTEPADS - 1].hProcess);
                countNOTEPADS--;
                break;
            }
            case 9:
            {
                CloseAll();
                break;
            }
            case 10:
            {
                CloseAll();
                TerminateProcess(piCount.hProcess, 0);
                break;
            }
        }
    }
    CloseAll();
    CloseHandle(counter);
    CloseHandle(piCount.hThread);
    CloseHandle(piCount.hProcess);

    return 0;
}