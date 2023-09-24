#include "idt.h"
#include "asm.h"
#include "boot.h"
#include "console.h"
#include "kbd.h"
#include "mem_r.h"
#include "pic.h"

static struct idtr_t idtr [[gnu::aligned(32)]]
= { .limit = sizeof(idt) - 1, .base = &idt[0] };

void set_gate(uint16_t index, uint16_t pri, uint16_t sel, uint32_t offset) {
    idt[index].offset_d = offset & 0x0000ffff;
    idt[index].offset_h = offset >> 16;
    idt[index].pri = pri;
    idt[index].sel = sel;
}

// debug_handler，测试通过
void idt_debug() {
    asm volatile("cli");
    panic("int");
}

// 中断号0-31被系统保留，这些中断由cpu内部引发
// 选择子为0,0x08,0x10,0x18,0x20
void init_idt() {
    set_gate(0, PRI_INT_GATE, 0x08, (uint32_t)&int0);
    set_gate(1, PRI_INT_GATE, 0x08, (uint32_t)&int1);
    set_gate(2, PRI_INT_GATE, 0x08, (uint32_t)&int2);
    set_gate(3, PRI_INT_GATE, 0x08, (uint32_t)&int3);
    set_gate(4, PRI_INT_GATE, 0x08, (uint32_t)&int4);
    set_gate(5, PRI_INT_GATE, 0x08, (uint32_t)&int5);
    set_gate(6, PRI_INT_GATE, 0x08, (uint32_t)&int6);
    set_gate(7, PRI_INT_GATE, 0x08, (uint32_t)&int7);
    set_gate(8, PRI_INT_GATE, 0x08, (uint32_t)&int8);
    set_gate(9, PRI_INT_GATE, 0x08, (uint32_t)&int9);
    set_gate(10, PRI_INT_GATE, 0x08, (uint32_t)&int10);
    set_gate(11, PRI_INT_GATE, 0x08, (uint32_t)&int11);
    set_gate(12, PRI_INT_GATE, 0x08, (uint32_t)&int12);
    set_gate(13, PRI_INT_GATE, 0x08, (uint32_t)&int13);
    set_gate(14, PRI_INT_GATE, 0x08, (uint32_t)&int14);
    set_gate(15, PRI_INT_GATE, 0x08, (uint32_t)&int15);
    set_gate(16, PRI_INT_GATE, 0x08, (uint32_t)&int16);
    set_gate(17, PRI_INT_GATE, 0x08, (uint32_t)&int17);
    set_gate(18, PRI_INT_GATE, 0x08, (uint32_t)&int18);
    set_gate(19, PRI_INT_GATE, 0x08, (uint32_t)&int19);
    set_gate(20, PRI_INT_GATE, 0x08, (uint32_t)&int20);
    set_gate(21, PRI_INT_GATE, 0x08, (uint32_t)&int21);
    set_gate(22, PRI_INT_GATE, 0x08, (uint32_t)&int22);
    set_gate(23, PRI_INT_GATE, 0x08, (uint32_t)&int23);
    set_gate(24, PRI_INT_GATE, 0x08, (uint32_t)&int24);
    set_gate(25, PRI_INT_GATE, 0x08, (uint32_t)&int25);
    set_gate(26, PRI_INT_GATE, 0x08, (uint32_t)&int26);
    set_gate(27, PRI_INT_GATE, 0x08, (uint32_t)&int27);
    set_gate(28, PRI_INT_GATE, 0x08, (uint32_t)&int28);
    set_gate(29, PRI_INT_GATE, 0x08, (uint32_t)&int29);
    set_gate(30, PRI_INT_GATE, 0x08, (uint32_t)&int30);
    set_gate(31, PRI_INT_GATE, 0x08, (uint32_t)&int31);
    set_gate(32, PRI_INT_GATE, 0x08, (uint32_t)&int32);
    set_gate(33, PRI_INT_GATE, 0x08, (uint32_t)&int33);
    set_gate(34, PRI_INT_GATE, 0x08, (uint32_t)&int34);
    set_gate(35, PRI_INT_GATE, 0x08, (uint32_t)&int35);
    set_gate(36, PRI_INT_GATE, 0x08, (uint32_t)&int36);
    set_gate(37, PRI_INT_GATE, 0x08, (uint32_t)&int37);
    set_gate(38, PRI_INT_GATE, 0x08, (uint32_t)&int38);
    set_gate(39, PRI_INT_GATE, 0x08, (uint32_t)&int39);
    set_gate(40, PRI_INT_GATE, 0x08, (uint32_t)&int40);
    set_gate(41, PRI_INT_GATE, 0x08, (uint32_t)&int41);
    set_gate(42, PRI_INT_GATE, 0x08, (uint32_t)&int42);
    set_gate(43, PRI_INT_GATE, 0x08, (uint32_t)&int43);
    set_gate(44, PRI_INT_GATE, 0x08, (uint32_t)&int44);
    set_gate(45, PRI_INT_GATE, 0x08, (uint32_t)&int45);
    set_gate(46, PRI_INT_GATE, 0x08, (uint32_t)&int46);
    set_gate(47, PRI_INT_GATE, 0x08, (uint32_t)&int47);
    set_gate(48, PRI_INT_GATE, 0x08, (uint32_t)&int48);
    set_gate(49, PRI_INT_GATE, 0x08, (uint32_t)&int49);
    set_gate(50, PRI_INT_GATE, 0x08, (uint32_t)&int50);
    set_gate(51, PRI_INT_GATE, 0x08, (uint32_t)&int51);
    set_gate(52, PRI_INT_GATE, 0x08, (uint32_t)&int52);
    set_gate(53, PRI_INT_GATE, 0x08, (uint32_t)&int53);
    set_gate(54, PRI_INT_GATE, 0x08, (uint32_t)&int54);
    set_gate(55, PRI_INT_GATE, 0x08, (uint32_t)&int55);
    set_gate(56, PRI_INT_GATE, 0x08, (uint32_t)&int56);
    set_gate(57, PRI_INT_GATE, 0x08, (uint32_t)&int57);
    set_gate(58, PRI_INT_GATE, 0x08, (uint32_t)&int58);
    set_gate(59, PRI_INT_GATE, 0x08, (uint32_t)&int59);
    set_gate(60, PRI_INT_GATE, 0x08, (uint32_t)&int60);
    set_gate(61, PRI_INT_GATE, 0x08, (uint32_t)&int61);
    set_gate(62, PRI_INT_GATE, 0x08, (uint32_t)&int62);
    set_gate(63, PRI_INT_GATE, 0x08, (uint32_t)&int63);
    set_gate(64, PRI_INT_GATE, 0x08, (uint32_t)&int64);
    set_gate(65, PRI_INT_GATE, 0x08, (uint32_t)&int65);
    set_gate(66, PRI_INT_GATE, 0x08, (uint32_t)&int66);
    set_gate(67, PRI_INT_GATE, 0x08, (uint32_t)&int67);
    set_gate(68, PRI_INT_GATE, 0x08, (uint32_t)&int68);
    set_gate(69, PRI_INT_GATE, 0x08, (uint32_t)&int69);
    set_gate(70, PRI_INT_GATE, 0x08, (uint32_t)&int70);
    set_gate(71, PRI_INT_GATE, 0x08, (uint32_t)&int71);
    set_gate(72, PRI_INT_GATE, 0x08, (uint32_t)&int72);
    set_gate(73, PRI_INT_GATE, 0x08, (uint32_t)&int73);
    set_gate(74, PRI_INT_GATE, 0x08, (uint32_t)&int74);
    set_gate(75, PRI_INT_GATE, 0x08, (uint32_t)&int75);
    set_gate(76, PRI_INT_GATE, 0x08, (uint32_t)&int76);
    set_gate(77, PRI_INT_GATE, 0x08, (uint32_t)&int77);
    set_gate(78, PRI_INT_GATE, 0x08, (uint32_t)&int78);
    set_gate(79, PRI_INT_GATE, 0x08, (uint32_t)&int79);
    set_gate(80, PRI_INT_GATE, 0x08, (uint32_t)&int80);
    set_gate(81, PRI_INT_GATE, 0x08, (uint32_t)&int81);
    set_gate(82, PRI_INT_GATE, 0x08, (uint32_t)&int82);
    set_gate(83, PRI_INT_GATE, 0x08, (uint32_t)&int83);
    set_gate(84, PRI_INT_GATE, 0x08, (uint32_t)&int84);
    set_gate(85, PRI_INT_GATE, 0x08, (uint32_t)&int85);
    set_gate(86, PRI_INT_GATE, 0x08, (uint32_t)&int86);
    set_gate(87, PRI_INT_GATE, 0x08, (uint32_t)&int87);
    set_gate(88, PRI_INT_GATE, 0x08, (uint32_t)&int88);
    set_gate(89, PRI_INT_GATE, 0x08, (uint32_t)&int89);
    set_gate(90, PRI_INT_GATE, 0x08, (uint32_t)&int90);
    set_gate(91, PRI_INT_GATE, 0x08, (uint32_t)&int91);
    set_gate(92, PRI_INT_GATE, 0x08, (uint32_t)&int92);
    set_gate(93, PRI_INT_GATE, 0x08, (uint32_t)&int93);
    set_gate(94, PRI_INT_GATE, 0x08, (uint32_t)&int94);
    set_gate(95, PRI_INT_GATE, 0x08, (uint32_t)&int95);
    set_gate(96, PRI_INT_GATE, 0x08, (uint32_t)&int96);
    set_gate(97, PRI_INT_GATE, 0x08, (uint32_t)&int97);
    set_gate(98, PRI_INT_GATE, 0x08, (uint32_t)&int98);
    set_gate(99, PRI_INT_GATE, 0x08, (uint32_t)&int99);
    set_gate(100, PRI_INT_GATE, 0x08, (uint32_t)&int100);
    set_gate(101, PRI_INT_GATE, 0x08, (uint32_t)&int101);
    set_gate(102, PRI_INT_GATE, 0x08, (uint32_t)&int102);
    set_gate(103, PRI_INT_GATE, 0x08, (uint32_t)&int103);
    set_gate(104, PRI_INT_GATE, 0x08, (uint32_t)&int104);
    set_gate(105, PRI_INT_GATE, 0x08, (uint32_t)&int105);
    set_gate(106, PRI_INT_GATE, 0x08, (uint32_t)&int106);
    set_gate(107, PRI_INT_GATE, 0x08, (uint32_t)&int107);
    set_gate(108, PRI_INT_GATE, 0x08, (uint32_t)&int108);
    set_gate(109, PRI_INT_GATE, 0x08, (uint32_t)&int109);
    set_gate(110, PRI_INT_GATE, 0x08, (uint32_t)&int110);
    set_gate(111, PRI_INT_GATE, 0x08, (uint32_t)&int111);
    set_gate(112, PRI_INT_GATE, 0x08, (uint32_t)&int112);
    set_gate(113, PRI_INT_GATE, 0x08, (uint32_t)&int113);
    set_gate(114, PRI_INT_GATE, 0x08, (uint32_t)&int114);
    set_gate(115, PRI_INT_GATE, 0x08, (uint32_t)&int115);
    set_gate(116, PRI_INT_GATE, 0x08, (uint32_t)&int116);
    set_gate(117, PRI_INT_GATE, 0x08, (uint32_t)&int117);
    set_gate(118, PRI_INT_GATE, 0x08, (uint32_t)&int118);
    set_gate(119, PRI_INT_GATE, 0x08, (uint32_t)&int119);
    set_gate(120, PRI_INT_GATE, 0x08, (uint32_t)&int120);
    set_gate(121, PRI_INT_GATE, 0x08, (uint32_t)&int121);
    set_gate(122, PRI_INT_GATE, 0x08, (uint32_t)&int122);
    set_gate(123, PRI_INT_GATE, 0x08, (uint32_t)&int123);
    set_gate(124, PRI_INT_GATE, 0x08, (uint32_t)&int124);
    set_gate(125, PRI_INT_GATE, 0x08, (uint32_t)&int125);
    set_gate(126, PRI_INT_GATE, 0x08, (uint32_t)&int126);
    set_gate(127, PRI_INT_GATE, 0x08, (uint32_t)&int127);
    set_gate(128, PRI_INT_GATE, 0x08, (uint32_t)&int128);
    set_gate(129, PRI_INT_GATE, 0x08, (uint32_t)&int129);
    set_gate(130, PRI_INT_GATE, 0x08, (uint32_t)&int130);
    set_gate(131, PRI_INT_GATE, 0x08, (uint32_t)&int131);
    set_gate(132, PRI_INT_GATE, 0x08, (uint32_t)&int132);
    set_gate(133, PRI_INT_GATE, 0x08, (uint32_t)&int133);
    set_gate(134, PRI_INT_GATE, 0x08, (uint32_t)&int134);
    set_gate(135, PRI_INT_GATE, 0x08, (uint32_t)&int135);
    set_gate(136, PRI_INT_GATE, 0x08, (uint32_t)&int136);
    set_gate(137, PRI_INT_GATE, 0x08, (uint32_t)&int137);
    set_gate(138, PRI_INT_GATE, 0x08, (uint32_t)&int138);
    set_gate(139, PRI_INT_GATE, 0x08, (uint32_t)&int139);
    set_gate(140, PRI_INT_GATE, 0x08, (uint32_t)&int140);
    set_gate(141, PRI_INT_GATE, 0x08, (uint32_t)&int141);
    set_gate(142, PRI_INT_GATE, 0x08, (uint32_t)&int142);
    set_gate(143, PRI_INT_GATE, 0x08, (uint32_t)&int143);
    set_gate(144, PRI_INT_GATE, 0x08, (uint32_t)&int144);
    set_gate(145, PRI_INT_GATE, 0x08, (uint32_t)&int145);
    set_gate(146, PRI_INT_GATE, 0x08, (uint32_t)&int146);
    set_gate(147, PRI_INT_GATE, 0x08, (uint32_t)&int147);
    set_gate(148, PRI_INT_GATE, 0x08, (uint32_t)&int148);
    set_gate(149, PRI_INT_GATE, 0x08, (uint32_t)&int149);
    set_gate(150, PRI_INT_GATE, 0x08, (uint32_t)&int150);
    set_gate(151, PRI_INT_GATE, 0x08, (uint32_t)&int151);
    set_gate(152, PRI_INT_GATE, 0x08, (uint32_t)&int152);
    set_gate(153, PRI_INT_GATE, 0x08, (uint32_t)&int153);
    set_gate(154, PRI_INT_GATE, 0x08, (uint32_t)&int154);
    set_gate(155, PRI_INT_GATE, 0x08, (uint32_t)&int155);
    set_gate(156, PRI_INT_GATE, 0x08, (uint32_t)&int156);
    set_gate(157, PRI_INT_GATE, 0x08, (uint32_t)&int157);
    set_gate(158, PRI_INT_GATE, 0x08, (uint32_t)&int158);
    set_gate(159, PRI_INT_GATE, 0x08, (uint32_t)&int159);
    set_gate(160, PRI_INT_GATE, 0x08, (uint32_t)&int160);
    set_gate(161, PRI_INT_GATE, 0x08, (uint32_t)&int161);
    set_gate(162, PRI_INT_GATE, 0x08, (uint32_t)&int162);
    set_gate(163, PRI_INT_GATE, 0x08, (uint32_t)&int163);
    set_gate(164, PRI_INT_GATE, 0x08, (uint32_t)&int164);
    set_gate(165, PRI_INT_GATE, 0x08, (uint32_t)&int165);
    set_gate(166, PRI_INT_GATE, 0x08, (uint32_t)&int166);
    set_gate(167, PRI_INT_GATE, 0x08, (uint32_t)&int167);
    set_gate(168, PRI_INT_GATE, 0x08, (uint32_t)&int168);
    set_gate(169, PRI_INT_GATE, 0x08, (uint32_t)&int169);
    set_gate(170, PRI_INT_GATE, 0x08, (uint32_t)&int170);
    set_gate(171, PRI_INT_GATE, 0x08, (uint32_t)&int171);
    set_gate(172, PRI_INT_GATE, 0x08, (uint32_t)&int172);
    set_gate(173, PRI_INT_GATE, 0x08, (uint32_t)&int173);
    set_gate(174, PRI_INT_GATE, 0x08, (uint32_t)&int174);
    set_gate(175, PRI_INT_GATE, 0x08, (uint32_t)&int175);
    set_gate(176, PRI_INT_GATE, 0x08, (uint32_t)&int176);
    set_gate(177, PRI_INT_GATE, 0x08, (uint32_t)&int177);
    set_gate(178, PRI_INT_GATE, 0x08, (uint32_t)&int178);
    set_gate(179, PRI_INT_GATE, 0x08, (uint32_t)&int179);
    set_gate(180, PRI_INT_GATE, 0x08, (uint32_t)&int180);
    set_gate(181, PRI_INT_GATE, 0x08, (uint32_t)&int181);
    set_gate(182, PRI_INT_GATE, 0x08, (uint32_t)&int182);
    set_gate(183, PRI_INT_GATE, 0x08, (uint32_t)&int183);
    set_gate(184, PRI_INT_GATE, 0x08, (uint32_t)&int184);
    set_gate(185, PRI_INT_GATE, 0x08, (uint32_t)&int185);
    set_gate(186, PRI_INT_GATE, 0x08, (uint32_t)&int186);
    set_gate(187, PRI_INT_GATE, 0x08, (uint32_t)&int187);
    set_gate(188, PRI_INT_GATE, 0x08, (uint32_t)&int188);
    set_gate(189, PRI_INT_GATE, 0x08, (uint32_t)&int189);
    set_gate(190, PRI_INT_GATE, 0x08, (uint32_t)&int190);
    set_gate(191, PRI_INT_GATE, 0x08, (uint32_t)&int191);
    set_gate(192, PRI_INT_GATE, 0x08, (uint32_t)&int192);
    set_gate(193, PRI_INT_GATE, 0x08, (uint32_t)&int193);
    set_gate(194, PRI_INT_GATE, 0x08, (uint32_t)&int194);
    set_gate(195, PRI_INT_GATE, 0x08, (uint32_t)&int195);
    set_gate(196, PRI_INT_GATE, 0x08, (uint32_t)&int196);
    set_gate(197, PRI_INT_GATE, 0x08, (uint32_t)&int197);
    set_gate(198, PRI_INT_GATE, 0x08, (uint32_t)&int198);
    set_gate(199, PRI_INT_GATE, 0x08, (uint32_t)&int199);
    set_gate(200, PRI_INT_GATE, 0x08, (uint32_t)&int200);
    set_gate(201, PRI_INT_GATE, 0x08, (uint32_t)&int201);
    set_gate(202, PRI_INT_GATE, 0x08, (uint32_t)&int202);
    set_gate(203, PRI_INT_GATE, 0x08, (uint32_t)&int203);
    set_gate(204, PRI_INT_GATE, 0x08, (uint32_t)&int204);
    set_gate(205, PRI_INT_GATE, 0x08, (uint32_t)&int205);
    set_gate(206, PRI_INT_GATE, 0x08, (uint32_t)&int206);
    set_gate(207, PRI_INT_GATE, 0x08, (uint32_t)&int207);
    set_gate(208, PRI_INT_GATE, 0x08, (uint32_t)&int208);
    set_gate(209, PRI_INT_GATE, 0x08, (uint32_t)&int209);
    set_gate(210, PRI_INT_GATE, 0x08, (uint32_t)&int210);
    set_gate(211, PRI_INT_GATE, 0x08, (uint32_t)&int211);
    set_gate(212, PRI_INT_GATE, 0x08, (uint32_t)&int212);
    set_gate(213, PRI_INT_GATE, 0x08, (uint32_t)&int213);
    set_gate(214, PRI_INT_GATE, 0x08, (uint32_t)&int214);
    set_gate(215, PRI_INT_GATE, 0x08, (uint32_t)&int215);
    set_gate(216, PRI_INT_GATE, 0x08, (uint32_t)&int216);
    set_gate(217, PRI_INT_GATE, 0x08, (uint32_t)&int217);
    set_gate(218, PRI_INT_GATE, 0x08, (uint32_t)&int218);
    set_gate(219, PRI_INT_GATE, 0x08, (uint32_t)&int219);
    set_gate(220, PRI_INT_GATE, 0x08, (uint32_t)&int220);
    set_gate(221, PRI_INT_GATE, 0x08, (uint32_t)&int221);
    set_gate(222, PRI_INT_GATE, 0x08, (uint32_t)&int222);
    set_gate(223, PRI_INT_GATE, 0x08, (uint32_t)&int223);
    set_gate(224, PRI_INT_GATE, 0x08, (uint32_t)&int224);
    set_gate(225, PRI_INT_GATE, 0x08, (uint32_t)&int225);
    set_gate(226, PRI_INT_GATE, 0x08, (uint32_t)&int226);
    set_gate(227, PRI_INT_GATE, 0x08, (uint32_t)&int227);
    set_gate(228, PRI_INT_GATE, 0x08, (uint32_t)&int228);
    set_gate(229, PRI_INT_GATE, 0x08, (uint32_t)&int229);
    set_gate(230, PRI_INT_GATE, 0x08, (uint32_t)&int230);
    set_gate(231, PRI_INT_GATE, 0x08, (uint32_t)&int231);
    set_gate(232, PRI_INT_GATE, 0x08, (uint32_t)&int232);
    set_gate(233, PRI_INT_GATE, 0x08, (uint32_t)&int233);
    set_gate(234, PRI_INT_GATE, 0x08, (uint32_t)&int234);
    set_gate(235, PRI_INT_GATE, 0x08, (uint32_t)&int235);
    set_gate(236, PRI_INT_GATE, 0x08, (uint32_t)&int236);
    set_gate(237, PRI_INT_GATE, 0x08, (uint32_t)&int237);
    set_gate(238, PRI_INT_GATE, 0x08, (uint32_t)&int238);
    set_gate(239, PRI_INT_GATE, 0x08, (uint32_t)&int239);
    set_gate(240, PRI_INT_GATE, 0x08, (uint32_t)&int240);
    set_gate(241, PRI_INT_GATE, 0x08, (uint32_t)&int241);
    set_gate(242, PRI_INT_GATE, 0x08, (uint32_t)&int242);
    set_gate(243, PRI_INT_GATE, 0x08, (uint32_t)&int243);
    set_gate(244, PRI_INT_GATE, 0x08, (uint32_t)&int244);
    set_gate(245, PRI_INT_GATE, 0x08, (uint32_t)&int245);
    set_gate(246, PRI_INT_GATE, 0x08, (uint32_t)&int246);
    set_gate(247, PRI_INT_GATE, 0x08, (uint32_t)&int247);
    set_gate(248, PRI_INT_GATE, 0x08, (uint32_t)&int248);
    set_gate(249, PRI_INT_GATE, 0x08, (uint32_t)&int249);
    set_gate(250, PRI_INT_GATE, 0x08, (uint32_t)&int250);
    set_gate(251, PRI_INT_GATE, 0x08, (uint32_t)&int251);
    set_gate(252, PRI_INT_GATE, 0x08, (uint32_t)&int252);
    set_gate(253, PRI_INT_GATE, 0x08, (uint32_t)&int253);
    set_gate(254, PRI_INT_GATE, 0x08, (uint32_t)&int254);
    set_gate(255, PRI_INT_GATE, 0x08, (uint32_t)&int255);
    load_idt((uint32_t)&idtr);
}

// 根据不同的中断号，响应不同的例程
// 32-47为PIC中断
void int_error_handler(uint32_t code) {
    switch (code) {

    // 32-47为PIC的中断号响应，PIC中断需要重置操作
    // TODO: 32号为时钟中断，用来切换进程
    case 32:
        print_uint32(code);
        print_msg("\n");
    case 33:
        keyboard_handler();
    case 34:
    case 35:
    case 36:
    case 37:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 47:
        handler_reset(code);
        break;

    // 未响应的中断号，直接halt
    default:
        print_msg("Not handler int: ");
        print_uint32(code);
        panic(", halt!");
        break;
    }
}

void keyboard_handler() {
    outb(0x61, 0x20);
    uint8_t data = inb(0x60); // > 0x80 为释放按键
    if (data < 0x80) {
        keyboard_write((char)data);
    }
}

void to_ascii(char *data) {
    *data = normalmap[*data];
}

void keyboard_write(char data) {
    to_ascii(&data);
    switch (data) {
    case 8:
        --cur_ptr;
        if (cur_ptr < &keyboard_buff[0]) {
            cur_ptr = &keyboard_buff[0];
        } else {
            *cur_ptr = '\x00';
            backspace();
        }
        break;

    case '\n':
        start_process_flag = 1;
        push_char(data);
        break;
    default:
        *cur_ptr = data;
        push_char(data);
        ++cur_ptr;
        if (cur_ptr >= &keyboard_buff[0] + KEYBOARD_BUFF_SIZE) {
            cur_ptr = &keyboard_buff[0];
            print_msg("input cmd can't more than 256 bytes.\n");
        }
        break;
    }
}

void keyboard_flush() {
    do {
        *cur_ptr = '\x00';
        --cur_ptr;
    } while (cur_ptr != &keyboard_buff[0]);
    start_process_flag = 0;
}

void intx80_handler(uint8_t code) {
}

void open_keyboard() {
    _sti();
}

void close_keyboard() {
    _cli();
}

// TODO
int parse_option(char *name, int *args, char ***argv) {
    if (keyboard_buff[0] == '\x00') {
        return -1;
    }
    int space_count = 0;
    char *buff = &keyboard_buff[0];
    for (; *buff != '\n'; ++buff) {
        if (space_count == 0) {
            for (int i = 0; *buff != '\x20'; ++i) {
                name[i] = *buff;
                ++buff;
            }
            *buff = '\x00';
            ++space_count;
            *argv = buff + 1;
        } else {
            if (*buff == '\x20') {
                *buff = '\x00';
                ++space_count;
            }
        }
    }
    *buff = '\x00';
    *args = space_count;
    return 0;
}

void test_cmd() {
    while (1) {
        print_msg("/#");
        while (start_process_flag == 0) {
        }
        if (keyboard_buff[0] == '\x00' || keyboard_buff[0] == ' '
            || keyboard_buff[0] == '\n') {
            print_msg("input cmd is error.\n");
            start_process_flag = 0;
            continue;
        }
        close_keyboard();

        char *args1;
        int i = 0;
        for (; i < 128; ++i) {
            char ch = keyboard_buff[i];
            if (ch == '\n' || ch == ' ' || ch == ' ') {
                keyboard_buff[i] = '\x00';
                break;
            }
        }
        args1 = &keyboard_buff[++i];

        if (str_cmp(&keyboard_buff[0], "ls")) {
            ls_dir();
        } else if (str_cmp(&keyboard_buff[0], "cat")) {
            if (args1[0] == '\x00') {
                print_msg("args parse error!\n");
                goto exit;
            }
            cat(args1);
        } else if (str_cmp(&keyboard_buff[0], "clear")) {
            clear_screent();
        } else {
            print_msg("not found cmd!\n");
            goto exit;
        }

    exit:
        keyboard_flush();
        open_keyboard();
    }
}
