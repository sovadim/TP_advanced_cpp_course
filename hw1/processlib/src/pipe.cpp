#include <unistd.h>
#include <stdexcept>
#include "pipe.h"

namespace process {

Pipe::Pipe() {
    if (-1 == ::pipe(fd_)) {
        fd_[0] = -1, fd_[1] = -1;
        throw std::runtime_error("Pipe failed");
    }
}

Pipe::~Pipe() noexcept {
    try {close();} catch(std::exception& e) {}
}

size_t Pipe::read(char* data, size_t len) const {
    ssize_t bytes = ::read(fd_[0], data, len);
    if (bytes < 0) throw std::runtime_error("Pipe failed - read error");
    return bytes;
}

size_t Pipe::write(const void* data, size_t len) const {
    ssize_t bytes = ::write(fd_[1], data, len);
    if (bytes < 0) throw std::runtime_error("Pipe failed - write error");
    return bytes;
}

void Pipe::dup_read_fd(int newfd) {
    if (-1 == ::dup2(fd_[0], newfd)) {
        fd_[0] = -1;
        throw std::runtime_error("Pipe failed - dup error");
    }
}

void Pipe::dup_write_fd(int newfd) {
    if (-1 == ::dup2(fd_[1], newfd)) {
        fd_[1] = -1;
        throw std::runtime_error("Pipe failed - dup error");
    }
}

void Pipe::close() {
    close_read(), close_write();
}

void Pipe::close_read() {
    if (fd_[0] != -1) {
        if (-1 == ::close(fd_[0])) {
            fd_[0] = -1;
            throw std::runtime_error("Pipe failed - read fd not closed");
        }
    }
}

void Pipe::close_write() {
    if (fd_[1] != -1) {
        if (-1 == ::close(fd_[1])) {
            fd_[1] = -1;
            throw std::runtime_error("Pipe failed - write fd not closed");
        }
    }
}

bool Pipe::is_closed() const {
    return (fd_[0] == -1 || fd_[1] == -1);
}

}  // namespace process
