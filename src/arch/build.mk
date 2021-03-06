BUILD-ARCH-ASM += arch/head.o
BUILD-ARCH-ASM += arch/entry.o
BUILD-ARCH-ASM += arch/stage2_pgt.o

BUILD-ARCH += arch/init.o
BUILD-ARCH += arch/boot_env.o
BUILD-ARCH += arch/guest_init.o
BUILD-ARCH += arch/guest_env.o
BUILD-ARCH += arch/traps.o
BUILD-ARCH += arch/ept_violation.o
BUILD-ARCH += arch/debug.o
BUILD-ARCH += arch/mmio.o
BUILD-ARCH += arch/spinlock.o
