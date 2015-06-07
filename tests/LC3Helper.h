#pragma once
#define SETDR(x) (((x) & 0x7) << 9)
#define SETSR1(x) (((x) & 0x7) << 6)
#define SETBASER(x) (((x) & 0x7) << 6)
#define SETSR2(x) (((x) & 0x7) << 0)

#define SETN(x) (((x) & 0x1) << 11)
#define SETZ(x) (((x) & 0x1) << 10)
#define SETP(x) (((x) & 0x1) << 9)
#define STEERINGNORM 1<<5

#define ADDR 0x1000
#define ADDI ADDR | STEERINGNORM
#define ANDR 0x5000
#define ANDI ANDR | STEERINGNORM
#define BR   0x0000
#define JMP  0xC000
#define JSR  0x4800
#define JSRR 0x4000
#define LD   0x2000
#define LDI  0xA000
#define LDR  0x6000
#define LEA  0xE000
#define NOT  0x903F
#define RET  0xC000
#define RTI  0x8000
#define ST   0x3000
#define STI  0xB000
#define STR  0x7000
#define TRAP 0xF000
#define RESERVEDINST 0xD000