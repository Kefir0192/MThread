#===========================================================================
# MAIN
#===========================================================================
NAMEPROJ   =test_1986ve92u

TOOLCHAIN  =D:/ARMprj/armTool/bin/
PATH_PROJ  =D:/ARMprj/NEWThread/MThread/sources/example/test_1986ve92u/file/
PATH_INCLU =$(PATH_PROJ)

PATH_BIN   =$(PATH_PROJ)bin/
PATH_SRC   =$(PATH_PROJ)src/
PATH_INC   =$(PATH_PROJ)inc/

CC         =$(TOOLCHAIN)arm-none-eabi-gcc
AS         =$(TOOLCHAIN)arm-none-eabi-as
LD         =$(TOOLCHAIN)arm-none-eabi-ld
OBJDUMP    =$(TOOLCHAIN)arm-none-eabi-objdump
OBJCOPY    =$(TOOLCHAIN)arm-none-eabi-objcopy
SIZE       =$(TOOLCHAIN)arm-none-eabi-size



#===========================================================================
# MThread
#===========================================================================
# MThread_Platform =
# ARM_CM0
# ARM_CM0_Plus
# ARM_CM3
# ARM_CM4
MThread_Platform=ARM_CM0

# Рабочий каталог
MThread_p_port   =../../../kernel/portable/
MThread_p_mthread=../../../kernel/mthread/

# Дополнительные пути
MThread_p_port_inc=$(MThread_p_port)inc/
MThread_p_port_src=$(MThread_p_port)src/

# Дополнительные включения
MThread_p_port_I= \
          -I$(MThread_p_port_inc) \
		  -I$(MThread_p_port_inc)$(MThread_Platform)

# Дополнительные пути
MThread_p_mthread_inc=$(MThread_p_mthread)inc/
MThread_p_mthread_src=$(MThread_p_mthread)src/

# Дополнительные включения
MThread_p_mthread_I= \
          -I$(MThread_p_mthread_inc)
		  
# Дополнительные включения	  
MThread_I=$(MThread_p_port_I) $(MThread_p_mthread_I)


MThread_inc= \
    $(MThread_p_port_inc)$(MThread_Platform)/portmacro.h \
	$(MThread_p_mthread_inc)task.h \
	$(MThread_p_mthread_inc)task_switch.h \
	$(MThread_p_mthread_inc)mutex.h \
	$(MThread_p_mthread_inc)delay.h
	
MThread_opj= \
	port_s.o \
	port_c.o \
	task.o \
	task_switch.o \
	mutex.o \
	delay.o



port_s.o: $(MThread_p_port_src)$(MThread_Platform)/port.s $(MThread_inc)
	$(CC) $(COMPILOP) -c $(MThread_p_port_src)$(MThread_Platform)/port.s -o port_s.o
	
port_c.o: $(MThread_p_port_src)$(MThread_Platform)/port.c $(MThread_inc)
	$(CC) $(COMPILOP) -c $(MThread_p_port_src)$(MThread_Platform)/port.c -o port_c.o

task.o: $(MThread_p_mthread_src)task.c $(MThread_inc)
	$(CC) $(COMPILOP) -c $(MThread_p_mthread_src)task.c -o task.o
	
task_switch.o: $(MThread_p_mthread_src)task_switch.c $(MThread_inc)
	$(CC) $(COMPILOP) -c $(MThread_p_mthread_src)task_switch.c -o task_switch.o
	
mutex.o: $(MThread_p_mthread_src)mutex.c $(MThread_inc)
	$(CC) $(COMPILOP) -c $(MThread_p_mthread_src)mutex.c -o mutex.o
	
delay.o: $(MThread_p_mthread_src)delay.c $(MThread_inc)
	$(CC) $(COMPILOP) -c $(MThread_p_mthread_src)delay.c -o delay.o



#===========================================================================
# MAIN FLAGS COMPIL
#===========================================================================
MAIN_I     =-I$(PATH_INC) \
            -I$(PATH_INC)cmsis \
            $(MThread_I)
			
COMPILOP   =-g -O0 -nostdlib -ffreestanding -Wall -mthumb  -mcpu=cortex-m3 $(MAIN_I) -std=c99
ASMOP      =-g -Wall -mthumb  -mcpu=cortex-m3 $(MAIN_I)
LINKOP     =-T link.ld -Map=$(PATH_BIN)$(NAMEPROJ).map



#===========================================================================
# MAIN
#===========================================================================
AFINC= \
	$(PATH_INC)globalincludefile.h \
	$(PATH_INC)main.h \
	$(PATH_INC)startup_1986ve92.h \
	$(PATH_INC)phisic.h

AFOBJ= \
	startup.o \
	startup_1986ve92.o \
	main.o \
	phisic.o


.PHONY : all
all: $(AFOBJ) $(MThread_opj)
	@$(LD) -o $(PATH_BIN)$(NAMEPROJ).elf $(LINKOP) $(AFOBJ) $(MThread_opj) $(LIB_OP)
	@$(OBJDUMP) -D $(PATH_BIN)$(NAMEPROJ).elf > $(PATH_BIN)$(NAMEPROJ).asm
	@$(OBJCOPY) $(PATH_BIN)$(NAMEPROJ).elf $(PATH_BIN)$(NAMEPROJ).bin -O binary
	

startup.o: $(PATH_INCLU)startup.S $(AFINC)
	$(AS) $(ASMOP) -c $(PATH_INCLU)startup.S -o startup.o
	
startup_1986ve92.o: $(PATH_SRC)startup_1986ve92.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)startup_1986ve92.c -o startup_1986ve92.o
	
phisic.o: $(PATH_SRC)phisic.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)phisic.c -o phisic.o

main.o: $(PATH_SRC)main.c $(AFINC)
	$(CC) $(COMPILOP) -c $(PATH_SRC)main.c -o main.o
#===========================================================================
# All
#===========================================================================

	
#===========================================================================
.PHONY : clean
clean:
	-@$(PATH_PROJ)clear.bat
	-$(SIZE) $(PATH_BIN)$(NAMEPROJ).elf