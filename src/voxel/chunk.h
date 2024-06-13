#ifndef CHUNK_H
#define CHUNK_H

typedef struct block Block;

static const int CHUNKSIZE = 16;

typedef struct chunk {
  Block ***blocks;
  int chunkSize;
} Chunk;

Chunk *CreateChunk();
void DestroyChunk(Chunk *);

#endif
