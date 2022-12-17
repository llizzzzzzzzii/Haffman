#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void CreateList(int arr[], Node** res)
{
    for (int i = 0; i < 256; ++i) {
        if (arr[i] != 0)
        {
            Node* pnew = (Node*)calloc(1, sizeof(Node));
            pnew->freq = arr[i];
            pnew->symb = i;
            pnew->isSymb = 1;
            Add2List(res, &pnew);
        }
    }
}
void Add2List(Node** pphead, Node** pnew)
{
    while (*pphead)
    {
        if ((*pnew)->freq < (*pphead)->freq)
            break;
        pphead = &((*pphead)->next);
    }
    (*pnew)->next = *pphead;
    *pphead = *pnew;
}
Node** MakeNodeFromNode(Node* left, Node* right)
{
    Node* res = (Node*)malloc(sizeof(Node));
    res->freq = left->freq + right->freq;
    res->isSymb = 0;
    res->symb = 0;
    res->left = left;
    res->right = right;
    res->next = 0;
    Node** pp = &res;
    return pp;
}
Node* MakeTreeFromList(Node* head)
{
    while (head && head->next)
    {
        Node* left = head;
        Node* right = head->next;
        Add2List(&(head), MakeNodeFromNode(left, right));
        head = head->next->next;
    }
    return head;
}
void simmetric(Node* root, char* code, int level)
{
    if (root)
    {
        if (!root->isSymb)
        {
            code[level] = '0';
            simmetric(root->left, code, level + 1);
            code[level] = '1';
            simmetric(root->right, code, level + 1);
            code[level] = 0;
        }
        else
            strcpy(root->code, code);
    }
}
void PrintThreeOnSide(const Node* root, int level)
{
    if (root)
    {
        PrintThreeOnSide(root->right, level + 1);
        for (int i = 0; i < level; ++i)
            printf("\t");
        printf("%3d\n", root->freq);
        PrintThreeOnSide(root->left, level + 1);
    }
}

void PrintList(FILE* const fw, Node* phead)
{
    Node* p = phead;
    int count = 0;
    while (p)
    {
        printf("%d", p->freq);
        p = p->next;
        count++;
    }
    printf("\n");
    fprintf(fw, "%d\n", count);
}
int write(FILE* fw, char message[], int n)
{
    for (int i = 0; i < n; i++)
    {
        putc(message[i], fw);
    }
    return 0;
}
void PrintTable(Node* root, FILE* fw)
{
    if (root->isSymb != 0)
    {
        printf("%c ", root->symb);
        unsigned char temp[2] = { 0 };
        temp[0] = root->symb;
        write(fw, temp, 1);
        write(fw, " ", 1);
        for (int i = 0; i < strlen(root->code); ++i)
            printf("%c", root->code[i]);
        write(fw, root->code, strlen(root->code));
        write(fw, "\n", 1);
        printf("\n");
    }
    else
    {
        PrintTable(root->left, fw);
        PrintTable(root->right, fw);
    }
}
