#ifndef SCC_PARTITION_H_INCLUDED
#define SCC_PARTITION_H_INCLUDED

#include "graph.h"

#define MIN(x,y) ((x) <= (y)) ? (x) : (y)

int scc_partition(graph* g, int* parts);

int tarjan_scc(graph* g, int* components);

#endif // SCC_PARTITION_H_INCLUDED