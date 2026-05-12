#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t chopstick[5];
sem_t room;
void* philosopher(void* num) {
    int id = *(int*)num;

    sem_wait(&room);
    printf("Philosopher %d is hungry\n", id);

    sem_wait(&chopstick[id]);
    sem_wait(&chopstick[(id + 1) % 5]);

    printf("Philosopher %d is EATING\n", id);
    sleep(2);

    sem_post(&chopstick[(id + 1) % 5]);
    sem_post(&chopstick[id]);
    sem_post(&room);

    printf("Philosopher %d finished eating and is thinking\n", id);
}

int main() {
    pthread_t tid[5];
    int ids[5];
    sem_init(&room, 0, 4);
    for (int i = 0; i < 5; i++) sem_init(&chopstick[i], 0, 1);

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&tid[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < 5; i++) pthread_join(tid[i], NULL);

    return 0;
}
