#ifndef TEST_THREAD
#define TEST_THREAD

extern struct Mmutex MutexA;

extern uint32_t stack_a[128];
extern uint32_t stack_b[128];

extern uint32_t vA, vB;


void Thread_A(void *pVoid);

void Thread_B(void *pVoid);

#endif // TEST_THREAD

