//
// Created by liza on 13.04.2022.
//

#ifndef PROJECTHAFF_BIT_STRING_H
#define PROJECTHAFF_BIT_STRING_H

#pragma once
#include "node.h"

#define INCREASE_SIZE 20
#define BIT8 8
typedef struct ArrStr {
    char* arr;
    int current_arr;
    int maxcount_arr;
}ARR_STR;
typedef union bit2char {
    unsigned char symb;
    struct bit {
        unsigned b8 : 1;
        unsigned b7 : 1;
        unsigned b6 : 1;
        unsigned b5 : 1;
        unsigned b4 : 1;
        unsigned b3 : 1;
        unsigned b2 : 1;
        unsigned b1 : 1;
    }mbit;
}BIT2CHAR;

typedef struct links {
    int symb;
    struct link* side[2];
}link;

void ReallocArray(ARR_STR* str);

void InitArrayStr(ARR_STR* str);

int Find(Node* root, unsigned char symbol, char* p);

void MakeNewStr(Node* phead, ARR_STR* rez, char* p, FILE* fr, int len, int len_buf, char* buf);

void MadeTail(FILE* fw, ARR_STR* str, int len_tail, int* len_buf, char* buf, int temp);

void MadeStr(FILE* fw, BIT2CHAR* symb, ARR_STR* str, int len);

void init_link(link* ok);

void read_file(FILE* fr, link* p, int* end);

void write_file(FILE* fw, FILE* fr, link* p, int end);
#endif //PROJECTHAFF_BIT_STRING_H
