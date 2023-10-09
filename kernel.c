typedef unsigned char uint8_t;
typedef unsigned int uint32_t;
typedef uint32_t size_t;

/*
 * リンカスクリプト内で定義されている各シンボルをextern charで宣言
 */
extern char __bss[], __bss_end[], __stack_top[];

void *memset(void *buf, char c, size_t n) {
    uint8_t *p = (uint8_t *) buf;
    while (n--)
        *p++ = c;
    return buf;
}

/* memset関数を使って.bss領域をゼロで初期化 */
void kernel_main(void) {
    memset(__bss, 0, (size_t) __bss_end - (size_t) __bss);

    for (;;);
}

__attribute__((section(".text.boot")))
/*
 * リンカスクリプトで定義されているシンボルを使って、
 * ブートローダから渡されたスタックトップアドレスを
 * spレジスタに設定し、kernel_mainにジャンプする
 */
__attribute__((naked))
void boot(void) {
    __asm__ __volatile__(
        "mv sp, %[stack_top]\n"
        "j kernel_main\n"
        :
        : [stack_top] "r" (__stack_top)
    );
}
