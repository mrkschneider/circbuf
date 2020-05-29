#include <cxxtest/TestSuite.h>

#include <circbuf.h>

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
    circbuf_fill(c);
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
  }

};
