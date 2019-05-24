#include "Schedule.h"

TCB* list = NULL;

void schedule(TCB *taskLinkedList) {

}

void insert(TCB *node) {
    // If the head pointer is pointing to nothing
    if (list == NULL) {
        printf("%d\n",5);
        // set the head and tail pointers to point to this node
        node->prev = NULL;
        node->next = NULL;
        list = node;
        std::cout << list->id << "\n";
    } else { // otherwise, head is not NULL, add the node to the end of the list
        TCB *cur = list;
        printf("%d\n",15);
        while (cur != NULL && cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = node;
        node->prev = cur;
        node->next = NULL;     
    }
}

void deleteTask(TCB *node) {
    if (list != NULL) {
        if (list->prev == NULL && list->next == NULL && list == node) { // only 1 element in the list
            list = NULL;
        } else if (list == node) { // if the head pointer is equal to the node we want to delete
            list = list->next;
            list->prev = NULL;
        } else { // if the node we want to delete is in the middle or end
            TCB *cur = list;
            while (cur != NULL && cur->next != NULL && cur->next != node) {
                cur = cur->next;
            }
            
            if (cur!= NULL && cur->next != NULL && cur->next->next != NULL) { // middle case
                cur->next = cur->next->next;
                cur->next->prev = cur;
                node->prev = NULL;
                node->next = NULL;
            } else if (cur != NULL && cur->next != NULL && cur->next->next == NULL) { // end case
                cur->next = cur->next->next;
                node->prev = NULL;
            }
        }
    }
}

void initSchedule(TCB* node) {
   
}