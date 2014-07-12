#include "parse.h"

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
  std::ofstream outfile (strcat(filename, ".csv"));

  char c;
  int char_count   = 0;
  int offset_count = 0;
  while (mainfile.get(c)) {
    outfile << c;
    if (c == '\n' || c == '\r') { offset_count = 0; char_count = 0; }
    else {
      char_count++;
      if (offset_count > breaks.size()) {
        std::cerr << "Line length too long.\n";
        return; 
      }

      if (char_count == breaks[offset_count]) {
        outfile << ",";
        char_count = 0;
        offset_count++;
      }
    }
  }
}

