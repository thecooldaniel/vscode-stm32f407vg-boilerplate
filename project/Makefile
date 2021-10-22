DEVICE          = stm32f407vg
OPENCM3_DIR     =../vendor/libopencm3
INCLUDE			+= include/
BIN				+= bin/
DUMP			+= dump/
CFLAGS          += -I$(OPENCM3_DIR)/include -MD \
				-flto -std=gnu99 \
				-Wall -Wextra -Wimplicit-function-declaration \
				-Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes \
				-Wundef -Wshadow \
				-fno-common -MD
LDFLAGS         = -static -nostartfiles
LDLIBS          += -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/gcc-config.mk

.PHONY: main_debug
main_debug: clean
main_debug: CFLAGS += -O0 -g -ggdb3 
main_debug: $(INCLUDE)hal-stm32f4.o
main_debug: $(INCLUDE)randombytes.o
main_debug: OBJS = main.c $(INCLUDE)main.s $(INCLUDE)x25519/curve25519-m4f-ptrswap-gcc-minified.s $(INCLUDE)x25519/x25519-cortex-m4-gcc.s  $(INCLUDE)hal-stm32f4.o $(INCLUDE)randombytes.o
main_debug: LDSCRIPT = stm32f407vg.ld
main_debug:
	$(CC) -o $(BIN)main.elf $(OBJS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -T$(LDSCRIPT) $(ARCH_FLAGS)

.PHONY: main
main: clean
main: CFLAGS += -O3
main: $(INCLUDE)hal-stm32f4.o
main: $(INCLUDE)randombytes.o
main: OBJS = main.c $(INCLUDE)main.s $(INCLUDE)x25519/curve25519-m4f-ptrswap-gcc-minified.s $(INCLUDE)x25519/x25519-cortex-m4-gcc.s $(INCLUDE)hal-stm32f4.o $(INCLUDE)randombytes.o
main: LDSCRIPT = stm32f407vg.ld
main:
	$(CC) -o $(BIN)main.elf $(OBJS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -T$(LDSCRIPT) $(ARCH_FLAGS)
	$(CC) -o $(BIN)main.bin $(OBJS) $(CFLAGS) $(LDLIBS) $(LDFLAGS) -T$(LDSCRIPT) $(ARCH_FLAGS)

.PHONY: clean
clean:
	$(Q)$(RM) -rf $(BIN)*.bin $(BIN)*.elf $(INCLUDE)*.o $(BIN)**.hex $(BIN)**.d $(DUMP)*.*

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

$(shell mkdir -p $(BIN))