#include <string.h>
#include "debug.h"
#include "iap.h"

typedef struct
{
    uint32_t application_version;
    uint32_t reserve_version;
} _settings_type;

static const _settings_type *_settings = (_settings_type *)(FLASH_BASE + IAP_ADDRESS_BOOTLOADER_SETTINGS);

static void write_settings(uint32_t application_version, uint32_t reserve_version)
{
    uint32_t buf[64];
    memcpy(buf, _settings, sizeof(_settings_type));
    buf[0] = application_version;
    buf[1] = reserve_version;
    FLASH_Unlock_Fast();
    FLASH_ErasePage_Fast(FLASH_BASE + IAP_ADDRESS_BOOTLOADER_SETTINGS);
    FLASH_ProgramPage_Fast(FLASH_BASE + IAP_ADDRESS_BOOTLOADER_SETTINGS, buf);
    FLASH_Lock_Fast();
}

void iap_init(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    USART_Printf_Init(115200);

    printf("\nThe bootloader for CH32V307. Powered by feallee@hotmail.com.\n");
    printf("%08XH\tBootloader Settings\n", IAP_ADDRESS_BOOTLOADER_SETTINGS);
    printf("%08XH\tApplication\n", IAP_ADDRESS_APPLICATION);
    printf("%08XH\tReserve\n", IAP_ADDRESS_RESERVE);
#ifdef IAP_SIMULATE
    write_settings(1, 2);
#endif
}

void iap_update(void)
{
    uint32_t i;
    uint8_t ret = 1;
    uint64_t *a = (uint64_t *)(FLASH_BASE + IAP_ADDRESS_APPLICATION), *r = (uint64_t *)(FLASH_BASE + IAP_ADDRESS_RESERVE);
    while (_settings->reserve_version > _settings->application_version)
    {
        printf("\nUpdate firmware: Version %u -> Version %u.\n", _settings->application_version, _settings->reserve_version);
        FLASH_Unlock_Fast();
        for (i = 0; i < (IAP_ADDRESS_RESERVE - IAP_ADDRESS_APPLICATION) / 256; i++)
        {
            printf("Updating: %u/%u.\n", i + 1, (IAP_ADDRESS_RESERVE - IAP_ADDRESS_APPLICATION) / 256);
            FLASH_ErasePage_Fast(FLASH_BASE + IAP_ADDRESS_APPLICATION + i * 256);
            FLASH_ProgramPage_Fast(FLASH_BASE + IAP_ADDRESS_APPLICATION + i * 256, (uint32_t *)(FLASH_BASE + IAP_ADDRESS_RESERVE + i * 256));
        }
        FLASH_Lock_Fast();
        i = 0;
        while (i < (IAP_ADDRESS_RESERVE - IAP_ADDRESS_APPLICATION) / 8)
        {
            if (a[i] != r[i])
            {
                ret = 0;
                break;
            }
            i++;
        }
        if (ret)
        {
            write_settings(_settings->reserve_version, _settings->reserve_version);
        }
    }
    printf("\nUpdate completed: Version %u\n", _settings->application_version);
}

void iap_jump(void)
{
    printf("\nJump to application: %08xH...\n\n", IAP_ADDRESS_APPLICATION);
    Delay_Ms(10);
    NVIC_EnableIRQ(Software_IRQn);
    NVIC_SetPendingIRQ(Software_IRQn);
}

void SW_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void SW_Handler(void)
{
    // __asm("li  a6, 0x8000");
    __asm("jr  %0" ::"r"(IAP_ADDRESS_APPLICATION));
    while (1)
        ;
}
