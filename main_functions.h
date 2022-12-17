

#ifndef PROJECTHAFF_MAIN_FUNCTIONS_H
#define PROJECTHAFF_MAIN_FUNCTIONS_H
#pragma once
#include "bit_string.h"
#include "node.h"
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define size 256
#define INCREASE_SIZE 20
#define CODE_SIZE 300
#define BIT8 8
#define max_size 1000000


void CountLen(FILE* fr, int arr[]);

int packing();

int unpack();

int COMPRESSION();

int UNPACKING();

int EXIT();

int NOTCOM();
#endif //PROJECTHAFF_MAIN_FUNCTIONS_H
