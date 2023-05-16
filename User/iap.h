#ifndef __IAP_H_
#define __IAP_H_

 #define IAP_SIMULATE
#define IAP_PAGE_SIZE 256

/*

                   FLASH MAP(256K)

           0 1 2 3 4 5 6 7 8 9 A B C D E F
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
00000000H |                               |
          .        BootLoader(31K)        .
          |                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
00007C00H |                               |
          .   BootLoader Settings(256B)   .
          |                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
00007D00H |                               |
          .  Application Settings (768B)  .
          |                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
00008000H |                               |
          .       Application(112K)       .
          |                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
00024000H |                               |
          .         Reserve(112K)         .
0003FFF0H |                               |
          +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
*/

#define IAP_ADDRESS_BOOTLOADER_SETTINGS 0x00007C00
#define IAP_ADDRESS_APPLICATION 0x00008000
#define IAP_ADDRESS_RESERVE 0x00024000

void iap_init(void);
void iap_update(void);
void iap_jump(void);

#endif
