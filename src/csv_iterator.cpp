#include "csv_iterator.h"

void CSVRow::readNextRow(std::istream& str) {
  std::string         line;
  std::getline(str,line);

  std::stringstream   lineStream(line);
  std::string         cell;

  m_data.clear();
  while(std::getline(lineStream,cell,','))
  {
      m_data.push_back(cell);
  }
}

std::istream& operator>>(std::istream& str, CSVRow& data) {
    data.readNextRow(str);
    return str;
}   

