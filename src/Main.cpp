#include <iostream>
#include "filesystem"
#include <fstream>
#include <vector>
#include <string>
#include "opCodeInitilization.h"
#include <algorithm>

int main()
{
    namespace fs = std::filesystem;
    fs::path f{"rom/rom.h"};
    std::ifstream::pos_type size;
    
    
    //check if file exists
    if (fs::exists(f))
    {
        std::cout << "File exists" << std::endl;
        
        // Open Binary file
        std::ifstream input(f, std::ios::in | std::ios::binary | std::ios::ate);
        if (input.is_open())
        {
            size = input.tellg();
            std::vector<uint8_t> memblock(size);
            input.seekg(0, std::ios::beg);
            input.read(reinterpret_cast<char*>(memblock.data()), size);
            input.close();
            
            std::cout << "The complete file is in memory" << std::endl;
            
            
            
            for (int i = 0; i < size; ++i)
            {
                std::ofstream assemblyOutput;
                assemblyOutput.open("rom.asm", std::ios::app);
                
                std::stringstream counter;
                counter << std::hex << std::setfill('0') << std::setw(4) << i ;
                std::string counterString = counter.str();
                
                
                std::stringstream ss;
                ss << "0x" << std::hex << std::setfill('0') << std::setw(2) << (int)memblock.at(i);
                std::string hexString = ss.str();
                ss.str("");
                std::cout << hexString;
                int hexInt = std::stoi(hexString, nullptr, 16);
                std::cout << hexInt;
    
                int excessBytesUsed = 0;
                std::string opCode;
                std::string opCodeName;
                std::string prefix;
                bool goThroughByteChecker = false;
                
                switch (hexInt)
                {
                    case 0x00:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x01:
                        opCodeName = "LXI";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "B,#$";
                        break;
                    case 0x02:
                        opCodeName = "STAX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x03:
                        opCodeName = "INX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x04:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x05:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x06:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "B,#$";
                        break;
                    case 0x07:
                        opCodeName = "RLC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x08:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x09:
                        opCodeName = "DAD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x0a:
                        opCodeName = "LDAX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x0b:
                        opCodeName = "DCX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x0c:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0x0d:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0x0e:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "C,#$";
                        break;
                    case 0x0f:
                        opCodeName = "RRC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
    
    
                    case 0x10:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x11:
                        opCodeName = "LXI";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "D,#$";
                        break;
                    case 0x12:
                        opCodeName = "STAX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x13:
                        opCodeName = "INX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x14:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x15:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x16:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "D,#$";
                        break;
                    case 0x17:
                        opCodeName = "RAL";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x18:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x19:
                        opCodeName = "DAD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x1a:
                        opCodeName = "LDAX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x1b:
                        opCodeName = "DCX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x1c:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0x1d:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0x1e:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "E,#$";
                        break;
                    case 0x1f:
                        opCodeName = "RAR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = true;
                        prefix = "";
                        break;
    
    
                    case 0x20:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x21:
                        opCodeName = "LXI";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "H,#$";
                        break;
                    case 0x22:
                        opCodeName = "SHLD";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0x23:
                        opCodeName = "INX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x24:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x25:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x26:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "H,#$";
                        break;
                    case 0x27:
                        opCodeName = "DAA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x28:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x29:
                        opCodeName = "DAD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x2a:
                        opCodeName = "LHLD";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0x2b:
                        opCodeName = "DCX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x2c:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0x2d:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0x2e:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "L,#$";
                        break;
                    case 0x2f:
                        opCodeName = "CMA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
    
    
                    case 0x30:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x31:
                        opCodeName = "LXI";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "SP,#$";
                        break;
                    case 0x32:
                        opCodeName = "STA";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0x33:
                        opCodeName = "INX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "SP";
                        break;
                    case 0x34:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0x35:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0x36:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "M,#$";
                        break;
                    case 0x37:
                        opCodeName = "STC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x38:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x39:
                        opCodeName = "DAD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "SP";
                        break;
                    case 0x3a:
                        opCodeName = "LDA";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0x3b:
                        opCodeName = "DCX";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "SP";
                        break;
                    case 0x3c:
                        opCodeName = "INR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
                    case 0x3d:
                        opCodeName = "DCR";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
                    case 0x3e:
                        opCodeName = "MVI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "A,#$";
                        break;
                    case 0x3f:
                        opCodeName = "CMC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
    
                    case 0x40:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,B";
                        break;
                    case 0x41:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,C";
                        break;
                    case 0x42:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,D";
                        break;
                    case 0x43:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,E";
                        break;
                    case 0x44:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,H";
                        break;
                    case 0x45:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,L";
                        break;
                    case 0x46:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,M";
                        break;
                    case 0x47:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B,A";
                        break;
                    case 0x48:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,B";
                        break;
                    case 0x49:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,C";
                        break;
                    case 0x4a:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,D";
                        break;
                    case 0x4b:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,E";
                        break;
                    case 0x4c:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,H";
                        break;
                    case 0x4d:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,L";
                        break;
                    case 0x4e:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,M";
                        break;
                    case 0x4f:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C,A";
                        break;
    
                    case 0x50:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,B";
                        break;
                    case 0x51:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,C";
                        break;
                    case 0x52:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,D";
                        break;
                    case 0x53:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,E";
                        break;
                    case 0x54:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,H";
                        break;
                    case 0x55:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,L";
                        break;
                    case 0x56:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,M";
                        break;
                    case 0x57:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D,A";
                        break;
                    case 0x58:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,B";
                        break;
                    case 0x59:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,C";
                        break;
                    case 0x5a:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,D";
                        break;
                    case 0x5b:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,E";
                        break;
                    case 0x5c:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,H";
                        break;
                    case 0x5d:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,L";
                        break;
                    case 0x5e:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,M";
                        break;
                    case 0x5f:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E,A";
                        break;
    
                    case 0x60:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,B";
                        break;
                    case 0x61:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,C";
                        break;
                    case 0x62:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,D";
                        break;
                    case 0x63:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,E";
                        break;
                    case 0x64:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,H";
                        break;
                    case 0x65:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,L";
                        break;
                    case 0x66:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,M";
                        break;
                    case 0x67:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H,A";
                        break;
                    case 0x68:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,B";
                        break;
                    case 0x69:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,C";
                        break;
                    case 0x6a:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,D";
                        break;
                    case 0x6b:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,E";
                        break;
                    case 0x6c:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,H";
                        break;
                    case 0x6d:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,L";
                        break;
                    case 0x6e:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,M";
                        break;
                    case 0x6f:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L,A";
                        break;
    
                    case 0x70:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,B";
                        break;
                    case 0x71:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,C";
                        break;
                    case 0x72:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,D";
                        break;
                    case 0x73:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,E";
                        break;
                    case 0x74:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,H";
                        break;
                    case 0x75:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,L";
                        break;
                    case 0x76:
                        opCodeName = "HLT";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0x77:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M,A";
                        break;
                    case 0x78:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,B";
                        break;
                    case 0x79:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,C";
                        break;
                    case 0x7a:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,D";
                        break;
                    case 0x7b:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,E";
                        break;
                    case 0x7c:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,H";
                        break;
                    case 0x7d:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,L";
                        break;
                    case 0x7e:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,M";
                        break;
                    case 0x7f:
                        opCodeName = "MOV";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A,A";
                        break;
    
                    case 0x80:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x81:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0x82:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x83:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0x84:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x85:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0x86:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0x87:
                        opCodeName = "ADD";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
                    case 0x88:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x89:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0x8a:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x8b:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0x8c:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x8d:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0x8e:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0x8f:
                        opCodeName = "ADC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
    
                    case 0x90:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x91:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0x92:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x93:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0x94:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x95:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0x96:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0x97:
                        opCodeName = "SUB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
                    case 0x98:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0x99:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0x9a:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0x9b:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0x9c:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0x9d:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0x9e:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0x9f:
                        opCodeName = "SBB";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
    
                    case 0xa0:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0xa1:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0xa2:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0xa3:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0xa4:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0xa5:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0xa6:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0xa7:
                        opCodeName = "ANA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
                    case 0xa8:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0xa9:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0xaa:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0xab:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0xac:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0xad:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0xae:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0xaf:
                        opCodeName = "XRA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
    
                    case 0xb0:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0xb1:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0xb2:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0xb3:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0xb4:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0xb5:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0xb6:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0xb7:
                        opCodeName = "ORA";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
                    case 0xb8:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0xb9:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "C";
                        break;
                    case 0xba:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0xbb:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "E";
                        break;
                    case 0xbc:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0xbd:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "L";
                        break;
                    case 0xbe:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "M";
                        break;
                    case 0xbf:
                        opCodeName = "CMP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "A";
                        break;
    
                    case 0xc0:
                        opCodeName = "RNZ";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xc1:
                        opCodeName = "POP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0xc2:
                        opCodeName = "JNZ";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xc3:
                        opCodeName = "JMP";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xc4:
                        opCodeName = "CNZ";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xc5:
                        opCodeName = "PUSH";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "B";
                        break;
                    case 0xc6:
                        opCodeName = "ADI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xc7:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "0";
                        break;
                    case 0xc8:
                        opCodeName = "RZ";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xc9:
                        opCodeName = "RET";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xca:
                        opCodeName = "JZ";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xcb:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xcc:
                        opCodeName = "CZ";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xcd:
                        opCodeName = "CALL";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xce:
                        opCodeName = "ACI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xcf:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "1";
                        break;
    
                    case 0xd0:
                        opCodeName = "RNC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xd1:
                        opCodeName = "POP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0xd2:
                        opCodeName = "JNC";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xd3:
                        opCodeName = "OUT";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xd4:
                        opCodeName = "CNC";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xd5:
                        opCodeName = "PUSH";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "D";
                        break;
                    case 0xd6:
                        opCodeName = "SUI";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xd7:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "2";
                        break;
                    case 0xd8:
                        opCodeName = "RC";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xd9:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xda:
                        opCodeName = "JC";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xdb:
                        opCodeName = "IN";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xdc:
                        opCodeName = "CC";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xdd:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xde:
                        opCodeName = "SBI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xdf:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "3";
                        break;
    
                    case 0xe0:
                        opCodeName = "RPO";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xe1:
                        opCodeName = "POP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0xe2:
                        opCodeName = "JPO";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xe3:
                        opCodeName = "XHTL";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xe4:
                        opCodeName = "CPO";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xe5:
                        opCodeName = "PUSH";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "H";
                        break;
                    case 0xe6:
                        opCodeName = "ANI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xe7:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "4";
                        break;
                    case 0xe8:
                        opCodeName = "RPE";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xe9:
                        opCodeName = "PCHL";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xea:
                        opCodeName = "JPE";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xeb:
                        opCodeName = "XCHG";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xec:
                        opCodeName = "CPE";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xed:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xee:
                        opCodeName = "XRI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xef:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "5";
                        break;
    
                    case 0xf0:
                        opCodeName = "RP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xf1:
                        opCodeName = "POP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "PSW";
                        break;
                    case 0xf2:
                        opCodeName = "JP";
                        excessBytesUsed = 2;
                        goThroughByteChecker = false;
                        prefix = "$";
                        break;
                    case 0xf3:
                        opCodeName = "DI";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xf4:
                        opCodeName = "CP";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xf5:
                        opCodeName = "PUSH";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "PSW";
                        break;
                    case 0xf6:
                        opCodeName = "ORI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xf7:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "6";
                        break;
                    case 0xf8:
                        opCodeName = "RM";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xf9:
                        opCodeName = "SPHL";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xfa:
                        opCodeName = "JM";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xfb:
                        opCodeName = "EI";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xfc:
                        opCodeName = "CM";
                        excessBytesUsed = 2;
                        goThroughByteChecker = true;
                        prefix = "$";
                        break;
                    case 0xfd:
                        opCodeName = "NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
                    case 0xfe:
                        opCodeName = "CPI";
                        excessBytesUsed = 1;
                        goThroughByteChecker = true;
                        prefix = "#$";
                        break;
                    case 0xff:
                        opCodeName = "RST";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "7";
                        break;
                }
                
                std::string byteStreamToString;
                std::string sortedHex;
                std::stringstream hexSortedString;
                std::string hexResult;
                
                if (goThroughByteChecker)
                {
                    std::vector<std::string> excessBytesVector;
                    std::stringstream singleByte;
    
                    for (int byteTracker = i + 1; byteTracker <= i + excessBytesUsed; ++byteTracker)
                    {
                        singleByte << std::hex << std::setfill('0') << std::setw(2) << (int) memblock.at(byteTracker);
                        std::string bytesString = singleByte.str();
                        excessBytesVector.push_back(bytesString);
                        singleByte.str("");
                    }
    
                    std::stringstream bytesSS;
                    for (auto it = excessBytesVector.begin(); it != excessBytesVector.end(); ++it)
                    {
                        if (it != excessBytesVector.begin())
                        {
                            bytesSS << " ";
                        }
                        bytesSS << *it;
                    }
    
                    //std::copy(excessBytesVector.begin(), excessBytesVector.end(),std::ostream_iterator<std::string>(bytesSS));
                    byteStreamToString = bytesSS.str();
                    std::cout << byteStreamToString;
                    bytesSS.str("");
    
                    std::reverse(excessBytesVector.begin(), excessBytesVector.end());
    
                    std::stringstream hexStream;
                    for (auto it = excessBytesVector.begin(); it != excessBytesVector.end(); ++it)
                    {
                        if (it != excessBytesVector.begin())
                        {
                            hexStream << "";
                        }
                        hexStream << *it;
                    }
                    hexResult = hexStream.str();
                }
                std::string result = counterString + " " + opCodeName + "    " + prefix + hexResult;
                assemblyOutput << result << std::endl;
                assemblyOutput.close();
                i = i + excessBytesUsed;
            }
        }
    }
    else
    {
        std::cout << "File does not exist" << std::endl;
    }
    
    
    
    //prevents application from automatically closing and waiting for user-input. Debugging purposes.
    //std::cout << "Press any key to exit." << std::endl;
    std::cin.ignore();
    std::cin.get();
    return 0;
}
