#include "chunk.h"
#include "block.h"
#include "stdlib.h"

Chunk *CreateChunk() {
  Chunk *chunk = (Chunk *)malloc(sizeof(Chunk));
  chunk->blocks = NULL;
  chunk->chunkSize = CHUNKSIZE;

  chunk->blocks = (Block ***)malloc(sizeof(Block **) * CHUNKSIZE);
  Block ***xb = chunk->blocks;
  for (int plane_id = 0; plane_id < CHUNKSIZE; plane_id += 1) {
    Block **plane = (Block **)malloc(sizeof(Block *) * CHUNKSIZE);
    *(xb + plane_id) = plane;
    for (int row_id = 0; row_id < CHUNKSIZE; row_id += 1) {
      Block *row = (Block *)malloc(sizeof(Block) * CHUNKSIZE);
      *(plane + row_id) = row;
      for (int block_id = 0; block_id < CHUNKSIZE; block_id += 1) {
        (row + block_id)->isActive = 1;
      }
    }
  }

  return chunk;
}
void DestroyChunk(Chunk *chunk) {
  Block ***xb = chunk->blocks;
  for (int plane_id = 0; plane_id < CHUNKSIZE; plane_id += 1) {
    Block **plane = *(xb + plane_id);
    for (int row_id = 0; row_id < CHUNKSIZE; row_id += 1) {
      Block *row = *(plane + row_id);
      free(row);
    }
    free(plane);
  }
  free(xb);
  free(chunk);
}
