#include "csv_iterator.h"
#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

int main(int argc, char** argv) {

  if (argc != 4) {
    std::cerr << "Invalid number of arguments. "
              << "Usage: deenaparser <flat_files_name> <record_subset_ids> <output_file_name>"
              << std::endl;
    return 1;
  }

  char *flat_file_name = argv[1];
  char *record_subset_ids = argv[2];
  char *output_file_name = argv[3];

  ifstream flat_file(flat_file_name);
  ifstream records_subset(record_subset_ids);
  ofstream output_file(output_file_name);

  string ff_buffer, record_buffer;
  bool first_record = true, mark_chain = false;
  getline(records_subset, record_buffer);

  while (getline(flat_file, ff_buffer)) {
    bool equal_substring = true;
    for (int i = 0; i < record_buffer.length(); i++) {
      if (record_buffer[i] != ff_buffer[i]) {
        equal_substring = false;
      }
    }

    if (mark_chain && !equal_substring) {
      if (!getline(records_subset, record_buffer)) {
        break; // Done with ID reading
      }
      mark_chain = false;

      equal_substring = true;
      for (int i = 0; i < record_buffer.length(); i++) {
        if (record_buffer[i] != ff_buffer[i]) {
          equal_substring = false;
        }
      }
    }

    if (equal_substring) {
      if (!first_record) { output_file << std::endl; }
      output_file << ff_buffer;
      first_record = false;
      mark_chain = true;
    }
  }

  output_file.close();
  
  return 0;
}

