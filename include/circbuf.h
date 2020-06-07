#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

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

#define CIRCBUF_CHECK(expression,return_value) \
  if(!(expression)){							\
    fprintf(stderr,"circbuf check failed: '%s' in %s at %s:%d\n",	\
	    #expression,__func__,__FILE__,__LINE__);			\
    if(errno) perror("Error: ");					\
    return return_value;						\
  }

circbuf* circbuf_create(char* bytes, uint size, uint read_size, FILE* fd);
void circbuf_free(circbuf* buf);
int circbuf_print(circbuf* buf);
char* circbuf_head(circbuf* buf);
char* circbuf_head_forward(circbuf* buf, uint n);

#ifdef __cplusplus
}
#endif
