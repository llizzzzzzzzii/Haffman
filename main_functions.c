#include "main_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CountLen(FILE* fr, int arr[])
{
    fseek(fr, 0L, SEEK_END);
    long len = ftell(fr);
    fseek(fr, 0L, SEEK_SET);
    for (int i = 0; i < len; ++i)
    {
        int symb = fgetc(fr);
        arr[(unsigned char)symb]++;
    }
}
int packing() {
    int arr[size] = { 0 };
    char InputFileName[50] = { 0 };
    scanf("%s", &InputFileName);
    int lenname = strlen(InputFileName);
    if (lenname < 4) {
        printf("The file is missing\n");
        return 0;
    }
    FILE* fr = fopen(InputFileName, "rb");
    char txt[5] = ".txt";
    InputFileName[lenname - 4] = 0;
    strncat(InputFileName, "_pack", 5);
    strncat(InputFileName, txt, 5);
    FILE* fw = fopen(InputFileName, "wb");
    if (!fr) {
        printf("The file is missing\n");
        return 0;
    }
    char* p = (char*)malloc(INCREASE_SIZE * sizeof(char));
    CountLen(fr, arr);
    Node* res = NULL;
    CreateList(arr, &res);
    PrintList(fw, res);
    printf("\n");
    res = MakeTreeFromList(res);
    PrintThreeOnSide(res, 0);
    printf("\n");
    char code[CODE_SIZE] = { '0', 0 };
    simmetric(res, code, 0);
    PrintTable(res, fw);
    ARR_STR str;
    long len = ftell(fr);
    int len_tail, len_buf = 0;
    char* buf[BIT8] = { 0 };
    fseek(fr, 0L, SEEK_SET);
    write(fw, "\n", 1);
    while (len > 0) {
        InitArrayStr(&str);
        int len_step = len > max_size ? max_size : len;
        MakeNewStr(res, &str, p, fr, len_step, len_buf, buf);
        len_tail = BIT8 - str.current_arr % BIT8;
        MadeTail(fw, &str, len_tail % BIT8, &len_buf, buf, len > max_size ? 1 : 0);
        //printf("%s %d\n", str.arr, str.current_arr);
        int lenght = str.current_arr / BIT8;
        //char* total = (char*)malloc((lenght) * sizeof(char));
        BIT2CHAR symb;
        MadeStr(fw, &symb, &str, lenght);
        //printf("%s", total);
        //write(fw, total, lenght);
        free(str.arr);
        // free(total);
        len -= max_size;
    }
    //char* len_tail_str = (char*)malloc((BIT8) * sizeof(char));
    //sprintf(len_tail_str, "%d", len_tail % BIT8);
    //write(fw, len_tail_str, strlen(len_tail_str));
    //free(len_tail_str);
    fputc(len_tail % BIT8, fw);
    fclose(fr);
    fclose(fw);
    return 1;
}
int unpack() {
    char OutFileName[50] = { 0 };
    scanf("%s", &OutFileName);
    int lenname = strlen(OutFileName);
    if (lenname < 4) {
        printf("The file is missing\n");
        return 0;
    }
    char ras[3] = { 0 };
    for (int i = 0; i < 3; ++i)
        ras[i] = OutFileName[lenname - 3 + i];
    OutFileName[lenname - 3] = 't';
    OutFileName[lenname - 2] = 'x';
    OutFileName[lenname - 1] = 't';
    FILE* fread = fopen(OutFileName, "rb");
    OutFileName[lenname - 4] = 0;
    strncat(OutFileName, "_unpack.", 8);
    strncat(OutFileName, ras, 3);
    FILE* fwrite = fopen(OutFileName, "wb");
    if (!fread) {
        printf("The file is missing\n");
        return 0;
    }
    link* code = (link*)calloc(1, sizeof(link));
    init_link(code);
    int end = 0;
    read_file(fread, code, &end);
    write_file(fwrite, fread, code, (BIT8 - end) % BIT8);
    fclose(fread);
    fclose(fwrite);
    return 1;
}

int COMPRESSION()
{
    printf("Enter the path to the file\n");
    if (!packing())
        return -1;
    return 1;
}
int UNPACKING()
{
    printf("Enter the path to save the unpacked file(the name with the extension)\n");
    if (!unpack())
        return -1;
    return 1;
}
int EXIT()
{
    printf("End of the program\n");
    return 0;
}
int NOTCOM()
{
    printf("Unknown command\n");
    return 0;
}

