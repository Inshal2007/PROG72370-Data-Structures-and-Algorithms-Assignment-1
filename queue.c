#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

static char random_char_from_set(const char* set) {
    int len = 0;
    while (set[len] != '\0') len++;
    return set[rand() % len];
}

static void generate_random_username(char out[USERNAME_LEN + 1]) {
    const char* letters = "abcdefghijklmnopqrstuvwxyz";
    const char* digits = "0123456789";

    for (int i = 0; i < USERNAME_LEN; i++) {
        // ~70% letters, ~30% digits (any ratio is fine)
        if ((rand() % 10) < 7) out[i] = random_char_from_set(letters);
        else out[i] = random_char_from_set(digits);
    }
    out[USERNAME_LEN] = '\0';
}

static User generate_random_user(void) {
    User u;
    generate_random_username(u.username);
    u.level = (rand() % 60) + 1;              // 1..60
    u.faction = (Faction)(rand() % 3);        // 0..2
    return u;
}

void queue_init(Queue* q) {
    if (!q) return;
    q->head = NULL;
    q->tail = NULL;
}

bool queue_is_empty(const Queue* q) {
    return (!q || q->head == NULL);
}

bool queue_enqueue(Queue* q, User user) {
    if (!q) return false;

    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (!node) return false;

    node->data = user;
    node->next = NULL;

    if (q->tail == NULL) {
        // empty queue
        q->head = node;
        q->tail = node;
    }
    else {
        q->tail->next = node;
        q->tail = node;
    }
    return true;
}

bool queue_dequeue(Queue* q, User* out_user) {
    if (!q || !q->head) return false;

    QueueNode* old_head = q->head;

    if (out_user) {
        *out_user = old_head->data;
    }

    q->head = old_head->next;
    if (q->head == NULL) {
        // queue became empty, so tail must also become NULL
        q->tail = NULL;
    }

    free(old_head);
    return true;
}

void queue_free(Queue* q) {
    if (!q) return;
    User tmp;
    while (queue_dequeue(q, &tmp)) {
        // keep dequeuing until empty
    }
}

int enqueue_random_users(Queue* q, int count) {
    if (!q) return 1;
    if (count < 0) return 2;

    for (int i = 0; i < count; i++) {
        User u = generate_random_user();
        if (!queue_enqueue(q, u)) {
            return 3; // allocation failure
        }
    }
    return 0;
}

const char* faction_to_string(Faction f) {
    switch (f) {
    case FACTION_RED: return "red";
    case FACTION_BLUE: return "blue";
    case FACTION_GREEN: return "green";
    default: return "unknown";
    }
}