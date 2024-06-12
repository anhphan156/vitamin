#ifndef BLOCK_H
#define BLOCK_H

#define BL_DEFAULT 0
#define BL_GRASS 1
#define BL_DIRT 2
#define BL_WATER 3
#define BL_STONE 4
#define BL_WOOD 5
#define BL_SAND 6

typedef struct block {
  int isActive;
  int type;
} Block;

#endif
