DEVICE          = stm32f407vg
OPENCM3_DIR     =../vendor/libopencm3
INCLUDE_DIR		+= include/
BIN_DIR			+= bin/
CFLAGS          += -I$(OPENCM3_DIR)/include
LDFLAGS         += -static -nostartfiles
LDLIBS          += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: main_debug
main_debug: clean
main_debug: CFLAGS += -O0 -g -ggdb3 -DSTM32F4 -DSTM32F4CCM -DSTM32F407VG
main_debug: include/stm32wrapper.o
main_debug: OBJS = main.c include/main.s include/stm32wrapper.o
main_debug: LDSCRIPT = stm32f407g.ld
main_debug: 
	$(CC) -o bin/main_debug.elf $(OBJS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -T$(LDSCRIPT) $(ARCH_FLAGS)

.PHONY: clean
clean:
	$(Q)$(RM) -rf *.bin *.elf *.o *.hex *.d

.PHONY: lib
lib:
	@if [ ! "`ls -A $(OPENCM3_DIR)`" ] ; then \
		printf "######## ERROR ########\n"; \
		printf "\tlibopencm3 is not initialized.\n"; \
		printf "\tPlease run (in the root directory):\n"; \
		printf "\t$$ git submodule init\n"; \
		printf "\t$$ git submodule update\n"; \
		printf "\tbefore running make.\n"; \
		printf "######## ERROR ########\n"; \
		exit 1; \
		fi
	make -C $(OPENCM3_DIR)

include $(OPENCM3_DIR)/mk/genlink-rules.mk
include $(OPENCM3_DIR)/mk/gcc-rules.mk