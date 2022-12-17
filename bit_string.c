#include "bit_string.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ReallocArray(ARR_STR* str) {
    char* aa = (char*)calloc(str->maxcount_arr * 2 + 1, sizeof(char));
    for (int i = 0; i < str->current_arr; ++i)
        aa[i] = str->arr[i];
    str->arr = NULL;
    free(str->arr);
    str->arr = aa;
    str->maxcount_arr = str->maxcount_arr * 2 + 1;
}
void InitArrayStr(ARR_STR* str) {
    str->maxcount_arr = 10;
    str->arr = (char*)calloc(str->maxcount_arr, sizeof(char));
    str->current_arr = 0;
}
int Find(Node* root, unsigned char symbol, char* p)
{
    if (root->isSymb != 0)
    {
        if (root->symb == symbol) {
            strcpy(p, root->code);
            return 1;
        }
    }
    else
    {
        if (Find(root->left, symbol, p)) return 1;
        if (Find(root->right, symbol, p)) return 1;
    }
    return 0;
}

void MakeNewStr(Node* phead, ARR_STR* rez, char* p, FILE* fr, int len, int len_buf, char* buf) {
    for (int i = 0; i < len_buf; ++i) {
        rez->arr[rez->current_arr] = buf[i];
        rez->current_arr++;
    }
    for (int i = 0; i < len; i++) {
        int symb = fgetc(fr);
        p = (char*)malloc(INCREASE_SIZE * sizeof(char));
        Find(phead, (unsigned char)symb, p);
        for (int j = 0; j < strlen(p); j++) {
            if (rez->maxcount_arr <= rez->current_arr) {
                ReallocArray(rez);
            }
            rez->arr[rez->current_arr] = p[j];
            rez->current_arr++;
        }
        p = NULL;
        free(p);
    }
    free(p);
}
void MadeTail(FILE* fw, ARR_STR* str, int len_tail, int* len_buf, char* buf, int temp) {
    if (!temp) {
        for (int i = 0; i < len_tail; ++i) {
            if (str->maxcount_arr < str->current_arr) {
                ReallocArray(str);
            }
            str->arr[str->current_arr] = '0';
            str->current_arr++;
        }
    }
    else {
        *len_buf = (BIT8 - len_tail) % BIT8;
        str->current_arr = str->current_arr - *len_buf;
        for (int i = 0; i < *len_buf; ++i)
            buf[i] = str->arr[str->current_arr + i];
    }
}
void MadeStr(FILE* fw, BIT2CHAR* symb, ARR_STR* str, int len) {
    for (int i = 0; i < len; ++i)
    {
        symb->mbit.b1 = (unsigned int)str->arr[i * BIT8 + 0];
        symb->mbit.b2 = (unsigned int)str->arr[i * BIT8 + 1];
        symb->mbit.b3 = (unsigned int)str->arr[i * BIT8 + 2];
        symb->mbit.b4 = (unsigned int)str->arr[i * BIT8 + 3];
        symb->mbit.b5 = (unsigned int)str->arr[i * BIT8 + 4];
        symb->mbit.b6 = (unsigned int)str->arr[i * BIT8 + 5];
        symb->mbit.b7 = (unsigned int)str->arr[i * BIT8 + 6];
        symb->mbit.b8 = (unsigned int)str->arr[i * BIT8 + 7];
        //total[i] = symb->symb;
        fputc(symb->symb, fw);
    }
}



void init_link(link* ok) {
    ok->symb = -1;
    ok->side[0] = NULL;
    ok->side[1] = NULL;
}
void read_file(FILE* fr, link* p, int* end) {
    fseek(fr, -1L, SEEK_END);
    *end = fgetc(fr);
    fseek(fr, 0L, SEEK_SET);
    int count, key, key1, irr;
    fscanf(fr, "%d", &count);
    fgetc(fr);
    link* step = (link*)calloc(1, sizeof(link));
    for (int i = 0; i < count; ++i) {
        step = p;
        link* pnew = (link*)calloc(1, sizeof(link));
        init_link(pnew);
        key = fgetc(fr);
        pnew->symb = key;
        fgetc(fr);
        key = fgetc(fr);
        while ((key1 = fgetc(fr)) != '\n') {
            irr = atoi((char*)&key);
            if (!step->side[irr]) {
                link* path = (link*)calloc(1, sizeof(link));
                init_link(path);
                step->side[irr] = path;
            }
            step = step->side[irr];
            key = key1;
        }
        irr = atoi((char*)&key);
        step->side[irr] = pnew;
    }
}
void write_file(FILE* fw, FILE* fr, link* p, int end) {
    int symb, symb1, symb2;
    unsigned char bit = 0;
    fgetc(fr);
    symb = fgetc(fr);
    symb1 = fgetc(fr);
    char ok;
    link* step = p;
    while ((symb2 = fgetc(fr)) != EOF) {
        for (int i = 0; i < BIT8; ++i) {
            bit = symb;
            bit = bit << i;
            bit = bit >> 7;
            step = step->side[bit];
            if (step->symb >= 0) {
                fprintf(fw, "%c", step->symb);
                step = p;
            }
        }
        symb = symb1;
        symb1 = symb2;
    }
    for (int i = 0; i < end; ++i) {
        bit = symb;
        bit = bit << i;
        bit = bit >> 7;
        step = step->side[bit];
        if (step->symb >= 0) {
            fprintf(fw, "%c", step->symb);
            step = p;
        }
    }
}
