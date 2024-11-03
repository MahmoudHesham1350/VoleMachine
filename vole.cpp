#include <iostream>
#include <fstream>
#include <string>
#include "CU.cpp"

using namespace std;


class CPU {
private:
    int program_counter;
    Register cpu_register;
    Memory memory;
    CU computer_unit;

    int instruction_fetch_counter;

    string fetch() {
        instruction_fetch_counter++;
        Byte byte1 = memory.get_address(Byte(program_counter));
        program_counter++;
        Byte byte2 = memory.get_address(Byte(program_counter));
        program_counter++;

        return byte1.get_byte_as_string() + byte2.get_byte_as_string();
    }

    void split_Input(ifstream &input, int startCounter = 10) {
        string line;
        static int address_counter = startCounter;

        while(getline(input ,line)){

            if (line.length() == 4) {
                string byte1 = line.substr(0, 2); // First two characters
                string byte2 = line.substr(2, 2); // Last two characters

                Byte address_byte = Byte(address_counter);
                memory.set_address(address_byte, Byte(byte1));
                address_counter++;
                address_byte = Byte(address_counter);
                memory.set_address(address_byte, Byte(byte2));
                address_counter++;
            }

            else {
                throw invalid_argument("Invalid input");
            }
        }
    }


public:
    CPU(string file_name) {
        program_counter = 10;
        instruction_fetch_counter = 0;
        cpu_register = Register();
        memory = Memory();
        ifstream file(file_name);
        split_Input(file);
    }

    void test(){
        while (true) {
            string instruction = fetch();
            char opcode = instruction[0];
            Byte register_index("00");
            Byte memory_index("00");


            if (opcode == 'C') {
                cout << "Halting program" << endl;
            }
            else {
                //cout << endl << "Program step: " << instruction_fetch_counter << endl;
                //cout << endl << "Memory" << endl;
                //memory.print();
                //cout << endl << "Register" << endl;
                //cpu_register.print(2);
                //cout << endl;
            }


            switch (opcode) {
                case '1': {
                    string byte = "0" + string(1, instruction[1]);
                    register_index = Byte(byte);
                    memory_index = Byte(instruction.substr(2, 2));
                    computer_unit.load1(register_index, memory_index, cpu_register, memory);
                    break;
                }

                case '2': {
                    string byte = "0" + string(1, instruction[1]);
                    register_index = Byte(byte);
                    Byte value = (instruction.substr(2, 2));
                    computer_unit.load2(cpu_register, register_index, value);
                    break;
                }

                case '3': {
                    Byte decisive_pattern(instruction.substr(2, 2));
                    string byte = "0" + string(1, instruction[1]);

                    if (decisive_pattern.get_byte_as_int() == 0) {
                        cout << "Screen Output: ";
                        cpu_register.get_address(Byte(byte)).print();
                        cout << endl;
                        break;
                    }
                    else {
                        register_index = Byte(byte);
                        memory_index = Byte(instruction.substr(2, 2));
                        computer_unit.store(register_index, memory_index, cpu_register, memory);
                        break;
                    }
                }

                case '4': {
                    string byte_get = "0" + string(1, instruction[2]);
                    string byte_set = "0" + string(1, instruction[3]);
                    Byte register_index_get = Byte(byte_get);
                    Byte register_index_set(byte_set);
                    computer_unit.move(register_index_set, register_index_get, cpu_register);
                    break;
                }

                case '5': {
                    string byte_to_add = "0" + string(1, instruction[1]);
                    string byte1 = "0" + string(1, instruction[2]);
                    string byte2 = "0" + string(1, instruction[3]);
                    register_index = Byte(byte_to_add);
                    Byte register_index1 = Byte(byte1);
                    Byte register_index2 = Byte(byte2);
                    Byte value1 = cpu_register.get_address(register_index1);
                    Byte value2 = cpu_register.get_address(register_index2);
                    Byte result = value1 + value2;
                    cpu_register.set_address(register_index, result);
                    break;
                }

                case '6': {
                    string byte_to_add = "0" + string(1, instruction[1]);
                    string byte1 = "0" + string(1, instruction[2]);
                    string byte2 = "0" + string(1, instruction[3]);
                    register_index = Byte(byte_to_add);
                    Byte register_index1 = Byte(byte1);
                    Byte register_index2 = Byte(byte2);
                    //throw invalid_argument("add float not implemented");
                    break;
                }

                case 'B': {
                    string byte = "0" + string(1, instruction[1]);
                    register_index = Byte(byte);
                    string string_memory_index = instruction.substr(2, 2);
                    memory_index = Byte(string_memory_index);
                    computer_unit.jump(register_index, memory_index, cpu_register, program_counter);
                    break;
                }
                case 'C': {
                    computer_unit.halt();
                    break;
                }

                case '0' : {
                    break;
                }
                default:
                    throw invalid_argument("Invalid opcode");
            }

        }


    }
};







int main() {

    CPU cpu("input_test1.txt");
    cpu.test();

    return 0;

}