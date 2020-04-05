#include <iostream>
#include <string>
#include <exception>
#include "process.h"
#include "pipe.h"

int main(int argc, char** argv) {
    process::Process *proc;

    try {
        proc = new process::Process("/bin/cat");
    } catch (const std::exception& e) {
        std::cerr << "Error in process initialisation" << std::endl;
        std::cerr << e.what() << std::endl;
        proc->terminate();
        return 1;
    }

    std::string buffer;

    try {
        while (std::getline(std::cin, buffer)) {
            std::string void_buffer;
            void_buffer.resize(buffer.size());
            size_t bytes;

            std::cout << "----------------" << std::endl;
            std::cout << "=== write / read ===" << std::endl;

            bytes = proc->write(buffer.c_str(), buffer.size());
            std::cout << "sent:" << std::endl;
            std::cout << "- data: " << buffer << std::endl;
            std::cout << "- bytes: " << bytes << std::endl;

            bytes = proc->read(&void_buffer[0], buffer.size());
            std::cout << "received:" << std::endl;
            std::cout << "- data: " << void_buffer << std::endl;
            std::cout << "- bytes: " << bytes << std::endl;

            std::cout << "\n=== writeExact / readExact ===" << std::endl;

            proc->writeExact(buffer.c_str(), buffer.size());
            std::cout << "sent:" << buffer << std::endl;

            proc->readExact(&void_buffer[0], buffer.size());
            std::cout << "received:" << void_buffer << std::endl;

            std::cout << "----------------" << std::endl;
        }
    } catch(std::exception& e) {
        std::cerr << e.what() <<std::endl;
    }

    std::cerr << "Eof received, stop" << std::endl;

    try { proc->close(); } catch(std::exception& e) {}
    proc->terminate();

    delete proc;

    return 0;
}