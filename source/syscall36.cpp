#include "common.h"
#include "peek_poke.h"
#include "hvcall.h"
#include "mm.h"
#include <string.h>
#include <psl1ght/lv2.h>
u64 mmap_lpar_addr;
extern unsigned char bdemu[0x1380];

int map_lv1()
{
	int result = lv1_undocumented_function_114(HV_START_OFFSET, HV_PAGE_SIZE, HV_SIZE, &mmap_lpar_addr);
	if (result != 0) return 0;

	result =  mm_map_lpar_memory_region(mmap_lpar_addr, HV_BASE, HV_SIZE, HV_PAGE_SIZE, 0);
	if (result) return 0;

	return 1;
}


void unmap_lv1()
{
	if (mmap_lpar_addr != 0) lv1_undocumented_function_115(mmap_lpar_addr);
}

int lv2launch(u64 addr) { 
	system_call_8(9, (u64) addr, 0,0,0,0,0,0,0); 
	return_to_user_prog(int);
}

void hermes_payload_341(void)
{
	if( Lv2Syscall1(6, 0x8000000000017CE0ULL) == 0x7C6903A64E800420ULL) return;  	
    int l, n;

    for(l = 0; l < 25; l++) 
	{
        u8 * p = (u8 *) bdemu;
        for(n = 0; n < 3840; n += 8) 
		{
            static u64 value;
            memcpy(&value, &p[n], 8);
            Lv2Syscall2(7, 0x80000000007e0000ULL + (u64) n, ~value);
            __asm__("sync");
            value =  Lv2Syscall1(6, 0x8000000000000000ULL);
		}
        // enable syscall9
        Lv2Syscall2(7, 0x8000000000017CE0ULL , 0x7C6903A64E800420ULL);
        __asm__("sync");
    }
	if(Lv2Syscall1(6, 0x8000000000017CE0ULL) == 0x7C6903A64E800420ULL)    	
		lv2launch(0x80000000007e0000ULL);
    __asm__("sync");
}


void psgroove_main(int enable)
{
		if(	Lv2Syscall1(6, 0x8000000000346690ULL) == 0x80000000002BE570ULL ) return;

		install_new_poke();
		if (!map_lv1()) { remove_new_poke(); return; }
		Lv2Syscall2(7, HV_BASE + HV_OFFSET +  0, 0x0000000000000001ULL);
		Lv2Syscall2(7, HV_BASE + HV_OFFSET +  8, 0xe0d251b556c59f05ULL);
		Lv2Syscall2(7, HV_BASE + HV_OFFSET + 16, 0xc232fcad552c80d7ULL);
		Lv2Syscall2(7, HV_BASE + HV_OFFSET + 24, 0x65140cd200000000ULL);
		unmap_lv1();
		remove_new_poke();

		if(enable==0) 
		{
		    int n=0;
			u64 val=0x0000000000000000ULL;
		    u8 * p = (u8 *) bdemu;

			// 34 @ 2D8430 (110)
		    for(n = 0; n < 0x110; n += 8) { memcpy(&val, &p[n+0xd8], 8); Lv2Syscall2(7, 0x80000000002D8430ULL + (u64) n, ~val); }

			// 27 @ 2BE4A0 (D8)
		    for(n = 0; n < 0xd8; n += 8) {  memcpy(&val, &p[n], 8); Lv2Syscall2(7, 0x80000000002BE4A0ULL + (u64) n, ~val); }

			Lv2Syscall2(7, 0x80000000002D8498ULL, 0x38A000064BD7623DULL ); // 06 symbols search /dev_b
			Lv2Syscall2(7, 0x80000000002D8504ULL, 0x38A000024BD761D1ULL ); // 0x002D7800 (/app_home) 2 search

		}

		Lv2Syscall2(7, 0x8000000000055EA0ULL, 0x63FF003D60000000ULL ); // fix 8001003D error
		Lv2Syscall2(7, 0x8000000000055F64ULL, 0x3FE080013BE00000ULL ); // fix 8001003E error

		Lv2Syscall2(7, 0x8000000000055F10ULL, 0x419E00D860000000ULL );
		Lv2Syscall2(7, 0x8000000000055F18ULL, 0x2F84000448000098ULL );
		Lv2Syscall2(7, 0x800000000007AF64ULL, 0x2F83000060000000ULL );
		Lv2Syscall2(7, 0x800000000007AF78ULL, 0x2F83000060000000ULL );

		if(enable==0) {
			Lv2Syscall2(7, 0x8000000000346690ULL, 0x80000000002BE570ULL ); // enable syscall36
			Lv2Syscall2(7, 0x80000000002B3274ULL, 0x480251EC2BA30420ULL ); // hook open
		}
}

void hermes_payload_355(int enable)
{
		if(	Lv2Syscall1(6, 0x8000000000346690ULL) == 0x800000000000F010ULL ) return;

		install_new_poke();
		if (!map_lv1()) { remove_new_poke(); return; }
		Lv2Syscall2(7, HV_BASE + HV_OFFSET +  0, 0x0000000000000001ULL);
		Lv2Syscall2(7, HV_BASE + HV_OFFSET +  8, 0xe0d251b556c59f05ULL);
		Lv2Syscall2(7, HV_BASE + HV_OFFSET + 16, 0xc232fcad552c80d7ULL);
		Lv2Syscall2(7, HV_BASE + HV_OFFSET + 24, 0x65140cd200000000ULL);
		unmap_lv1();
		remove_new_poke();

		if(enable==0) 
		{
		    int n=0;
			u64 val=0x0000000000000000ULL;
		    u8 * p = (u8 *) bdemu;

		    for(n = 0; n < 0x200; n += 8) { memcpy(&val, &p[n], 8); Lv2Syscall2(7, 0x800000000000EF48ULL + (u64) n, ~val); }
		    for(n = 0; n < 0x200; n += 8) { memcpy(&val, &p[n+0x200], 8); Lv2Syscall2(7, 0x800000000000F1E8ULL + (u64) n, ~val); }
		}

		Lv2Syscall2(7, 0x8000000000055EA0ULL, 0x63FF003D60000000ULL ); // fix 8001003D error
		Lv2Syscall2(7, 0x8000000000055F64ULL, 0x3FE080013BE00000ULL ); // fix 8001003E error

		Lv2Syscall2(7, 0x8000000000055F10ULL, 0x419E00D860000000ULL );
		Lv2Syscall2(7, 0x8000000000055F18ULL, 0x2F84000448000098ULL );
		Lv2Syscall2(7, 0x800000000007AF64ULL, 0x2F83000060000000ULL );
		Lv2Syscall2(7, 0x800000000007AF78ULL, 0x2F83000060000000ULL );

		if(enable==0) {
			Lv2Syscall2(7, 0x8000000000346690ULL, 0x800000000000F010ULL ); // enable syscall36
			Lv2Syscall2(7, 0x80000000003465B0ULL, 0x800000000000F2E0ULL ); // enable syscall8
			Lv2Syscall2(7, 0x80000000002b3298ULL, 0x4bd5bda04bd9b411ULL ); // hook open()
		}

}

