################################################################################
# MRS Version: {"version":"1.8.4","date":"2023/02/015"}
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
V307Loader.bin \

SECONDARY_LIST += \
V307Loader.lst \

SECONDARY_SIZE += \
V307Loader.siz \


# 所有目标
all: V307Loader.elf secondary-outputs

# 工具调用
V307Loader.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imacxw -mabi=ilp32 -msmall-data-limit=8 -msave-restore -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized  -g -T "E:\FealLeeWork\WchLoader\V307Loader\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"V307Loader.map" --specs=nano.specs --specs=nosys.specs -o "V307Loader.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
V307Loader.bin: V307Loader.elf
	@	riscv-none-embed-objcopy -O binary "V307Loader.elf"  "V307Loader.bin"
	@	@
V307Loader.lst: V307Loader.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "V307Loader.elf" > "V307Loader.lst"
	@	@
V307Loader.siz: V307Loader.elf
	@	riscv-none-embed-size --format=berkeley "V307Loader.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) V307Loader.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
