#ifndef PARSE_H
#define PARSE_H

#include "csv_iterator.h"

typedef std::vector<int> FlatFileBreaks;

FlatFileBreaks parse_header(char* file);
void parse_flatfile(FlatFileBreaks breaks, char* filename);

#endif

