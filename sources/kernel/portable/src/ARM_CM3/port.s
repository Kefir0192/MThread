@/*
@   Mark
@*/



@/*
@   Актуально для:
@   ARM_CM0
@   ARM_CM0_Plus
@   ARM_CM3
@   ARM_CM4
@*/



.align 2
.global PendSV_Handler
.code 16
.thumb_func
.type PendSV_Handler, %function
PendSV_Handler:
    # Адрес для сохранения контекста
    ldr r1, =pPointer_Save_Context_Stask
    ldr r0, [r1]
    # Сохраняем указатель стека psp в регистр r2
    mrs r1, psp
    # Вычисляем смещение для сохранения регистров
    sub r1, r1, #32
    # Сохраняем указатель стека в Pointer_Save_Context_Stask
    str r1, [r0]
    # Сохраняем low регистры
    stmia r1!, {r4-r7}
    # Сохраняем high регистры
    mov r4, r8
    mov r5, r9
    mov r6, r10
    mov r7, r11
    stmia r1!, {r4-r7}



    # Адрес для загрузки контекста
    ldr r0, =pPointer_Load_Context_Stask
    ldr r1, [r0]
    ldr r0, [r1]
    # Вычисляем смещение для загрузки регистров
    add r0, r0, #16
    # Сохраняем low регистры
    ldmia r0!, {r4-r7}
    # Сохраняем high регистры
    mov r8, r4
    mov r9, r5
    mov r10, r6
    mov r11, r7
    # Загружаем указатель стека в psp
    msr psp, r0
    # Вычисляем смещение для загрузки регистров
    sub r0, r0, #32
    ldmia r0!, {r4-r7}



    # Выходим с использованием в качестве основного указателя стека PSP
    ldr r0,=0xFFFFFFFD
    bx r0
.size PendSV_Handler, .-PendSV_Handler
