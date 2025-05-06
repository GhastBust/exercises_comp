#include "vel-ver.h"

#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#include "../diag/diag.h"

#define Flag    bool
#define Mutex   pthread_mutex_t
#define Cond    pthread_cond_t
#define lock    pthread_mutex_lock
#define unlock  pthread_mutex_unlock
#define THREADS 8

typedef struct Signal {
    Mutex* mutex;
    Cond*  cond;
    Flag*  is_ready;
} Signal;

typedef struct ThreadArgs {
    VernelSimulation* sym;
    Signal* signal;
    Mutex*  mutex;
    double  dt;
    bool*   can_exe;
    bool*   stop;
    size_t  start;
    size_t  len;
} ThreadArgs;


void 

void wait_ready(Signal* signal) {
    pthread_mutex_lock(signal->mutex);
    while(!*signal->flag) { pthread_cond_wait(signal->cond, signal->mutex); }
    pthread_mutex_unlock(signal->mutex);
}

void set_all_ready(Signal* signal) {
    pthread_mutex_lock(signal->mutex);
    *signal->flag = true;
    pthread_cond_broadcast(signal->cond);
    pthread_mutex_unlock(signal->mutex);
}

void init_all( Mutex* mutexs ) {
    for (int i = 0; i < THREADS; i++ ) { pthread_mutex_init(mutexs+i, NULL); }
}

void lock_all( Mutex* mutexs ) {
    printf("main: try locking all\n");
    for (int i = 0; i < THREADS; i++ ) { lock(mutexs+i); }
    printf("main: done locking\n");
}

void unlock_all( Mutex* mutexs ) {
    printf("main: try unlocking all\n");
    for (int i = 0; i < THREADS; i++ ) { unlock(mutexs+i); }
    printf("main: done unlocking\n");
}



void* __step_some_vernel( void* v_arg ) {

    ThreadArgs* arg = (ThreadArgs*) v_arg; 

    printf("thread n: %ld, try first lock\n", arg->start / arg->len );
    lock(arg->mutex);
    printf("thread n: %ld, first lock done\n", arg->start / arg->len );
    while (!*arg->stop) {


        for ( size_t i = arg->start; i < arg->start + arg->len; i++ ) {
            Particle new_p = step_vernel_vec3(arg->sym->particles + i, arg->sym, arg->dt);
            arg->sym->cache[i] = new_p;
        }
        
        printf("thread n: %ld, try unlock\n", arg->start / arg->len );
        unlock(arg->mutex);
        printf("thread n: %ld, unlock done\n", arg->start / arg->len );

        // sleep(1);

        printf("thread n: %ld, try lock\n", arg->start / arg->len );
        lock(arg->mutex);
        printf("thread n: %ld, lock done\n", arg->start / arg->len );
    }

    printf("returning thread n: %ld\n", arg->start / arg->len);

    return NULL;
}


void step_all_vernel_threads(VernelSimulation *sym, void (*init_task)(VernelSimulation*), double T, double dt) {

    pthread_t   threads[THREADS];
    ThreadArgs  args   [THREADS];
    Mutex       mutexs [THREADS];
    bool        can_exe[THREADS];
    bool        stop   = false;
    
    int len = sym->n_particles / THREADS;
    
    if (len * THREADS != sym->n_particles) {critical("Number of threads does not divide evenly the particles");}

    init_all(mutexs);
    lock_all(mutexs);
    
    for ( int i = 0; i < THREADS; i++ ) {

        args[i] = (ThreadArgs){
            .sym = sym, .dt = dt, 
            .len = len, .start = i*len, 
            .mutex = mutexs+i,
            .stop = &stop,
            .can_exe = &can_exe[i]
        };

        pthread_create(threads+i, NULL, __step_some_vernel, args+i);
    }

    sleep(1);

    unlock_all(mutexs);

    for ( double t = dt; t < T; t += dt ) {

        // (*init_task)(sym);
        // sleep(1);
        printf("Print sys\n");

        lock_all(mutexs);

        // sleep(1);
        __swap_old_new(sym);
        __mirror_particles(sym);

        unlock_all(mutexs);

        if ( t > 1*dt ) {break;}
    }

    lock_all(mutexs);
    stop = true;

    for ( int i = 0; i < THREADS; i++ ) {
        unlock(mutexs+i);
        pthread_join(threads[i], NULL);
    }
}