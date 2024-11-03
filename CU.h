#ifndef TASK3_CU_H
#define TASK3_CU_H
class Byte;
class Register;
class Memory;

class CU {
public:
    void load1(Byte register_index, Byte memory_index, Register& cpu_register, Memory& memory);
    void load2(Register& cpu_register, Byte register_index, Byte value);
    void store(Byte register_index, Byte memory_index, Register& cpu_register, Memory& memory);
    void move(Byte register_index_set, Byte register_index_get, Register& cpu_register);
    void jump(Byte register_index, Byte memory_index, Register& cpu_register, int& program_counter);
    void halt();
};


#endif //TASK3_CU_H
