#include <portmacro.h>
#include <task.h>
#include <mutex.h>



//------------------------------------------------------
// Создать Mutex
//------------------------------------------------------
void eMutex_Create(struct Mmutex *pMmutex)
{
    pMmutex->Inquiry = NULL;
    pMmutex->lock = NULL;
}

//------------------------------------------------------
// Блокируем мьютекс
// В случаи если мьютекс занят вызывается eTask_Schedule,
// дальнейшие выполнение программы блокируется
//------------------------------------------------------
void eMutex_lock(struct Mmutex *pMmutex)
{
    while(1) {
        if(port_atomic_exchange(&pMmutex->lock, 1) == 0) {
            // Проверка, кто-то ожидает мьютекс ?
            if(pMmutex->Inquiry == NULL) {
                // Блокируем мьютекс
                // Ресурс успешно занят
                pMmutex->pTask_Descriptor = sTask_Status.pTask_Descriptor;
                return; // Ресурс успешно занят
            }
            pMmutex->Inquiry = NULL;
            port_atomic_exchange(&pMmutex->lock, 0);
            // Блокируем поток до тех пор пока не захватим мьютекс
            sTask_Schedule();
            continue;
        }

        if(pMmutex->pTask_Descriptor == sTask_Status.pTask_Descriptor)
            return; //рекурсивный захват


        pMmutex->Inquiry = 1;
        // Блокируем поток до тех пор пока не захватим мьютекс
        sTask_Schedule();
    }
}

//------------------------------------------------------
// Блокируем мьютекс
// В случаи если мьютекс занят не нами возвращает -1, если занят нами 0
// eTask_Schedule не вызывается
//------------------------------------------------------
uint8_t eMutex_try_lock(struct Mmutex *pMmutex)
{
    if(port_atomic_exchange(&pMmutex->lock, 1) == 0) {
        // Проверка, кто-то ожидает мьютекс ?
        if(pMmutex->Inquiry == NULL) {
            // Блокируем мьютекс
            // Ресурс успешно занят
            pMmutex->pTask_Descriptor = sTask_Status.pTask_Descriptor;
            return 0; // Ресурс успешно занят
        }
        pMmutex->Inquiry = NULL;
        port_atomic_exchange(&pMmutex->lock, 0);
        sTask_Schedule();
        return -1;
    }

    if(pMmutex->pTask_Descriptor == sTask_Status.pTask_Descriptor)
        return 0; //рекурсивный захват

    pMmutex->Inquiry = 1;
    return -1;
}

//------------------------------------------------------
// Разблокирует мьютекс
//------------------------------------------------------
void eMutex_unlock(struct Mmutex *pMmutex)
{
    // Можно разблокировать
    if(pMmutex->pTask_Descriptor == sTask_Status.pTask_Descriptor) {
        pMmutex->lock = NULL;
        port_atomic_exchange(&pMmutex->lock, 0);
        // Ресурс успешно разблокирован
    }
}
