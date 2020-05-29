#include <cxxtest/TestSuite.h>

#include <circbuf.h>
#include <cassert>

class CircbufTestSuite : public CxxTest::TestSuite {

  circbuf* c;
  char* b;
  uint size = 12;
  FILE* fd;
  
public:

  void setUp(){
    fd = fopen("resources/test/bytes.txt","r");
    if(fd == NULL) throw "File read error";
    b = (char*)malloc(sizeof(char)*size);
    c = circbuf_create(b,size,4,fd);
  }

  void tearDown(){
    free(b);
    fclose(fd);
    circbuf_free(c);
  }

  void test_circbuf_head_forward(){
    char* h = circbuf_head_forward(c,0);
    TS_ASSERT_EQUALS('a',h[0]);
    circbuf_print(c);
    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    TS_ASSERT_EQUALS('e',h[0]);
    TS_ASSERT_EQUALS('a',h[-4]);
    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    TS_ASSERT_EQUALS('i',h[0]);
    TS_ASSERT_EQUALS('e',h[-4]);
    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    TS_ASSERT_EQUALS('m',h[0]);
    TS_ASSERT_EQUALS('i',h[-4]);
    TS_ASSERT_EQUALS('e',h[-8]);
    h = circbuf_head_forward(c,3);
    TS_ASSERT_EQUALS('p',h[0]);
    TS_ASSERT_EQUALS('l',h[-4]);
    TS_ASSERT_EQUALS('s',h[3]);
    circbuf_print(c);

    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    TS_ASSERT_EQUALS('\n',h[0]);

    h = circbuf_head_forward(c,4);
    circbuf_print(c);
    TS_ASSERT_EQUALS('\n',h[0]);

    h = circbuf_head_forward(c,3);
    circbuf_print(c);
    TS_ASSERT_EQUALS('\n',h[0]);
  }

  void test_circbuf_head_forward_error(){
    char* h = circbuf_head_forward(c,0);
    TS_ASSERT(h);

    h = circbuf_head_forward(c,-1);
    TS_ASSERT(!h);

    h = circbuf_head_forward(c,5);
    TS_ASSERT(!h);

  }

  void test_circbuf_create(){
    circbuf* c = circbuf_create(b,12,4,fd);
    TS_ASSERT(c);

    c = circbuf_create(NULL,12,4,fd);
    TS_ASSERT(!c);

    c = circbuf_create(b,12,4,NULL);
    TS_ASSERT(!c);

    c = circbuf_create(b,8,4,fd);
    TS_ASSERT(!c);
  }

};
