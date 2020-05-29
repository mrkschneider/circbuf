#include <stdio.h>
#include <stdlib.h>
#include <circbuf.h>

circbuf* circbuf_create(char* bytes, uint size, uint read_size, FILE* fd){
  circbuf* c = malloc(sizeof(circbuf));
  c->bytes = bytes;
  c->pos = read_size;
  c->read_pos = read_size;
  c->size = size;
  c->read_size = read_size;
  c->fd = fd;
  c->finished = 0;
  return c;
}

void circbuf_free(circbuf* buf){
  free(buf);
}

void circbuf_print(circbuf* c){
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
}


uint circbuf_fill(circbuf* buf){
  uint pos = buf->read_pos;
  uint read_size = buf->read_size;
  char* bytes = buf->bytes;
  if(read_size > buf->size - pos){
    printf("ERROR: Not enough space to read %d characters\n",read_size);
    return 0;
  }
  uint n_read = fread(bytes+pos,(size_t)1,read_size,buf->fd);
  if(n_read < read_size) buf->finished = 1;
  buf->read_pos = pos + read_size;
  return n_read;
}

void circbuf_rewind(circbuf* buf){
  uint size = buf->size;
  uint pos = buf->pos;
  char* bytes = buf->bytes;
  uint read_size = buf->read_size;
  int start = pos - read_size;
  if(start < 0){
    printf("ERROR: Could not rewind buffer\n");
  }
  for(uint i=start;i<size;i++){
    bytes[i-start] = bytes[i];
  }
  buf->pos = read_size;
  buf->read_pos -= start;
}

char* circbuf_head_forward(circbuf* buf, uint n){
  buf->pos += n;
  uint size = buf->size;
  uint rest = size - buf->read_pos;

  if(n > rest) {
    circbuf_rewind(buf);
  }

  if(buf->pos + buf->read_size - 1 >= buf->read_pos){
    circbuf_fill(buf);
  }
  char* head = buf->bytes + buf->pos;
  return head; 
}
