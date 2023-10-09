/* エントリーポイント */
ENTRY(boot)

SECTIONS {
    /* ベースアドレス */
    . = 0x80200000;

    /* 実行可能なコードを格納する */
    .text :{
        KEEP(*(.text.boot));
        *(.text .text.*);
    }

    /* 読み取り専用のデータを格納する */
    .rodata : ALIGN(4) {
        *(.rodata .rodata.*);
    }

    /* 読み書き可能なデータを格納する */
    .data : ALIGN(4) {
        *(.data .data.*);
    }

    /*
     * 読み書き可能データを格納する
     * 初期値がゼロの変数を配置
    */
    .bss : ALIGN(4) {
        __bss = .;
        *(.bss .bss.* .sbss .sbss.*);
        __bss_end = .;
    }

    /* 現在の位置を次の4バイト境界に移動する */
    . = ALIGN(4);
    /* 128KB 進める */
    . += 128 * 1024;
    __stack_top = .;
}
