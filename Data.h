#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

class Byte{
private :
    string value;
public:

    Byte(string byte) {
        if (byte.size() != 2) {
            throw invalid_argument("Byte must be of size 2");
        }
        else {
            this->value = byte;
        }
    }

    Byte(int byte) {
        if (byte < 0 || byte > 255) {
            throw invalid_argument("Byte must be between 0 and 255");
        }
        else {
            stringstream ss;
            ss << hex << setw(2) << setfill('0') << byte;
            string hex = ss.str();
            this->value = hex;
        }
    }

    string get_binary_value() {
        int byte_int = get_byte_as_int();
        string binary = bitset<8>(byte_int).to_string();
        return binary;
    }


    string get_byte_as_string() {
        return value;
    }

    int get_byte_as_int() {
        return stoi(get_byte_as_string(), nullptr, 16);
    }

    void print() {
        cout << get_byte_as_string() << " ";
    }

    bool operator==(const Byte& other) {
        return this->value == other.value;
    }

    Byte operator+(Byte& other) {
        int sum = this->get_byte_as_int() + other.get_byte_as_int();
        if (sum > 255) {
            sum -= 256; // Correctly handle overflow for binary complement addition
        }
        return Byte(sum);
    }

};

class Storage {
private:
    int number_bytes;
    vector<Byte> values;

public:
    Storage(int number_bytes) {
        this->number_bytes = number_bytes;
        Byte zero_byte("00");
        values = vector<Byte>(number_bytes, zero_byte);
    }

    void set_address(Byte address, Byte value) {
        int address_int = address.get_byte_as_int();
        values[address_int] = value;
    }

    Byte get_address(Byte address) {
        int address_int = address.get_byte_as_int();
        return values[address_int];
    }

    void print(int row_width = 16) {
        for (int index = 0; index < number_bytes; index++) {
            values[index].print();
            if((index+1) % row_width == 0) {
                cout << endl;
            }
        }
    }


};


class Memory : public Storage {
public:
    Memory() : Storage(256) {
    }
};


class Register : public Storage {
public:
    Register() : Storage(16) {
    }
};
