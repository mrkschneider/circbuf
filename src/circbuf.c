#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <circbuf.h>

static int circbuf_fill(circbuf* buf){
  CIRCBUF_CHECK(buf,-1);

  size_t pos = buf->read_pos;
  size_t read_size = buf->read_size;
  char* bytes = buf->bytes;

  CIRCBUF_CHECK(pos + read_size - 1 < buf->size,-1);
  size_t n_read = fread(bytes+pos,(size_t)1,read_size,buf->fd);
  if(n_read < read_size) {
    buf->finished = 1;
    memset(bytes + pos + n_read,'\0',read_size - n_read);
  }
  buf->read_pos = pos + read_size;
  return n_read;
}

static int circbuf_rewind(circbuf* buf, size_t start){
  CIRCBUF_CHECK(buf,-1);

  size_t size = buf->size;
  char* bytes = buf->bytes;
  size_t pos = buf->pos;

  CIRCBUF_CHECK(start <= pos,-1);
  CIRCBUF_CHECK(start <= size,-1);
  
  for(size_t i=start;i<size;i++){
    bytes[i-start] = bytes[i];
  }

  buf->pos = pos - start;
  buf->read_pos -= start;
  return 0;
}

circbuf* circbuf_create(char* bytes, size_t size, size_t read_size, FILE* fd){
  CIRCBUF_CHECK(bytes,NULL);
  CIRCBUF_CHECK(size >= 4*read_size,NULL);
  CIRCBUF_CHECK(fd,NULL);

  circbuf* c = malloc(sizeof(circbuf)); 
  CIRCBUF_CHECK(c,NULL);
  
  c->bytes = bytes;
  c->pos = read_size;
  c->read_pos = read_size;
  c->size = size;
  c->read_size = read_size;
  c->fd = fd;
  c->finished = 0;
  int rc = circbuf_fill(c);
  CIRCBUF_CHECK(rc >= 0, NULL);
  return c;
}

void circbuf_free(circbuf* buf){
  free(buf);
}

int circbuf_print(circbuf* c){
  CIRCBUF_CHECK(c,-1);
  size_t size = c->size;
  char* bytes = c->bytes;
  size_t pos = c->pos;
  for(size_t i=0;i<pos;i++){
    putchar(bytes[i]);
    putchar(' ');
  }
  putchar('.');
  putchar(' ');
  for(size_t i=pos;i<size;i++){
    putchar(bytes[i]);
    putchar(' ');
  }
  putchar('\n');
  return 0;
}

char* circbuf_head(circbuf* buf){
  CIRCBUF_CHECK(buf,NULL);
  return buf->bytes + buf->pos;
}

char* circbuf_head_forward(circbuf* buf, size_t n){
  CIRCBUF_CHECK(buf,NULL);
  CIRCBUF_CHECK(n <= buf->read_size,NULL);

  size_t size = buf->size;
  size_t rest = size - buf->read_pos;
  
  if(rest < buf->read_size) {
    int rc = circbuf_rewind(buf,buf->pos + n - buf->read_size);
    CIRCBUF_CHECK(rc >= 0,NULL);
  }

  size_t pos = buf->pos;
  pos += n;

  if(pos + buf->read_size - 1 >= buf->read_pos){
    int rc = circbuf_fill(buf); // Does not change buf->pos
    CIRCBUF_CHECK(rc >= 0, NULL);
  }

  buf->pos = pos;

  char* head = buf->bytes + pos;
  return head; 
}
