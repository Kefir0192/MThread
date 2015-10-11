#include <portmacro.h>
#include <task.h>
#include <task_switch.h>

/// Указатель на переменную в которую нужно сохранить текущие положение стека
uint32_t **pPointer_Save_Context_Stask;
/// Указатель на переменную которая ссылается на указатель стека для загрузки
uint32_t **pPointer_Load_Context_Stask;

/// Массив структур для каждой задачи
struct Task_Element eTask_Element[VALUE_TASKS];
/// Статусная структура всех задач
struct Task_Status sTask_Status;

//------------------------------------------------------
// Создание новой задачи
// pTask_Element    Указатель на элемент задачи
// pTack            Указатель на функцию задачи type -> pFunction *
// pStack           Указатель на вершину стека  type -> uint32_t *
// Size_Stack       Размера стека в словах      type -> uint32_t
// pParameters      Аргумент потока             type -> void *
//------------------------------------------------------
void eTask_Create(struct Task_Element *pTask_Element, void (*pTack)(void *pVoid), uint32_t *pStack, uint32_t Size_Stack, void *pParameters, uint8_t priority)
{
    // Проверка указателей и минимального размера стека
    if(!pTask_Element && !pTack && !pStack && (Size_Stack >= MINIMUM_SIZE_STACK_WORD)) return;

    // Инициализация задачи
    pTask_Element->Size_Stack = Size_Stack;
    pTask_Element->pParameters = pParameters;
    pTask_Element->pTask_Descriptor = (descriptorTask)pTack;
    // Устанавливаем в начале приоритеты по дефолту
    pTask_Element->Setting_priority = priority;
    pTask_Element->Current_priority = pTask_Element->Setting_priority;

    // Текущий указатель на стек
    pTask_Element->pStack_pointer = port_Initialise_Stack(pTack, pStack, Size_Stack, pParameters);
}

//------------------------------------------------------
// Выбирает задачу, затем вызывает переключение контекста
//------------------------------------------------------
void sTask_Schedule(void)
{
    // Начало критической секции обеспечивающая атомарность
    port_Start_Critical_Section_Mutex();

    // Выбираем текущий поток
    sTask_Status.Task_Current = sTask_Status.Task_Next;
    // Выбираем задачу
    sTask_Status.Task_Next = sTask_Switch();

    // Указатель на переменную в которую нужно сохранить текущие положение стека
    pPointer_Save_Context_Stask = &eTask_Element[sTask_Status.Task_Current].pStack_pointer;
    // Указатель на стек откуда нужно начать восстановление контекста
    pPointer_Load_Context_Stask = &eTask_Element[sTask_Status.Task_Next].pStack_pointer;

    // Копируем дескриптор потока
    sTask_Status.pTask_Descriptor = eTask_Element[sTask_Status.Task_Next].pTask_Descriptor;

    // Конец критической секции обеспечивающая атомарность
    port_End_Critical_Section_Mutex();

    // Программное прерывание Schedule
    port_Inquiry_Interruption();
}

//------------------------------------------------------
// Запустить шедулер
//------------------------------------------------------
void eStart_Schedule(void)
{
    // Начальная инициализация
    sTask_Status.Task_Current = 0;
    sTask_Status.Task_Next = 0;

    // Выбирает задачу, затем вызывает переключение контекста
    sTask_Switch();
    // Текущая задача
    sTask_Status.Task_Current = sTask_Status.Task_Next;
    // Указатель на переменную в которую нужно сохранить текущие положение стека
    pPointer_Save_Context_Stask = &eTask_Element[sTask_Status.Task_Current].pStack_pointer;
    // Указатель на стек откуда нужно начать восстановление контекста
    pPointer_Load_Context_Stask = &eTask_Element[sTask_Status.Task_Next].pStack_pointer;
    // Копируем дескриптор потока
    sTask_Status.pTask_Descriptor = eTask_Element[sTask_Status.Task_Next].pTask_Descriptor;
    // Запустить шедулер
    port_Start_Schedule(eTask_Element[sTask_Status.Task_Current].pStack_pointer + 8);
}
