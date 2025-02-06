const unsigned long long NINSTR = 15*100;
const unsigned long long NFPOPS = NINSTR;

#define REPEAT10(_x) \
  _x _x _x _x _x _x _x _x _x _x

#define REPEAT100(_x) \
  REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) \
  REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x) REPEAT10(_x)

void work() {
  asm("pushq %rbx;"
      "pushq %rbp;"
      "pushq %r12;"
      "pushq %r13;"
      "pushq %r14;"
      "pushq %r15;"
  );

  REPEAT100(
    asm("add %rax, %rax;"
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
        "add %r13, %r13;"
        "add %r14, %r14;"
        "add %r15, %r15;"
    );
  )

  asm("popq %r15;"
      "popq %r14;"
      "popq %r13;"
      "popq %r12;"
      "popq %rbp;"
      "popq %rbx;"
  );
}
