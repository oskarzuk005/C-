#pragma once

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
inline int pobierzKlawisz()
{
    struct termios staryTerminal, nowyTerminal;
    int znak;
    tcgetattr(STDIN_FILENO, &staryTerminal);
    nowyTerminal = staryTerminal;
    nowyTerminal.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &nowyTerminal);
    znak = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &staryTerminal);
    return znak;
}
#endif