#include "csv_iterator.h"
#include "parse.h"

int main(int argc, char** argv) {

  if (argc != 3) {
    std::cerr << "Invalid number of arguments. "
              << "Usage: flatfileparser <header_file_name> <flat_file_name>"
              << std::endl;
    return 1;
  }

  parse_flatfile(parse_header(argv[1]), argv[2]);

  return 0;
}

