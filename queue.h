#pragma once

#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

#define USERNAME_LEN 10  // fixed length usernames (not counting '\0')

typedef enum Faction {
    FACTION_RED = 0,
    FACTION_BLUE = 1,
    FACTION_GREEN = 2
} Faction;

typedef struct User {
    char username[USERNAME_LEN + 1]; // +1 for null terminator
    int level;                       // 1..60
    Faction faction;                 // red/blue/green
} User;

typedef struct QueueNode {
    User data;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;

/* Queue ADT operations */
void queue_init(Queue* q);
bool queue_is_empty(const Queue* q);
bool queue_enqueue(Queue* q, User user);
bool queue_dequeue(Queue* q, User* out_user);
void queue_free(Queue* q);

/* Assignment helper: enqueue random users */
int enqueue_random_users(Queue* q, int count);

/* Utility for printing faction */
const char* faction_to_string(Faction f);

#endif