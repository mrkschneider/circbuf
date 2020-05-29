#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <circbuf.h>

static int circbuf_fill(circbuf* buf){
  CIRCBUF_ASSERT(buf,-1);
  if(buf->finished) return 0;

  uint pos = buf->read_pos;
  uint read_size = buf->read_size;
  char* bytes = buf->bytes;
  CIRCBUF_ASSERT(pos + read_size - 1 < buf->size,-1);
  uint n_read = fread(bytes+pos,(size_t)1,read_size,buf->fd);
  if(n_read < read_size) buf->finished = 1;
  buf->read_pos = pos + n_read;
  return n_read;
}

static int circbuf_rewind(circbuf* buf, uint start){
  CIRCBUF_ASSERT(buf,-1);
  if(buf->finished) return 0;

  uint size = buf->size;
  char* bytes = buf->bytes;
  uint pos = buf->pos;

  CIRCBUF_ASSERT(start <= pos,-1);
  CIRCBUF_ASSERT(start <= size,-1);
  
  for(uint i=start;i<size;i++){
    bytes[i-start] = bytes[i];
  }

  buf->pos = pos - start;
  buf->read_pos -= start;
  return 0;
}

circbuf* circbuf_create(char* bytes, uint size, uint read_size, FILE* fd){
  CIRCBUF_ASSERT(bytes,NULL);
  CIRCBUF_ASSERT(size > 2*read_size,NULL);
  CIRCBUF_ASSERT(fd,NULL);

  circbuf* c = malloc(sizeof(circbuf));
  CIRCBUF_ASSERT(c,NULL);
  
  c->bytes = bytes;
  c->pos = read_size;
  c->read_pos = read_size;
  c->size = size;
  c->read_size = read_size;
  c->fd = fd;
  c->finished = 0;
  int rc = circbuf_fill(c);
  CIRCBUF_ASSERT(rc >= 0, NULL);
  return c;
}

void circbuf_free(circbuf* buf){
  free(buf);
}

int circbuf_print(circbuf* c){
  CIRCBUF_ASSERT(c,-1);
  uint size = c->size;
  char* bytes = c->bytes;
  uint pos = c->pos;
  for(uint i=0;i<pos;i++){
    putchar(bytes[i]);
    putchar(' ');
  }
  putchar('.');
  putchar(' ');
  for(uint i=pos;i<size;i++){
    putchar(bytes[i]);
    putchar(' ');
  }
  putchar('\n');
  return 0;
}



char* circbuf_head_forward(circbuf* buf, uint n){
  CIRCBUF_ASSERT(buf,NULL);
  CIRCBUF_ASSERT(n <= buf->read_size,NULL);

  uint size = buf->size;
  uint rest = size - buf->read_pos;
  
  if(n > rest) {
    int rc = circbuf_rewind(buf,buf->pos + n - buf->read_size);
    CIRCBUF_ASSERT(rc >= 0,NULL);
  }

  uint pos = buf->pos;
  pos += n;
  CIRCBUF_ASSERT(pos < size,NULL);

  if(pos + buf->read_size - 1 >= buf->read_pos){
    int rc = circbuf_fill(buf); // Does not change buf->pos
    CIRCBUF_ASSERT(rc >= 0, NULL);
  }

  if(pos >= buf->read_pos){
    pos = buf->read_pos - 1;
  }

  buf->pos = pos;

  char* head = buf->bytes + pos;
  return head; 
}
