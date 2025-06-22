#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

class VirtualOS {
private:
    char M[100][4];  // Memory (100 words, 4 bytes each)
    char IR[4];      // Instruction Register
    char R[4];       // General Purpose Register
    int IC;          // Instruction Counter
    bool C;          // Toggle
    int SI;          // Service Interrupt

    std::ifstream input_file;
    std::ofstream output_file;

public:
    VirtualOS(const std::string& input_filename, const std::string& output_filename) {
        input_file.open(input_filename);
        output_file.open(output_filename);
        if (!input_file.is_open() || !output_file.is_open()) {
            throw std::runtime_error("Error opening input or output file");
        }
        init();
    }

    ~VirtualOS() {
        if (input_file.is_open()) input_file.close();
        if (output_file.is_open()) output_file.close();
    }

    void init() {
        memset(M, 0, sizeof(M));
        memset(IR, 0, sizeof(IR));
        memset(R, 0, sizeof(R));
        IC = 0;
        C = false;
        SI = 0;
    }

    void load() {
        std::string line;
        int address = 0;
        
        while (std::getline(input_file, line)) {
            if (line.substr(0, 4) == "$AMJ") {
                init();
            } else if (line.substr(0, 4) == "$DTA") {
                execute_user_program();
            } else if (line.substr(0, 4) == "$END") {
                break;  // End of job
            } else {
                // Load program into memory
                for (size_t i = 0; i < line.length(); i += 4) {
                    for (int j = 0; j < 4 && i + j < line.length(); ++j) {
                        M[address][j] = line[i + j];
                    }
                    ++address;
                }
            }
        }
    }

    void execute_user_program() {
        IC = 0;  // Reset Instruction Counter at the start of each program
        while (true) {
            // Fetch instruction
            for (int i = 0; i < 4; ++i) {
                IR[i] = M[IC][i];
            }

            // Print the fetched instruction
            std::cout << "Fetched instruction: " << IR[0] << IR[1] << IR[2] << IR[3] << " at IC: " << IC << std::endl;
            IC++;  // Increment Instruction Counter

            // Execute based on instruction
            if (IR[0] == 'G' && IR[1] == 'D') {
                SI = 1;
                MOS();
            } else if (IR[0] == 'P' && IR[1] == 'D') {
                SI = 2;
                MOS();
            } else if (IR[0] == 'H') {
                std::cout << "Halting program" << std::endl;
                SI = 3;
                MOS();
                break;
            } else if (IR[0] == 'L' && IR[1] == 'R') {
                int address = (IR[2] - '0') * 10 + (IR[3] - '0');
                memcpy(R, M[address], 4);
                std::cout << "Loaded into R from address " << address << ": ";
                for (int i = 0; i < 4; ++i) std::cout << R[i];
                std::cout << std::endl;
            } else if (IR[0] == 'S' && IR[1] == 'R') {
                int address = (IR[2] - '0') * 10 + (IR[3] - '0');
                memcpy(M[address], R, 4);
            } else if (IR[0] == 'C' && IR[1] == 'R') {
                int address = (IR[2] - '0') * 10 + (IR[3] - '0');
                C = (memcmp(R, M[address], 4) == 0);
                std::cout << "Comparing R with address " << address << ": ";
                for (int i = 0; i < 4; ++i) std::cout << M[address][i];
                std::cout << " Result: " << (C ? "True" : "False") << std::endl;
            } else if (IR[0] == 'B' && IR[1] == 'T') {
                if (C) {
                    IC = (IR[2] - '0') * 10 + (IR[3] - '0');
                    std::cout << "Branching to: " << IC << std::endl;
                } else {
                    std::cout << "Not branching, C is false" << std::endl;
                }
            }

            std::cout << "Next IC: " << IC << std::endl << std::endl;

            // Check for end of memory program
            if (IC >= 100) break;  // Prevent out of bounds access
        }
    }

    void MOS() {
        switch (SI) {
            case 1: read(); break;
            case 2: write(); break;
            case 3: terminate(); break;
        }
    }

    void read() {
        std::string line;
        if (std::getline(input_file, line)) {
            int address = (IR[2] - '0') * 10 + (IR[3] - '0');
            for (size_t i = 0; i < line.length() && i < 40; ++i) {
                M[address + i / 4][i % 4] = line[i];
            }
            std::cout << "Read into memory at address " << address << ": " << line << std::endl;
            // Debug: Print the actual memory contents
            std::cout << "Memory contents: ";
            for (int i = 0; i < 10; ++i) {
                for (int j = 0; j < 4; ++j) {
                    std::cout << M[address + i][j];
                }
            }
            std::cout << std::endl;
        }
    }

    void write() {
        int address = (IR[2] - '0') * 10 + (IR[3] - '0');
        std::string output;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (M[address + i][j] != 0) {
                    output += M[address + i][j];
                }
            }
        }
        output_file << output << std::endl;
        std::cout << "Wrote to output: " << output << std::endl;
    }

    void terminate() {
        output_file << std::endl << std::endl;
    }

    void display_memory() {
        for (int i = 0; i < 100; ++i) {
            std::cout << i << ": ";
            for (int j = 0; j < 4; ++j) {
                std::cout << M[i][j];
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    try {
        VirtualOS os("/home/admin-/Desktop/c++/OS phase 1/input.txt", "/home/admin-/Desktop/c++/OS phase 1/output.txt");
        os.load();
        os.display_memory();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
