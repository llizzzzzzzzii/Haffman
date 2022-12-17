#include "node.h"
#include "bit_string.h"
#include "main_functions.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int (*functions[])() = { COMPRESSION, UNPACKING, EXIT, NOTCOM };
char* f[] = { "COMPRESSION", "UNPACKING", "EXIT" };

int main() {
    setlocale(LC_ALL, "russian");
    char com[15] = { 0 };
    while (1) {
        printf("Enter the command:\nCOMPRESSION or UNPACKING\nEnter EXIT to exit the programm\n");
        scanf("%s", com);
        int flag = 0;
        for (int i = 0; i < 3; ++i) {
            if (!strcmp(com, f[i]))
            {
                int ret = functions[i](&com);
                if (ret == -1)
                    return -1;
                else if (!ret)
                    return 0;
                flag = 1;
                break;
            }
        }
        if (!flag) {
            functions[3](&com);
        }
        printf("\n");
    }
}

