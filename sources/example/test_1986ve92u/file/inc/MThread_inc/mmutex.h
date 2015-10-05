#ifndef MMUTEX
#define MMUTEX

// Mutex
typedef void mmutex;

struct Mmutex {
    /// Блокировка мьютекса
    mmutex *lock;
    /// Запрос на блокировку мьютекса
    uint8_t Inquiry;
};

// Блокируем мьютекс
// В случаи если мьютекс занят вызывается eTask_Schedule,
// дальнейшие выполнение программы блокируется
//------------------------------------------------------
void eMutex_lock(struct Mmutex *pMmutex);

// Блокируем мьютекс
// В случаи если мьютекс занят не нами возвращает -1, если занят нами 0
// eTask_Schedule не вызывается
//------------------------------------------------------
uint8_t eMutex_try_lock(struct Mmutex *pMmutex);

// Разблокирует мьютекс
//------------------------------------------------------
void eMutex_unlock(struct Mmutex *pMmutex);

#endif // MMUTEX

