#ifndef CSVLOADER_H
#define CSVLOADER_H

#include <string>
#include "RBTree.h"
#include "hashTable.h"

void loadBooks(const std::string& filename, RBTree& tree);

#endif
