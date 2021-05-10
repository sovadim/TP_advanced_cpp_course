#include <unistd.h>
#include <iostream>
#include "loglib/loglib.h"

int main(int argc, char* argv[]) {

    // TODO: getopt
    // --verbose - all logs
    // --quiet
    // --log-to-file <path>
    // --stderr
    // --help

    // tmp
    log::create_stdout_logger(log::DEBUG);

    // log::create_file_logger("filename", log::Level::DEBUG);
    // log::create_stdout_logger();

    log::debug("debug");
    log::info("info");
    log::warning("warning");
    log::error("error");

    std::string str("str");
    log::debug(str);
    log::info(str);
    log::warning(str);
    log::error(str);

    // TODO: implement some examples which write logs with all levels

    return 0;
}