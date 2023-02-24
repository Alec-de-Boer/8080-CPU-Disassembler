#include <iostream>
#include "filesystem"
#include <fstream>
#include <vector>
#include <string>
#include "opCodeInitilization.h"

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
                        opCode = "00";
                        opCodeName = "           NOP";
                        excessBytesUsed = 0;
                        goThroughByteChecker = false;
                        prefix = "";
                        break;
        
                    case 0x01:
                        opCode = "01";
                        opCodeName = "LXI";
                        excessBytesUsed = 4;
                        goThroughByteChecker = true;
                        prefix = "A,#0x";
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
                    
                    for(int byteTracker = i + 1; byteTracker <= i + excessBytesUsed; ++byteTracker)
                    {
                        singleByte << std::hex << std::setfill('0') << std::setw(2) << (int)memblock.at(byteTracker);
                        std::string bytesString = singleByte.str();
                        excessBytesVector.push_back(bytesString);
                        singleByte.str("");
                    }
                    
                    std::stringstream bytesSS;
                    for (auto it = excessBytesVector.begin(); it!=excessBytesVector.end(); ++it)
                    {
                        if (it != excessBytesVector.begin())
                        {
                            bytesSS<<" ";
                        }
                        bytesSS << *it;
                    }
                    
                    //std::copy(excessBytesVector.begin(), excessBytesVector.end(),std::ostream_iterator<std::string>(bytesSS));
                    byteStreamToString = bytesSS.str();
                    std::cout << byteStreamToString;
                    bytesSS.str("");
                    
                    
                    //vector to temporarily store ints
                    std::vector<int> tempIntStorage;
                    
                    //vector to store the eventual sorted hex numbers
                    std::vector<std::string> hexSortedVector;
                    
                    for (int x = 0; x < excessBytesVector.size(); ++x)
                    {
                        int tempSingleByte;
                        std::ostringstream excessByteSorted;
                        excessByteSorted << excessBytesVector.at(x);
                        std::string excessStringSorted = excessByteSorted.str();
                        //convert items in array to int
                        tempSingleByte = std::stoi(excessBytesVector.at(x), 0, 16);
                        tempIntStorage.push_back(tempSingleByte);
                    }
                    
                    //sort items in ascending order
                    std::sort(tempIntStorage.begin(), tempIntStorage.end());
                    
                    //convert items back to hex
                    for (int y = 0; y < tempIntStorage.size(); ++y)
                    {
                       std::ostringstream hexSortedStream;
                       hexSortedStream << std::hex << std::setfill('0') << std::setw(2) << tempIntStorage.at(y);
                       std::string tempHex = hexSortedStream.str();
                       hexSortedVector.push_back(tempHex);
                    }
                    
                    std::stringstream hexSortedFinal;
                    //loop through vector, adding spaces and converting to string.
                    for (auto it = hexSortedVector.begin(); it!=hexSortedVector.end(); ++it)
                    {
                        if (it != hexSortedVector.begin())
                        {
                            hexSortedFinal<<" ";
                        }
                        hexSortedFinal << *it;
                    }
                    hexResult = hexSortedFinal.str();
                }
                
                std::string result = counterString + " " + opCode + " " + byteStreamToString + " " + opCodeName + "    " + prefix + hexResult;
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
