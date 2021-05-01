DEVICE          = stm32f407vg
OPENCM3_DIR     =../vendor/libopencm3
INCLUDE			+= include/
BIN				+= bin/
DUMP			+= dump/
CFLAGS          += -DSTM32F4 -DSTM32F4CCM -DSTM32F407VG -I$(OPENCM3_DIR)/include
LDFLAGS         = -static -nostartfiles
LDLIBS          += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: main_debug
main_debug: clean
main_debug: CFLAGS += -O0 -g -ggdb3 -flto
main_debug: $(INCLUDE)stm32wrapper.o
main_debug: OBJS = main.c $(INCLUDE)main.s $(INCLUDE)stm32wrapper.o
main_debug: LDSCRIPT = stm32f407vg.ld
main_debug:
	@mkdir -p $(BIN)
	$(CC) -o $(BIN)main.elf $(OBJS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -T$(LDSCRIPT) $(ARCH_FLAGS)

.PHONY: main
main: clean
main: CFLAGS += -O3 -flto
main: $(INCLUDE)stm32wrapper.o
main: OBJS = main.c $(INCLUDE)main.s $(INCLUDE)stm32wrapper.o
main: LDSCRIPT = stm32f407vg.ld
main:
	@mkdir -p $(BIN) 
	$(CC) -o $(BIN)main.elf $(OBJS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -T$(LDSCRIPT) $(ARCH_FLAGS)

.PHONY: clean
clean:
	$(Q)$(RM) -rf $(BIN)*.bin $(BIN)*.elf $(INCLUDE)*.o $(BIN)**.hex $(BIN)**.d $(DUMP)/*.*

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