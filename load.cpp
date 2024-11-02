#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;
COORD getXY() 
{
    CONSOLE_SCREEN_BUFFER_INFO pBuffer;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &pBuffer);
    return COORD{pBuffer.dwCursorPosition.X, pBuffer.dwCursorPosition.Y};  
}
COORD getScrnInfo() 
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO scBufInf;           
    GetConsoleScreenBufferInfo(hStd, &scBufInf); 
    return scBufInf.dwSize; 
}
void moveXY(COORD pstn)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pstn);
}
void clearDisplay(COORD firstPst, COORD lastPst) 
{
    int yDValue(lastPst.Y - firstPst.Y); 

    COORD size(getScrnInfo()); 
    moveXY(firstPst);                 
    for (int y(0); y <= yDValue; y++) 
    {
        for (int x(firstPst.X); x <= size.X; x++) 
        {
            std::cout << ' '; 
            int px;           
            if (x != size.X)
                px = x + 1;
            else
                px = 0;
            if (y == yDValue && px == lastPst.X) 
                break;
        }
    }
    moveXY(firstPst);
}
void loadingMode(int mode = 0)
{
    if (mode == 1)
    {
        cout << "Loading...\n[";
        for (int i = 0; i < 25; i++)
        {
            cout << "=";
            Sleep(50);
        }
        cout << ">] 100%" << endl;
        return;
    }
    COORD headPst(getXY()); 
    HANDLE hStd(GetStdHandle(STD_OUTPUT_HANDLE));
    CONSOLE_CURSOR_INFO cInfo;
    GetConsoleCursorInfo(hStd, &cInfo); 
    cInfo.bVisible = false;             
    SetConsoleCursorInfo(hStd, &cInfo); 

    std::cout << "Loading...";
    COORD firstPst; 
    COORD lastPst;

    int n(0);                    
    int m(0);                    
    srand((unsigned)time(NULL)); 
    while (n < 100)              
    {
        m = n / 5;
        n += rand() % 14 + 1;
        if (n < 100)
        {
            for (int i(n / 5 - m); i > 0; i--)
                std::cout << "¨€";
            firstPst = getXY();    
            std::cout << n << "%"; 
            lastPst = getXY();    
        }
        else
        {
            n = 100; 
            std::cout << "¨€";
            std::cout << n << "%";
            lastPst = getXY();
            break;
        }

        Sleep(80);
        clearDisplay(firstPst, lastPst); 
    }

    clearDisplay(headPst, lastPst); 
    cInfo.bVisible = true;          
    SetConsoleCursorInfo(hStd, &cInfo);
}