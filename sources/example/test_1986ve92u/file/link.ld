/*
    Mark
*/

MEMORY
{
   FLASH(RX)    : ORIGIN = 0x08000000, LENGTH = 128K
   RAM(rwx)     : ORIGIN = 0x20000000, LENGTH = 32K
}

/*
.text — скомпилированный машинный код;
.data — глобальные и статические переменные;
.rodata — аналог .data для неизменяемых данных;
.bss — глобальные и статические переменные, которые при старте содержат нулевое значение.

.comment — информация о версии компилятора;
.ARM.attributes — ARM-специфичные атрибуты файла.
*/

SECTIONS
{
    .isr_vector : ALIGN(4)
    {
        _start_isr_vector = .;
        KEEP(*(.isr_vector))
        _end_isr_vector = .;
        . = 0xc8 - _end_isr_vector + ALIGN(4);
        KEEP(*(.loop))
    } > FLASH = 0xff

    .text : ALIGN(4)
    {
        _start_text = .;
        *(.text)
        *(.text*)
        KEEP(*(.data_flash))
        _end_text = .;
    } > FLASH

    .rodata : ALIGN(4)
    {
        _start_rodata = .;
        *(.rodata)
        *(.rodata*)
        _end_rodata = .;
    } > RAM AT > FLASH

    .data : ALIGN(4)
    {
        _start_data = .;
        *(.data)
        *(.data*)
        _end_data = .;
    } >  RAM AT > FLASH

    .bss :
    {
        _start_bss = .;
        *(.bss)
        *(.bss*)
        _end_bss = .;
    } > RAM
}
_size_rodata = SIZEOF(.rodata);
_size_data = SIZEOF(.data);
_size_bss = SIZEOF(.bss);

_start_rodata_copi = _end_text;
_start_data_copi = _end_text + _size_rodata;
_start_bss_copi = _end_text + _size_rodata + _size_data;
