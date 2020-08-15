#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif
  
typedef struct circbuf {
  char* bytes;
  size_t pos;
  size_t read_pos;
  size_t read_size;
  size_t size;
  FILE* fd;
  int finished;
} circbuf;

extern int CIRCBUF_DEBUG_LOG_LEVEL;
  
#ifdef CIRCBUF_DEBUG
#define CIRCBUF_CHECK(expression,return_value) \
  if(!(expression)){							\
    if(CIRCBUF_DEBUG_LOG_LEVEL > 0) {					\
    fprintf(stderr,"circbuf check failed: '%s' in %s at %s:%d\n",	\
	    #expression,__func__,__FILE__,__LINE__);			\
    if(errno) perror("Error: ");					\
    }									\
    return return_value;						\
  }
#else
#define CIRCBUF_CHECK(expression,return_value)
#endif

circbuf* circbuf_create(char* bytes, size_t size, size_t read_size, FILE* fd);
void circbuf_free(circbuf* buf);
int circbuf_fprint(circbuf* buf, FILE* fd);
int circbuf_print(circbuf* buf);
char* circbuf_head(circbuf* buf);
char* circbuf_head_forward(circbuf* buf, size_t n);

#ifdef __cplusplus
}
#endif
