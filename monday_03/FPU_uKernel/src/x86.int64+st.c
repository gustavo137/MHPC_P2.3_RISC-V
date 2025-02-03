const unsigned long long NINSTR = 20*100;
const unsigned long long NFPOPS = NINSTR;

#define REPEAT10(_x) \
  _x _x _x _x _x _x _x _x _x _x

#define REPEAT100(_x) \
  REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) \
  REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x)

#define REPEAT1000(_x) \
  REPEAT100(_x) REPEAT100(_x) REPEAT100(_x) REPEAT100(_x) REPEAT100(_x) \
  REPEAT100(_x) REPEAT100(_x) REPEAT100(_x) REPEAT100(_x) REPEAT100(_x)

void work() {
  asm("pushq %rbx;"
      "pushq %rbp;"
      "pushq %r12;"
      "pushq %r13;"
      "pushq %r14;"
      "pushq %r15;"
  );

  //REPEAT10(
    asm(
        "mov $100, %r15;"
      "loop:"
        "mov -0x0(%rsp), %r10;"
        "mov -0x0(%rsp), %r11;"
        "mov -0x0(%rsp), %r12;"
        "add %rax, %rax;"
        "add %rbx, %rbx;"
        "add %rcx, %rcx;"

        "add %rdx, %rdx;"
        "add %rdi, %rdi;"
        "add %rsi, %rsi;"
        "add %rbp, %rbp;"
        "add  %r8,  %r8;"
        "add  %r9,  %r9;"

        "add %r10, %r10;"
        "add %r11, %r11;"
        "add %r12, %r12;"
        "add %rdx, %rcx;"
        "add %r8, %rdx;"
        "add %r9, %rdi;"
        
        "dec %r15;"
        "jnz loop;"
    );

  asm("popq %r15;"
      "popq %r14;"
      "popq %r13;"
      "popq %r12;"
      "popq %rbp;"
      "popq %rbx;"
  );
}
