//
// Created by liza on 13.04.2022.
//

#ifndef PROJECTHAFF_NODE_H
#define PROJECTHAFF_NODE_H

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define CODE_SIZE 300
typedef struct node {
    unsigned char symb;
    unsigned char isSymb;
    unsigned int freq;
    char code[CODE_SIZE];
    int level;
    struct node* left, * right, * next;
}Node;

void CreateList(int arr[], Node** res);

void Add2List(Node** pphead, Node** pnew);

Node** MakeNodeFromNode(Node* left, Node* right);

Node* MakeTreeFromList(Node* head);

void simmetric(Node* root, char code[], int level);

void PrintList(FILE*fw, Node* phead);

int write(FILE* fw, char message[], int n);

void PrintThreeOnSide(const Node* root, int level);

void PrintTable(Node* root, FILE* fw);
#endif //PROJECTHAFF_NODE_H
