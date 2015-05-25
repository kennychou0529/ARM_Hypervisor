#include <asm/processor.h>
#include <asm/cpregs.h>
#include <asm/types.h>
#include <asm/page.h>
#include <asm/types.h>
#include <asm/guest_init.h>
#include <string.h>
#include <config.h>
#include <stdio.h>

static void vctr_write(unsigned long val)
{
  WRITE_SYSREG32(val, VTCR_EL2);
  isb();
}

static void vctr_init(void)
{
  unsigned long vctr_val = VTCR_RES1|VTCR_SH0_IS|VTCR_ORGN0_WBWA|VTCR_IRGN0_WBWA;
  vctr_val |= VTCR_T0SZ(0x18); /* 40 bit IPA */
  vctr_val |= VTCR_SL0(0x1); /* P2M starts at first level */
  vctr_write(vctr_val);
}

void guest_init(void)
{
  vctr_init();
  guest_ept_init();
  copy_guest();
}

extern lpae_t guest_ept_L1[LPAE_ENTRIES];
extern lpae_t guest_ept_L2[LPAE_ENTRIES][LPAE_ENTRIES];
extern lpae_t guest_ept_L3[LPAE_ENTRIES][LPAE_ENTRIES][LPAE_ENTRIES];
void guest_ept_init(void)
{
  int index_l1;
  unsigned long gpa = 0;
  unsigned long tmp = (unsigned long)&guest_ept_L1[0];
  unsigned long long vttbr_val = (unsigned long long)tmp;
  unsigned long hcr;
  for(index_l1 = 0 ; index_l1 < LPAE_ENTRIES ; index_l1++)
  {
    lpae_t e;
    e.bits = 0x7C5;
    e.bits |= gpa;
    guest_ept_L1[index_l1] = e;
    gpa += 1024*1024*1024;
    // memset(&guest_ept_L1[index_l1],0,sizeof(lpae_t));
    // guest_ept_L1[index_l1].walk.base = (unsigned long)guest_ept_L2[index_l1];
    // guest_ept_L1[index_l1].walk.table = 1;
    // guest_ept_L1[index_l1].walk.valid = 1;
    // for(index_l2 = 0 ; index_l2 < LPAE_ENTRIES ; index_l2++)
    // {
    //   memset(&guest_ept_L2[index_l1][index_l2],0,sizeof(lpae_t));
    //   guest_ept_L2[index_l1][index_l2].walk.base = (unsigned long)guest_ept_L3[index_l1][index_l2];
    //   guest_ept_L2[index_l1][index_l2].walk.table = 1;
    //   guest_ept_L2[index_l1][index_l2].walk.valid = 1;
    //   for(index_l3 = 0 ; index_l3 < LPAE_ENTRIES ; index_l3++)
    //   {
    //     lpae_t e = (lpae_t) {
    //       .pt = {
    //         .xn = 0,              /* No need to execute outside .text */
    //         .ng = 1,              /* Makes TLB flushes easier */
    //         .af = 1,              /* No need for access tracking */
    //         .ns = 1,              /* Hyp mode is in the non-secure world */
    //         .user = 1,            /* See below */
    //         .ai = 0,
    //         .table = 1,           /* Set to 1 for links and 4k maps */
    //         .valid = 1,           /* Mappings are present */
    //         .base = gpa
    //       }};
    //       memset(&guest_ept_L3[index_l1][index_l2][index_l3],0,sizeof(lpae_t));
    //       gpa += 4096;
    //       guest_ept_L3[index_l1][index_l2][index_l3] = e;
    //     }
    //   }
    }

    // Write EPT to VTTBR
    WRITE_SYSREG64(vttbr_val,VTTBR_EL2);

    // Turn on Stage 2 Address Translation
    hcr = READ_SYSREG(HCR_EL2);
    WRITE_SYSREG(hcr | HCR_VM, HCR_EL2);
    isb();
}

void copy_guest(void)
{
  unsigned long *from = (unsigned long*)KERNEL_ADDR;
  unsigned long *to = (unsigned long*)KERNEL_START;
  printf("Copy guest kernel image from %x to %x (%d bytes)\n",from,to,KERNEL_SIZE);
  memcpy(to,from,KERNEL_SIZE);
  printf("Copy end : %x\n",*to);
}

extern void guest_start(unsigned long addr);
void guest_boot(void)
{
  printf("Jump to %x\n",guest_start);
  guest_start(KERNEL_START);
}
