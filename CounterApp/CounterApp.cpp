#include <iostream>
#include <Windows.h>

int main(int argc, char* argv[])
{
    HANDLE hThread;
    hThread = (HANDLE)atoi(argv[1]);
    int selection = 0;
    do
    {
        std::cout << "1 - suspend thread\n2 - resume thread\n3 - exit\nselect: ";
        std::cin >> selection;
        switch (selection)
        {
            case 1:
            {
                SuspendThread(hThread);
                break;
            }
            case 2:
            {
                ResumeThread(hThread);
                break;
            }
        }
    } while (selection != 3);

    CloseHandle(hThread);
}
