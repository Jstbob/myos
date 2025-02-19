
#ifndef _IDT_H_
#define _IDT_H_

#include "idt.h"
#include <stdint.h>

//  P DPL, P为段存在标志，DPL为0、3权限级别。
// b1 00 00101 0000 0000
// b1 00 01110 0000 0000
// b1 00 01111 0000 0000
// 反向存储
#define PRI_TASK_GATE 0x8500
#define PRI_INT_GATE 0x8e00
#define PRI_TRAP_GATE 0x8f00

struct [[gnu::packed]] gate_descriptor {
    uint16_t offset_d;
    uint16_t sel;
    uint16_t pri; // P、DPL，有三种不同的描述符
    uint16_t offset_h;
};

#define ENTRIES 256

// idt table
static struct gate_descriptor idt[ENTRIES] [[gnu::aligned(4)]];

struct [[gnu::packed]] idtr_t {
    uint16_t limit;
    struct gate_descriptor *base;
};

void init_idt();

#define KEYBOARD_BUFF_SIZE 256
static char keyboard_buff[KEYBOARD_BUFF_SIZE];
static char *cur_ptr = &keyboard_buff[0];
static uint32_t start_process_flag = 0;

void keyboard_write(char data);
void open_keyboard();
void close_keyboard();
int parse_option(char *name, int *args, char **argv);
void keyboard_flush();

void test_cmd();

void intx80_handler(uint8_t code);

// asm.S中的中断号响应函数
extern void int0();
extern void int1();
extern void int2();
extern void int3();
extern void int4();
extern void int5();
extern void int6();
extern void int7();
extern void int8();
extern void int9();
extern void int10();
extern void int11();
extern void int12();
extern void int13();
extern void int14();
extern void int15();
extern void int16();
extern void int17();
extern void int18();
extern void int19();
extern void int20();
extern void int21();
extern void int22();
extern void int23();
extern void int24();
extern void int25();
extern void int26();
extern void int27();
extern void int28();
extern void int29();
extern void int30();
extern void int31();
extern void int32();
extern void int33();
extern void int34();
extern void int35();
extern void int36();
extern void int37();
extern void int38();
extern void int39();
extern void int40();
extern void int41();
extern void int42();
extern void int43();
extern void int44();
extern void int45();
extern void int46();
extern void int47();
extern void int48();
extern void int49();
extern void int50();
extern void int51();
extern void int52();
extern void int53();
extern void int54();
extern void int55();
extern void int56();
extern void int57();
extern void int58();
extern void int59();
extern void int60();
extern void int61();
extern void int62();
extern void int63();
extern void int64();
extern void int65();
extern void int66();
extern void int67();
extern void int68();
extern void int69();
extern void int70();
extern void int71();
extern void int72();
extern void int73();
extern void int74();
extern void int75();
extern void int76();
extern void int77();
extern void int78();
extern void int79();
extern void int80();
extern void int81();
extern void int82();
extern void int83();
extern void int84();
extern void int85();
extern void int86();
extern void int87();
extern void int88();
extern void int89();
extern void int90();
extern void int91();
extern void int92();
extern void int93();
extern void int94();
extern void int95();
extern void int96();
extern void int97();
extern void int98();
extern void int99();
extern void int100();
extern void int101();
extern void int102();
extern void int103();
extern void int104();
extern void int105();
extern void int106();
extern void int107();
extern void int108();
extern void int109();
extern void int110();
extern void int111();
extern void int112();
extern void int113();
extern void int114();
extern void int115();
extern void int116();
extern void int117();
extern void int118();
extern void int119();
extern void int120();
extern void int121();
extern void int122();
extern void int123();
extern void int124();
extern void int125();
extern void int126();
extern void int127();
extern void int128();
extern void int129();
extern void int130();
extern void int131();
extern void int132();
extern void int133();
extern void int134();
extern void int135();
extern void int136();
extern void int137();
extern void int138();
extern void int139();
extern void int140();
extern void int141();
extern void int142();
extern void int143();
extern void int144();
extern void int145();
extern void int146();
extern void int147();
extern void int148();
extern void int149();
extern void int150();
extern void int151();
extern void int152();
extern void int153();
extern void int154();
extern void int155();
extern void int156();
extern void int157();
extern void int158();
extern void int159();
extern void int160();
extern void int161();
extern void int162();
extern void int163();
extern void int164();
extern void int165();
extern void int166();
extern void int167();
extern void int168();
extern void int169();
extern void int170();
extern void int171();
extern void int172();
extern void int173();
extern void int174();
extern void int175();
extern void int176();
extern void int177();
extern void int178();
extern void int179();
extern void int180();
extern void int181();
extern void int182();
extern void int183();
extern void int184();
extern void int185();
extern void int186();
extern void int187();
extern void int188();
extern void int189();
extern void int190();
extern void int191();
extern void int192();
extern void int193();
extern void int194();
extern void int195();
extern void int196();
extern void int197();
extern void int198();
extern void int199();
extern void int200();
extern void int201();
extern void int202();
extern void int203();
extern void int204();
extern void int205();
extern void int206();
extern void int207();
extern void int208();
extern void int209();
extern void int210();
extern void int211();
extern void int212();
extern void int213();
extern void int214();
extern void int215();
extern void int216();
extern void int217();
extern void int218();
extern void int219();
extern void int220();
extern void int221();
extern void int222();
extern void int223();
extern void int224();
extern void int225();
extern void int226();
extern void int227();
extern void int228();
extern void int229();
extern void int230();
extern void int231();
extern void int232();
extern void int233();
extern void int234();
extern void int235();
extern void int236();
extern void int237();
extern void int238();
extern void int239();
extern void int240();
extern void int241();
extern void int242();
extern void int243();
extern void int244();
extern void int245();
extern void int246();
extern void int247();
extern void int248();
extern void int249();
extern void int250();
extern void int251();
extern void int252();
extern void int253();
extern void int254();
extern void int255();

#endif