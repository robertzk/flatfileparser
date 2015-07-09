#include "parse.h"
#include <cstring>
#include <cstdlib>

FlatFileBreaks parse_header(char* filename) {
  std::ifstream file(filename);
  FlatFileBreaks chunk_lengths;

  bool first = true;
  for (CSVIterator loop(file); loop != CSVIterator(); ++loop) {
    if (first) { first = false; continue; }
    int index;
    std::istringstream ((*loop)[4]) >> index;
    chunk_lengths.push_back(index);
  }
  file.close();

  return chunk_lengths;
}

void parse_flatfile(FlatFileBreaks breaks, char* filename) {
  std::ifstream mainfile(filename);
  std::ofstream outfile(strcat(filename, ".csv"));

  int chars_per_line = 0;
  for (FlatFileBreaks::iterator i = breaks.begin(); i != breaks.end(); i++)
    chars_per_line += *i;

  char c;
  int char_count   = 0;
  int offset_count = 0;
  int charsum = 0;
  while (mainfile.get(c)) {
    outfile << c;
    if (c == '\n' || c == '\r') {
      if (offset_count == 0) continue;
      if (offset_count != breaks.size()) {
        std::cerr << offset_count << "Line length too short.\n" << breaks.size();
        exit(1);
      }
      offset_count = char_count = charsum = 0;
    } else {
      char_count++; charsum++;
      if (offset_count >= breaks.size()) {
        std::cerr << offset_count << "Line length too long.\n" << breaks.size();
        exit(1);
      }

      if (char_count == breaks[offset_count]) {
        if (charsum != chars_per_line) outfile << ",";
        char_count = 0;
        offset_count++;
      }
    }
  }
}

