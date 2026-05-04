/** EL2008 Praktikum Pemecahan Masalah dengan Pemrograman 2025/2026
 *   Modul               : 04 – Dynamic Structures
 *   Hari dan Tanggal    : Senin, 04 Mei 2025
 *   Nama (NIM)          : Muhammad Zaki Azzamy Syauqi (13224045)
 *   Nama File           : soal1.c
 *   Deskripsi           : Diberi input:
 *                           Q op1 x1 op2 x2 ... opQ xQ
 *                         Dimana Q adalah jumlah operasi, opQ adalah operasi yang ingin dilakukan pada tahap Q, xQ adalah data yang digunakan untuk operasi tahap Q
 *                         Operasi:
 *                          1. 1 x = PUSH_FRONT x
 *                          2. 2 x = PUSH_BACK x
 *                          3. 3 x = DELETE x pertama yang ada
 *                          4. 4 x = FIND x, 0 based position
 *                         Format output:
 *                           for each found: FOUND position / NOT FOUND
 *                           LIST ... / LIST EMPTY
 * 
 *                         Contoh:
 *                         Input: 6 2 10 2 20 1 5 4 20 3 10 4 10
 *                         
 *                         Output: 
 *                         FOUND 2
 *                         NOT FOUND
 *                         LIST 5 20
 * 
 *                         5 10 20, find 20 --> 2, delete 10, list 5 20
 *                         Referensi:
 *                          1. Jawaban soal TP saya
 *                          2. Jawaban untuk soal di kelas saya
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNodeWithData(int data) {
    Node* node;
    node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        printf("Memori tidak cukup.\n");
        return NULL;
    }

    node->data = data;
    node->next = NULL;

    return node;
}

void pushFront(Node** head_list, int data) {
    Node* new_node = createNodeWithData(data);
    new_node->next = *head_list;
    *head_list = new_node;
    return;
}

void pushBack(Node** head_list, int data) {
    Node* new_node = createNodeWithData(data);
    if (*head_list == NULL) {
        *head_list = new_node;
        return;
    }
    
    Node* temp = *head_list;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
    return;
}

int findNode(Node* head_list, int data) {
    Node* temp = head_list;
    int count = 0;
    while (temp != NULL) {
        if (temp->data == data) {
            return count;
        }
        count += 1;
        temp = temp->next;
    }
    return -1;
}

void deleteNode(Node** head_list, int data) {
    Node* temp = *head_list;
    int found = findNode(*head_list, data);
    if (found == 0) {
        Node* temp = *head_list;
        *head_list = (*head_list)->next;
        free(temp);
        return;
    }
    
    if (found > 0) {
        for (int i = 0; i < found - 1; i += 1) {
            temp = temp->next;
        }
        Node* jump = temp->next->next;
        free(temp->next);
        temp->next = jump;
        return;
    }
    return;
    // if ((*head_list)->data == data) {
    //     Node* temp = *head_list;
    //     *head_list = (*head_list)->next;
    //     free(temp);
    //     return;
    // }

    // while (temp != NULL) {
    //     if (temp->next->data != data) {
    //         temp = temp->next;
    //     } else {
    //         found = 1;
    //         break;
    //     }
    // }

    // if (temp->next == NULL) {
    //     printf("DNE.\n");
    //     return;
    // }

    // if (found) {
        // Node* jump = temp->next->next;
        // free(temp->next);
        // temp->next = jump;
        // return;
    // }
    
    // printf("NOT EXIST");
    // return;
}

void printList(Node* head_list) {
    printf("LIST");
    Node* temp = head_list;
    
    if (temp == NULL) {
        printf(" EMPTY\n");
        return;
    }

    while (temp != NULL) {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    printf("\n");
    return;
}

int main(void) {
    Node* head_list = NULL;
    int Q, action, data;

    scanf("%d", &Q);
    for (int i = 0; i < Q; i += 1) {
        scanf("%d %d", &action, &data);
        if (action == 1) {
            pushFront(&head_list, data);
        }

        else if (action == 2) {
            pushBack(&head_list, data);
        }

        else if (action == 3) {
            deleteNode(&head_list, data);
        }

        else if (action == 4) {
            int count = findNode(head_list, data);
            if (count == -1) printf("NOT FOUND\n");
            else if (count >= 0) printf("FOUND %d\n", count);
        }
    }
    printList(head_list);
    return 0;
}
