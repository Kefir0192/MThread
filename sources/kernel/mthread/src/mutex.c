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
        // Начало критической секции обеспечивающая атомарность
        port_Start_Critical_Section_Mutex();
        // Свободный ?
        if(pMmutex->lock == NULL) {
            // Проверка, кто-то ожидает мьютекс ?
            if(pMmutex->Inquiry == NULL) {
                // Блокируем мьютекс
                // Ресурс успешно занят
                PORT_ATOMIC_SAVE(pMmutex->lock, sTask_Status.pTask_Descriptor);
                goto exit_critical;
            }
            pMmutex->Inquiry = NULL;
            goto continue_critical;
        }

        // Занят нами ?
        if(pMmutex->lock == sTask_Status.pTask_Descriptor) {
            goto exit_critical;
        }

        pMmutex->Inquiry = 1;

        continue_critical:
        // Конец критической секции обеспечивающая атомарность
        port_End_Critical_Section_Mutex();
        // Блокируем поток до тех пор пока не захватим мьютекс
        sTask_Schedule();
    }
    exit_critical:
    // Конец критической секции обеспечивающая атомарность
    port_End_Critical_Section_Mutex();
}

//------------------------------------------------------
// Блокируем мьютекс
// В случаи если мьютекс занят не нами возвращает -1, если занят нами 0
// eTask_Schedule не вызывается
//------------------------------------------------------
uint8_t eMutex_try_lock(struct Mmutex *pMmutex)
{
    // Начало критической секции обеспечивающая атомарность
    port_Start_Critical_Section_Mutex();
    // Свободный ?
    if(pMmutex->lock == NULL) {
        // Проверка, кто-то ожидает мьютекс ?
        if(pMmutex->Inquiry == NULL) {
            // Блокируем мьютекс
            // Ресурс успешно занят
            PORT_ATOMIC_SAVE(pMmutex->lock, sTask_Status.pTask_Descriptor);
            goto exit_critical_true;
        }
        pMmutex->Inquiry = NULL;

        // Конец критической секции обеспечивающая атомарность
        port_End_Critical_Section_Mutex();
        sTask_Schedule();
        return -1;
    }

    // Занят нами ?
    if(pMmutex->lock == sTask_Status.pTask_Descriptor) {
        goto exit_critical_true;
    }

    // Конец критической секции обеспечивающая атомарность
    port_End_Critical_Section_Mutex();
    return -1;

    exit_critical_true:
    // Конец критической секции обеспечивающая атомарность
    port_End_Critical_Section_Mutex();
    return 0;
}

//------------------------------------------------------
// Разблокирует мьютекс
//------------------------------------------------------
void eMutex_unlock(struct Mmutex *pMmutex)
{
    // Можно разблокировать
    if(pMmutex->lock == sTask_Status.pTask_Descriptor) {
        pMmutex->lock = NULL;
        // Ресурс успешно разблокирован
    }
}
