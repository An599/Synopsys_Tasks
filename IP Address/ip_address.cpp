#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <cstdlib>
#include <ctime>
#include <unordered_set>

typedef unsigned long long uint64_t;

std::string generateRandomIP() {
    return std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256) + "." +
        std::to_string(rand() % 256);
}

uint32_t ipToInt(const std::string& ip) {
    uint32_t result = 0;
    size_t start = 0;
    size_t end = ip.find('.');

    for (int shift = 24; shift >= 0; shift -= 8) {
        std::string octet = ip.substr(start, end - start);
        uint32_t octetValue = std::stoi(octet);
        result |= (octetValue << shift);
        start = end + 1;
        end = ip.find('.', start);
    }

    return result;
}

void del_item(const std::string& target, const std::string& fobj) {
    std::ifstream fobj_read(fobj);
    if (!fobj_read.is_open()) {
        std::cout << "Error while opening the file" << std::endl;
        exit(1);
    }

    std::string fileContent;
    std::string line;
    while (std::getline(fobj_read, line)) {
        if (line != target) {
            fileContent += line + "\n";
        }
    }
    fobj_read.close();

    std::ofstream fobj_write(fobj);
    if (!fobj_write.is_open()) {
        std::cout << "Error while opening the file" << std::endl;
        exit(1);
    }

    fobj_write << fileContent;
    fobj_write.close();
}

int main() {
    std::srand(std::time(0)); 

    int n;
    std::cout << "Enter the number of IPs to generate (1-10000): ";
    do {
        std::cin >> n;
    } while (n < 0 || n > 10000);

    std::ofstream fobj_write("ips.txt", std::ios::out);
    if (!fobj_write.is_open()) {
        std::cout << "File open error" << std::endl;
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fobj_write << generateRandomIP() << std::endl;
    }
    fobj_write.close();

    std::ifstream fobj_read("ips.txt", std::ios::in);
    if (!fobj_read.is_open()) {
        std::cout << "File open error" << std::endl;
        exit(1);
    }

    std::unordered_set<uint32_t> ips_existance_set; 
    std::string line;
    while (std::getline(fobj_read, line)) {
        uint32_t ipInt = ipToInt(line);
        if (ips_existance_set.find(ipInt) != ips_existance_set.end()) {
            del_item(line, "ips.txt");
        }
        else {
            ips_existance_set.insert(ipInt);
        }
    }

    fobj_read.close();
    return 0;
}
