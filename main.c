#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

static int parse_count_arg(int argc, char* argv[]) {
    if (argc < 2) return -1;

    char* end = NULL;
    long val = strtol(argv[1], &end, 10);
    if (end == argv[1] || *end != '\0') return -1; // not a clean integer
    if (val < 0 || val > 1000000) return -1;       // basic sanity limit

    return (int)val;
}

int main(int argc, char* argv[]) {
    // Seed RNG for random users
    srand((unsigned int)time(NULL));

    int count = parse_count_arg(argc, argv);
    if (count < 0) {
        printf("Usage: %s <number_of_users>\n", argv[0]);
        printf("Example: %s 10\n", argv[0]);
        return 1;
    }

    Queue q;
    queue_init(&q);

    int rc = enqueue_random_users(&q, count);
    if (rc != 0) {
        printf("Error: failed to enqueue random users (code=%d)\n", rc);
        queue_free(&q);
        return 2;
    }

    printf("Dequeuing users...\n\n");

    User u;
    while (queue_dequeue(&q, &u)) {
        printf("Username: %-10s | Level: %2d | Faction: %s\n",
            u.username, u.level, faction_to_string(u.faction));
    }

    printf("\nDone. Queue is empty.\n");
    return 0;
}