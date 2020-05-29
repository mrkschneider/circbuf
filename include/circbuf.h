#include <stdio.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char byte;
typedef unsigned int uint;

typedef struct circbuf {
  char* bytes;
  uint pos;
  uint read_pos;
  uint read_size;
  uint size;
  FILE* fd;
  byte finished;
} circbuf;

circbuf* circbuf_create(char* bytes, uint size, uint read_size, FILE* fd);
void circbuf_free(circbuf* buf);

void circbuf_print(circbuf* c);
uint circbuf_fill(circbuf* buf);
void circbuf_rewind(circbuf* buf);
char* circbuf_head_forward(circbuf* buf, uint n);

#ifdef __cplusplus
}
#endif
