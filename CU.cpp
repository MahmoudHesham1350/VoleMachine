#include "CU.h"
#include "Data.h"

void CU::load1(Byte register_index, Byte memory_index, Register& cpu_register, Memory& memory) {
    Byte value = memory.get_address(memory_index);
    cpu_register.set_address(register_index, value);
}

void CU::load2(Register& cpu_register, Byte register_index, Byte value) {
    cpu_register.set_address(register_index, value);
}

void CU::store(Byte register_index, Byte memory_index, Register& cpu_register, Memory& memory) {
    Byte value = cpu_register.get_address(register_index);
    memory.set_address(memory_index, value);
}

void CU::move(Byte register_index_set, Byte register_index_get, Register& cpu_register) {
    Byte value = cpu_register.get_address(register_index_get);
    cpu_register.set_address(register_index_set, value);
}

void CU::jump(Byte register_index, Byte memory_index, Register& cpu_register, int& program_counter) {
    Byte byte_zero = cpu_register.get_address(Byte("00"));
    Byte jump_byte = cpu_register.get_address(register_index);

    if (jump_byte == byte_zero) {
        program_counter = memory_index.get_byte_as_int();
    }
}

void CU::printOutput(Byte output) {
    cout << "Screen Output: " << endl;
    cout << "hex: ";
    output.print();
    cout << endl << "ASCII: ";

    int ascii_value = output.get_byte_as_int();

    if (ascii_value < 32 || ascii_value == 127) {
        cout << "A control Character: " << ascii_value << endl;
    } else {
        cout << static_cast<char>(ascii_value) << endl;
    }
}

void CU::halt() {
    exit(0);
}