#ifndef MTHREAD_CONFIG
#define MTHREAD_CONFIG
#include "inc/GlobalIncludeFile.h"

/// Значение всех задач
#define VALUE_TASKS             2
/// Минимальный размер стека в словах (слово - 4 байта)
#define MINIMUM_SIZE_STACK_WORD 16
/// Максимальное число приоритетов потоков
#define MIN_PRIORITY 2

/// Указатель на переменную в которую нужно сохранить текущие положение стека
extern uint32_t **pPointer_Save_Context_Stask;
/// Указатель на переменную которая ссылается на указатель стека для загрузки
extern uint32_t **pPointer_Load_Context_Stask;

/// Минимальный и текущий приоритеты
/// Приоритет меняется от максимально большого (0) до максимально малого (в сторону увеличения)
uint8_t current_min_priority;
uint8_t current_priority;

/// Descriptor Task
typedef void *descriptorTask;

struct Task_Element {
    /// Размера стека в словах
    uint32_t    Size_Stack,
    /// Текущий указатель стека
                *pStack_pointer;
    /// Установленный приоритет
    uint8_t     Setting_priority,
    /// Текущий приоритет
                Current_priority;
    /// Дескриптор задачи
    descriptorTask pTask_Descriptor;

    /// Аргумент потока
    void *pParameters;
};

struct Task_Status {
    /// Индекс элемента массива структур текущей задачи
    uint32_t    Task_Current,
    /// Индекс элемента массива структур следующий задачи
                Task_Next;
    /// Дескриптор текущей задачи
    descriptorTask pTask_Descriptor;
};

/// Массив структур для каждой задачи
extern struct Task_Element eTask_Element[VALUE_TASKS];
/// Статусная структура всех задач
extern struct Task_Status sTask_Status;

//------------------------------------------------------
// Создание новой задачи
// pTask_Element    Указатель на элемент задачи
// pTack            Указатель на функцию задачи type -> pFunction *
// pStack           Указатель на вершину стека  type -> uint32_t *
// Size_Stack       Размера стека в словах      type -> uint32_t
// pParameters      Аргумент потока             type -> void *
//------------------------------------------------------
void eTask_Create(struct Task_Element *pTask_Element, void (*pTack)(void *pVoid), uint32_t *pStack, uint32_t Size_Stack, void *pParameters);
// Возвращает следующую задачу
//------------------------------------------------------
uint8_t sTask_Switch(void);
// Выбирает задачу, затем вызывает переключение контекста
//------------------------------------------------------
void sTask_Schedule(void);
// Запустить шедулер
//------------------------------------------------------
void eStart_Schedule(void);
// Delay
//------------------------------------------------------
void Delay(uint32_t value);

#endif // MTHREAD_CONFIG

