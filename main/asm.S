.section .text
.global outb
.global inb
.global exit
.global load_idt
.extern int_error_handler
.global int0
.global int1
.global int2
.global int3
.global int4
.global int5
.global int6
.global int7
.global int8
.global int9
.global int10
.global int11
.global int12
.global int13
.global int14
.global int15
.global int16
.global int17
.global int18
.global int19
.global int20
.global int21
.global int22
.global int23
.global int24
.global int25
.global int26
.global int27
.global int28
.global int29
.global int30
.global int31
.global int32
.global int33
.global int34
.global int35
.global int36
.global int37
.global int38
.global int39
.global int40
.global int41
.global int42
.global int43
.global int44
.global int45
.global int46
.global int47
.global int48
.global int49
.global int50
.global int51
.global int52
.global int53
.global int54
.global int55
.global int56
.global int57
.global int58
.global int59
.global int60
.global int61
.global int62
.global int63
.global int64
.global int65
.global int66
.global int67
.global int68
.global int69
.global int70
.global int71
.global int72
.global int73
.global int74
.global int75
.global int76
.global int77
.global int78
.global int79
.global int80
.global int81
.global int82
.global int83
.global int84
.global int85
.global int86
.global int87
.global int88
.global int89
.global int90
.global int91
.global int92
.global int93
.global int94
.global int95
.global int96
.global int97
.global int98
.global int99
.global int100
.global int101
.global int102
.global int103
.global int104
.global int105
.global int106
.global int107
.global int108
.global int109
.global int110
.global int111
.global int112
.global int113
.global int114
.global int115
.global int116
.global int117
.global int118
.global int119
.global int120
.global int121
.global int122
.global int123
.global int124
.global int125
.global int126
.global int127
.global int128
.global int129
.global int130
.global int131
.global int132
.global int133
.global int134
.global int135
.global int136
.global int137
.global int138
.global int139
.global int140
.global int141
.global int142
.global int143
.global int144
.global int145
.global int146
.global int147
.global int148
.global int149
.global int150
.global int151
.global int152
.global int153
.global int154
.global int155
.global int156
.global int157
.global int158
.global int159
.global int160
.global int161
.global int162
.global int163
.global int164
.global int165
.global int166
.global int167
.global int168
.global int169
.global int170
.global int171
.global int172
.global int173
.global int174
.global int175
.global int176
.global int177
.global int178
.global int179
.global int180
.global int181
.global int182
.global int183
.global int184
.global int185
.global int186
.global int187
.global int188
.global int189
.global int190
.global int191
.global int192
.global int193
.global int194
.global int195
.global int196
.global int197
.global int198
.global int199
.global int200
.global int201
.global int202
.global int203
.global int204
.global int205
.global int206
.global int207
.global int208
.global int209
.global int210
.global int211
.global int212
.global int213
.global int214
.global int215
.global int216
.global int217
.global int218
.global int219
.global int220
.global int221
.global int222
.global int223
.global int224
.global int225
.global int226
.global int227
.global int228
.global int229
.global int230
.global int231
.global int232
.global int233
.global int234
.global int235
.global int236
.global int237
.global int238
.global int239
.global int240
.global int241
.global int242
.global int243
.global int244
.global int245
.global int246
.global int247
.global int248
.global int249
.global int250
.global int251
.global int252
.global int253
.global int254
.global int255
.global _cli
.global _sti
.global _read_sector
.global _write_sector
.global ata_read_one_sector
.global ata_write_one_sector

ata_read_one_sector:
    push %ebp
    mov %esp, %ebp
    pusha

    mov 12(%ebp), %ebx
    mov $0x1F2, %edx
    mov %cl, %al
    outb %al, %dx

    mov $0x1F3, %edx
    mov %ebx, %eax
    outb %al, %dx

    mov $0x1F4, %edx
    mov %ebx, %eax
    shr $8, %eax
    outb %al, %dx

    mov $0x1F5, %edx
    mov %ebx, %eax
    shr $16, %eax
    outb %al, %dx

    mov $0x1F7, %edx
    mov $0x20, %eax
    outb %al, %dx

going:
    inb %dx, %al
    test $8, %al
    jz going

    mov $256, %ecx
    mov 8(%ebp), %edi
    mov $0x1f0, %dx
    rep insw
    
    popa
    mov %ebp, %esp
    pop %ebp
    ret

ata_write_one_sector:
    push %ebp
    mov %esp, %ebp
    pusha

    mov 12(%ebp), %ebx
    mov $0x1F2, %edx
    mov %cl, %al
    outb %al, %dx

    mov $0x1F3, %edx
    mov %ebx, %eax
    outb %al, %dx

    mov $0x1F4, %edx
    mov %ebx, %eax
    shr $8, %eax
    outb %al, %dx

    mov $0x1F5, %edx
    mov %ebx, %eax
    shr $16, %eax
    outb %al, %dx

    mov $0x1F7, %edx
    mov $0x30, %eax
    outb %al, %dx

w_going:
    inb %dx, %al
    test $8, %al
    jz w_going

    mov $256, %ecx
    mov 8(%ebp), %edi
    mov $0x1f0, %dx
    mov %edi, %esi
    rep outsw            
    
    popa
    mov %ebp, %esp
    pop %ebp
    ret

// 从硬盘读取到内存
_read_sector:
    push %ebp
    mov %esp, %ebp
    
    pusha
    
    mov 12(%ebp), %eax
    mov $256, %ecx
    mul %ecx
    mov %eax, %ecx

    mov 8(%ebp), %edi
    mov $0x1f0, %dx
    rep insw
    
    popa
    
    mov %ebp, %esp
    pop %ebp
    ret

// 从内存写入到硬盘
_write_sector:
    push %ebp
    mov %esp, %ebp
    
    pusha
    
    mov 12(%ebp), %eax
    mov $256, %ecx
    mul %ecx
    mov %eax, %ecx

    mov 8(%ebp), %esi
    mov $0x1f0, %dx
    rep outsw
    
    popa
    
    mov %ebp, %esp
    pop %ebp
    ret

_cli:
    cli
    ret

_sti:
    sti
    ret

outb:
    push %ebp
    mov %esp, %ebp
    mov 8(%ebp), %dx
    mov 12(%ebp), %al
    out %al, %dx
    mov %ebp, %esp
    pop %ebp
    ret 

inb:
    push %ebp
    mov %esp, %ebp
    mov 8(%ebp), %dx
    in %dx, %al
    mov %ebp, %esp
    pop %ebp
    ret

exit:
    hlt
    jmp exit

load_idt:
    push %ebp
    mov %esp, %ebp
    mov 8(%ebp), %eax
    lidt (%eax)
    mov %ebp, %esp
    pop %ebp
    ret

// 8, 10-14 中断号会push Error code
// 有错误代码的情况下要pop error code
// 测试int 8，没有push error code
// 实测int 11, 也没有push error code
int_com_handler:
    call int_error_handler
    pop %eax
    popa
    sti
    iret

.extern intx80_handler
// int0x80做特殊处理
int128:
    cli
    pusha
    push $128
    jmp int_com_handler

// 中断vector向量函数
int0:
    cli
    pusha
    push $0
    jmp int_com_handler
        
int1:
    cli
    pusha
    push $1
    jmp int_com_handler
        
int2:
    cli
    pusha
    push $2
    jmp int_com_handler
        
int3:
    cli
    pusha
    push $3
    jmp int_com_handler
        
int4:
    cli
    pusha
    push $4
    jmp int_com_handler
        
int5:
    cli
    pusha
    push $5
    jmp int_com_handler
        
int6:
    cli
    pusha
    push $6
    jmp int_com_handler
        
int7:
    cli
    pusha
    push $7
    jmp int_com_handler
        
int8:
    cli
    pusha
    push $8
    jmp int_com_handler
        
int9:
    cli
    pusha
    push $9
    jmp int_com_handler
        
int10:
    cli
    pusha
    push $10
    jmp int_com_handler
        
int11:
    cli
    pusha
    push $11
    jmp int_com_handler
        
int12:
    cli
    pusha
    push $12
    jmp int_com_handler
        
int13:
    cli
    pusha
    push $13
    jmp int_com_handler
        
int14:
    cli
    pusha
    push $14
    jmp int_com_handler
        
int15:
    cli
    pusha
    push $15
    jmp int_com_handler
        
int16:
    cli
    pusha
    push $16
    jmp int_com_handler
        
int17:
    cli
    pusha
    push $17
    jmp int_com_handler
        
int18:
    cli
    pusha
    push $18
    jmp int_com_handler
        
int19:
    cli
    pusha
    push $19
    jmp int_com_handler
        
int20:
    cli
    pusha
    push $20
    jmp int_com_handler
        
int21:
    cli
    pusha
    push $21
    jmp int_com_handler
        
int22:
    cli
    pusha
    push $22
    jmp int_com_handler
        
int23:
    cli
    pusha
    push $23
    jmp int_com_handler
        
int24:
    cli
    pusha
    push $24
    jmp int_com_handler
        
int25:
    cli
    pusha
    push $25
    jmp int_com_handler
        
int26:
    cli
    pusha
    push $26
    jmp int_com_handler
        
int27:
    cli
    pusha
    push $27
    jmp int_com_handler
        
int28:
    cli
    pusha
    push $28
    jmp int_com_handler
        
int29:
    cli
    pusha
    push $29
    jmp int_com_handler
        
int30:
    cli
    pusha
    push $30
    jmp int_com_handler
        
int31:
    cli
    pusha
    push $31
    jmp int_com_handler
        
int32:
    cli
    pusha
    push $32
    jmp int_com_handler
        
int33:
    cli
    pusha
    push $33
    jmp int_com_handler
        
int34:
    cli
    pusha
    push $34
    jmp int_com_handler
        
int35:
    cli
    pusha
    push $35
    jmp int_com_handler
        
int36:
    cli
    pusha
    push $36
    jmp int_com_handler
        
int37:
    cli
    pusha
    push $37
    jmp int_com_handler
        
int38:
    cli
    pusha
    push $38
    jmp int_com_handler
        
int39:
    cli
    pusha
    push $39
    jmp int_com_handler
        
int40:
    cli
    pusha
    push $40
    jmp int_com_handler
        
int41:
    cli
    pusha
    push $41
    jmp int_com_handler
        
int42:
    cli
    pusha
    push $42
    jmp int_com_handler
        
int43:
    cli
    pusha
    push $43
    jmp int_com_handler
        
int44:
    cli
    pusha
    push $44
    jmp int_com_handler
        
int45:
    cli
    pusha
    push $45
    jmp int_com_handler
        
int46:
    cli
    pusha
    push $46
    jmp int_com_handler
        
int47:
    cli
    pusha
    push $47
    jmp int_com_handler
        
int48:
    cli
    pusha
    push $48
    jmp int_com_handler
        
int49:
    cli
    pusha
    push $49
    jmp int_com_handler
        
int50:
    cli
    pusha
    push $50
    jmp int_com_handler
        
int51:
    cli
    pusha
    push $51
    jmp int_com_handler
        
int52:
    cli
    pusha
    push $52
    jmp int_com_handler
        
int53:
    cli
    pusha
    push $53
    jmp int_com_handler
        
int54:
    cli
    pusha
    push $54
    jmp int_com_handler
        
int55:
    cli
    pusha
    push $55
    jmp int_com_handler
        
int56:
    cli
    pusha
    push $56
    jmp int_com_handler
        
int57:
    cli
    pusha
    push $57
    jmp int_com_handler
        
int58:
    cli
    pusha
    push $58
    jmp int_com_handler
        
int59:
    cli
    pusha
    push $59
    jmp int_com_handler
        
int60:
    cli
    pusha
    push $60
    jmp int_com_handler
        
int61:
    cli
    pusha
    push $61
    jmp int_com_handler
        
int62:
    cli
    pusha
    push $62
    jmp int_com_handler
        
int63:
    cli
    pusha
    push $63
    jmp int_com_handler
        
int64:
    cli
    pusha
    push $64
    jmp int_com_handler
        
int65:
    cli
    pusha
    push $65
    jmp int_com_handler
        
int66:
    cli
    pusha
    push $66
    jmp int_com_handler
        
int67:
    cli
    pusha
    push $67
    jmp int_com_handler
        
int68:
    cli
    pusha
    push $68
    jmp int_com_handler
        
int69:
    cli
    pusha
    push $69
    jmp int_com_handler
        
int70:
    cli
    pusha
    push $70
    jmp int_com_handler
        
int71:
    cli
    pusha
    push $71
    jmp int_com_handler
        
int72:
    cli
    pusha
    push $72
    jmp int_com_handler
        
int73:
    cli
    pusha
    push $73
    jmp int_com_handler
        
int74:
    cli
    pusha
    push $74
    jmp int_com_handler
        
int75:
    cli
    pusha
    push $75
    jmp int_com_handler
        
int76:
    cli
    pusha
    push $76
    jmp int_com_handler
        
int77:
    cli
    pusha
    push $77
    jmp int_com_handler
        
int78:
    cli
    pusha
    push $78
    jmp int_com_handler
        
int79:
    cli
    pusha
    push $79
    jmp int_com_handler
        
int80:
    cli
    pusha
    push $80
    jmp int_com_handler
        
int81:
    cli
    pusha
    push $81
    jmp int_com_handler
        
int82:
    cli
    pusha
    push $82
    jmp int_com_handler
        
int83:
    cli
    pusha
    push $83
    jmp int_com_handler
        
int84:
    cli
    pusha
    push $84
    jmp int_com_handler
        
int85:
    cli
    pusha
    push $85
    jmp int_com_handler
        
int86:
    cli
    pusha
    push $86
    jmp int_com_handler
        
int87:
    cli
    pusha
    push $87
    jmp int_com_handler
        
int88:
    cli
    pusha
    push $88
    jmp int_com_handler
        
int89:
    cli
    pusha
    push $89
    jmp int_com_handler
        
int90:
    cli
    pusha
    push $90
    jmp int_com_handler
        
int91:
    cli
    pusha
    push $91
    jmp int_com_handler
        
int92:
    cli
    pusha
    push $92
    jmp int_com_handler
        
int93:
    cli
    pusha
    push $93
    jmp int_com_handler
        
int94:
    cli
    pusha
    push $94
    jmp int_com_handler
        
int95:
    cli
    pusha
    push $95
    jmp int_com_handler
        
int96:
    cli
    pusha
    push $96
    jmp int_com_handler
        
int97:
    cli
    pusha
    push $97
    jmp int_com_handler
        
int98:
    cli
    pusha
    push $98
    jmp int_com_handler
        
int99:
    cli
    pusha
    push $99
    jmp int_com_handler
        
int100:
    cli
    pusha
    push $100
    jmp int_com_handler
        
int101:
    cli
    pusha
    push $101
    jmp int_com_handler
        
int102:
    cli
    pusha
    push $102
    jmp int_com_handler
        
int103:
    cli
    pusha
    push $103
    jmp int_com_handler
        
int104:
    cli
    pusha
    push $104
    jmp int_com_handler
        
int105:
    cli
    pusha
    push $105
    jmp int_com_handler
        
int106:
    cli
    pusha
    push $106
    jmp int_com_handler
        
int107:
    cli
    pusha
    push $107
    jmp int_com_handler
        
int108:
    cli
    pusha
    push $108
    jmp int_com_handler
        
int109:
    cli
    pusha
    push $109
    jmp int_com_handler
        
int110:
    cli
    pusha
    push $110
    jmp int_com_handler
        
int111:
    cli
    pusha
    push $111
    jmp int_com_handler
        
int112:
    cli
    pusha
    push $112
    jmp int_com_handler
        
int113:
    cli
    pusha
    push $113
    jmp int_com_handler
        
int114:
    cli
    pusha
    push $114
    jmp int_com_handler
        
int115:
    cli
    pusha
    push $115
    jmp int_com_handler
        
int116:
    cli
    pusha
    push $116
    jmp int_com_handler
        
int117:
    cli
    pusha
    push $117
    jmp int_com_handler
        
int118:
    cli
    pusha
    push $118
    jmp int_com_handler
        
int119:
    cli
    pusha
    push $119
    jmp int_com_handler
        
int120:
    cli
    pusha
    push $120
    jmp int_com_handler
        
int121:
    cli
    pusha
    push $121
    jmp int_com_handler
        
int122:
    cli
    pusha
    push $122
    jmp int_com_handler
        
int123:
    cli
    pusha
    push $123
    jmp int_com_handler
        
int124:
    cli
    pusha
    push $124
    jmp int_com_handler
        
int125:
    cli
    pusha
    push $125
    jmp int_com_handler
        
int126:
    cli
    pusha
    push $126
    jmp int_com_handler
        
int127:
    cli
    pusha
    push $127
    jmp int_com_handler
        
int129:
    cli
    pusha
    push $129
    jmp int_com_handler
        
int130:
    cli
    pusha
    push $130
    jmp int_com_handler
        
int131:
    cli
    pusha
    push $131
    jmp int_com_handler
        
int132:
    cli
    pusha
    push $132
    jmp int_com_handler
        
int133:
    cli
    pusha
    push $133
    jmp int_com_handler
        
int134:
    cli
    pusha
    push $134
    jmp int_com_handler
        
int135:
    cli
    pusha
    push $135
    jmp int_com_handler
        
int136:
    cli
    pusha
    push $136
    jmp int_com_handler
        
int137:
    cli
    pusha
    push $137
    jmp int_com_handler
        
int138:
    cli
    pusha
    push $138
    jmp int_com_handler
        
int139:
    cli
    pusha
    push $139
    jmp int_com_handler
        
int140:
    cli
    pusha
    push $140
    jmp int_com_handler
        
int141:
    cli
    pusha
    push $141
    jmp int_com_handler
        
int142:
    cli
    pusha
    push $142
    jmp int_com_handler
        
int143:
    cli
    pusha
    push $143
    jmp int_com_handler
        
int144:
    cli
    pusha
    push $144
    jmp int_com_handler
        
int145:
    cli
    pusha
    push $145
    jmp int_com_handler
        
int146:
    cli
    pusha
    push $146
    jmp int_com_handler
        
int147:
    cli
    pusha
    push $147
    jmp int_com_handler
        
int148:
    cli
    pusha
    push $148
    jmp int_com_handler
        
int149:
    cli
    pusha
    push $149
    jmp int_com_handler
        
int150:
    cli
    pusha
    push $150
    jmp int_com_handler
        
int151:
    cli
    pusha
    push $151
    jmp int_com_handler
        
int152:
    cli
    pusha
    push $152
    jmp int_com_handler
        
int153:
    cli
    pusha
    push $153
    jmp int_com_handler
        
int154:
    cli
    pusha
    push $154
    jmp int_com_handler
        
int155:
    cli
    pusha
    push $155
    jmp int_com_handler
        
int156:
    cli
    pusha
    push $156
    jmp int_com_handler
        
int157:
    cli
    pusha
    push $157
    jmp int_com_handler
        
int158:
    cli
    pusha
    push $158
    jmp int_com_handler
        
int159:
    cli
    pusha
    push $159
    jmp int_com_handler
        
int160:
    cli
    pusha
    push $160
    jmp int_com_handler
        
int161:
    cli
    pusha
    push $161
    jmp int_com_handler
        
int162:
    cli
    pusha
    push $162
    jmp int_com_handler
        
int163:
    cli
    pusha
    push $163
    jmp int_com_handler
        
int164:
    cli
    pusha
    push $164
    jmp int_com_handler
        
int165:
    cli
    pusha
    push $165
    jmp int_com_handler
        
int166:
    cli
    pusha
    push $166
    jmp int_com_handler
        
int167:
    cli
    pusha
    push $167
    jmp int_com_handler
        
int168:
    cli
    pusha
    push $168
    jmp int_com_handler
        
int169:
    cli
    pusha
    push $169
    jmp int_com_handler
        
int170:
    cli
    pusha
    push $170
    jmp int_com_handler
        
int171:
    cli
    pusha
    push $171
    jmp int_com_handler
        
int172:
    cli
    pusha
    push $172
    jmp int_com_handler
        
int173:
    cli
    pusha
    push $173
    jmp int_com_handler
        
int174:
    cli
    pusha
    push $174
    jmp int_com_handler
        
int175:
    cli
    pusha
    push $175
    jmp int_com_handler
        
int176:
    cli
    pusha
    push $176
    jmp int_com_handler
        
int177:
    cli
    pusha
    push $177
    jmp int_com_handler
        
int178:
    cli
    pusha
    push $178
    jmp int_com_handler
        
int179:
    cli
    pusha
    push $179
    jmp int_com_handler
        
int180:
    cli
    pusha
    push $180
    jmp int_com_handler
        
int181:
    cli
    pusha
    push $181
    jmp int_com_handler
        
int182:
    cli
    pusha
    push $182
    jmp int_com_handler
        
int183:
    cli
    pusha
    push $183
    jmp int_com_handler
        
int184:
    cli
    pusha
    push $184
    jmp int_com_handler
        
int185:
    cli
    pusha
    push $185
    jmp int_com_handler
        
int186:
    cli
    pusha
    push $186
    jmp int_com_handler
        
int187:
    cli
    pusha
    push $187
    jmp int_com_handler
        
int188:
    cli
    pusha
    push $188
    jmp int_com_handler
        
int189:
    cli
    pusha
    push $189
    jmp int_com_handler
        
int190:
    cli
    pusha
    push $190
    jmp int_com_handler
        
int191:
    cli
    pusha
    push $191
    jmp int_com_handler
        
int192:
    cli
    pusha
    push $192
    jmp int_com_handler
        
int193:
    cli
    pusha
    push $193
    jmp int_com_handler
        
int194:
    cli
    pusha
    push $194
    jmp int_com_handler
        
int195:
    cli
    pusha
    push $195
    jmp int_com_handler
        
int196:
    cli
    pusha
    push $196
    jmp int_com_handler
        
int197:
    cli
    pusha
    push $197
    jmp int_com_handler
        
int198:
    cli
    pusha
    push $198
    jmp int_com_handler
        
int199:
    cli
    pusha
    push $199
    jmp int_com_handler
        
int200:
    cli
    pusha
    push $200
    jmp int_com_handler
        
int201:
    cli
    pusha
    push $201
    jmp int_com_handler
        
int202:
    cli
    pusha
    push $202
    jmp int_com_handler
        
int203:
    cli
    pusha
    push $203
    jmp int_com_handler
        
int204:
    cli
    pusha
    push $204
    jmp int_com_handler
        
int205:
    cli
    pusha
    push $205
    jmp int_com_handler
        
int206:
    cli
    pusha
    push $206
    jmp int_com_handler
        
int207:
    cli
    pusha
    push $207
    jmp int_com_handler
        
int208:
    cli
    pusha
    push $208
    jmp int_com_handler
        
int209:
    cli
    pusha
    push $209
    jmp int_com_handler
        
int210:
    cli
    pusha
    push $210
    jmp int_com_handler
        
int211:
    cli
    pusha
    push $211
    jmp int_com_handler
        
int212:
    cli
    pusha
    push $212
    jmp int_com_handler
        
int213:
    cli
    pusha
    push $213
    jmp int_com_handler
        
int214:
    cli
    pusha
    push $214
    jmp int_com_handler
        
int215:
    cli
    pusha
    push $215
    jmp int_com_handler
        
int216:
    cli
    pusha
    push $216
    jmp int_com_handler
        
int217:
    cli
    pusha
    push $217
    jmp int_com_handler
        
int218:
    cli
    pusha
    push $218
    jmp int_com_handler
        
int219:
    cli
    pusha
    push $219
    jmp int_com_handler
        
int220:
    cli
    pusha
    push $220
    jmp int_com_handler
        
int221:
    cli
    pusha
    push $221
    jmp int_com_handler
        
int222:
    cli
    pusha
    push $222
    jmp int_com_handler
        
int223:
    cli
    pusha
    push $223
    jmp int_com_handler
        
int224:
    cli
    pusha
    push $224
    jmp int_com_handler
        
int225:
    cli
    pusha
    push $225
    jmp int_com_handler
        
int226:
    cli
    pusha
    push $226
    jmp int_com_handler
        
int227:
    cli
    pusha
    push $227
    jmp int_com_handler
        
int228:
    cli
    pusha
    push $228
    jmp int_com_handler
        
int229:
    cli
    pusha
    push $229
    jmp int_com_handler
        
int230:
    cli
    pusha
    push $230
    jmp int_com_handler
        
int231:
    cli
    pusha
    push $231
    jmp int_com_handler
        
int232:
    cli
    pusha
    push $232
    jmp int_com_handler
        
int233:
    cli
    pusha
    push $233
    jmp int_com_handler
        
int234:
    cli
    pusha
    push $234
    jmp int_com_handler
        
int235:
    cli
    pusha
    push $235
    jmp int_com_handler
        
int236:
    cli
    pusha
    push $236
    jmp int_com_handler
        
int237:
    cli
    pusha
    push $237
    jmp int_com_handler
        
int238:
    cli
    pusha
    push $238
    jmp int_com_handler
        
int239:
    cli
    pusha
    push $239
    jmp int_com_handler
        
int240:
    cli
    pusha
    push $240
    jmp int_com_handler
        
int241:
    cli
    pusha
    push $241
    jmp int_com_handler
        
int242:
    cli
    pusha
    push $242
    jmp int_com_handler
        
int243:
    cli
    pusha
    push $243
    jmp int_com_handler
        
int244:
    cli
    pusha
    push $244
    jmp int_com_handler
        
int245:
    cli
    pusha
    push $245
    jmp int_com_handler
        
int246:
    cli
    pusha
    push $246
    jmp int_com_handler
        
int247:
    cli
    pusha
    push $247
    jmp int_com_handler
        
int248:
    cli
    pusha
    push $248
    jmp int_com_handler
        
int249:
    cli
    pusha
    push $249
    jmp int_com_handler
        
int250:
    cli
    pusha
    push $250
    jmp int_com_handler
        
int251:
    cli
    pusha
    push $251
    jmp int_com_handler
        
int252:
    cli
    pusha
    push $252
    jmp int_com_handler
        
int253:
    cli
    pusha
    push $253
    jmp int_com_handler
        
int254:
    cli
    pusha
    push $254
    jmp int_com_handler
        
int255:
    cli
    pusha
    push $255
    jmp int_com_handler
        