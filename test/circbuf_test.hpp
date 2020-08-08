#include <cxxtest/TestSuite.h>

#include <circbuf.h>

class CircbufTestSuite : public CxxTest::TestSuite {

  circbuf* c;
  char* b;
  uint size = 16;
  uint read_size = 4;
  FILE* fd;
  
public:

  void setUp(){
    fd = fopen("resources/test/bytes.txt","r");
    if(fd == NULL) throw "File read error";
    b = (char*)calloc(size,sizeof(char));
    c = circbuf_create(b,size,read_size,fd);
  }

  void tearDown(){
    free(b);
    fclose(fd);
    circbuf_free(c);
  }

  void test_circbuf_head(){
    TS_ASSERT_EQUALS(circbuf_head(c), circbuf_head_forward(c,0));
    TS_ASSERT_EQUALS(circbuf_head(c),b+read_size);
    
    circbuf_head_forward(c,2);
    TS_ASSERT_EQUALS(circbuf_head(c),circbuf_head_forward(c,0));
    TS_ASSERT_EQUALS(circbuf_head(c),b+read_size+2);
  }

  void test_circbuf_head_error(){
    TS_ASSERT(circbuf_head(c));

    TS_ASSERT(!circbuf_head(NULL));

  }

  void test_circbuf_head_forward(){
    char* h = circbuf_head_forward(c,0);
    TS_ASSERT_EQUALS('a',h[0]);
    TS_ASSERT_EQUALS('\0',h[-4]);
    //circbuf_print(c);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('e',h[0]);
    TS_ASSERT_EQUALS('a',h[-4]);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('i',h[0]);
    TS_ASSERT_EQUALS('e',h[-4]);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('m',h[0]);
    TS_ASSERT_EQUALS('i',h[-4]);
    h = circbuf_head_forward(c,3);
    TS_ASSERT_EQUALS('p',h[0]);
    TS_ASSERT_EQUALS('l',h[-4]);
    TS_ASSERT_EQUALS('s',h[3]);
    //circbuf_print(c);

    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);

    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);

    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);

    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);
  }

  void test_circbuf_head_forward_2(){
    char* h = circbuf_head_forward(c,1);
    TS_ASSERT_EQUALS('b',h[0]);
    //circbuf_print(c);
    h = circbuf_head_forward(c,2);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('d',h[0]);
    TS_ASSERT_EQUALS('a',h[-3]);
    h = circbuf_head_forward(c,3);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('g',h[0]);
    TS_ASSERT_EQUALS('c',h[-4]);
    h = circbuf_head_forward(c,1);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('h',h[0]);
    TS_ASSERT_EQUALS('d',h[-4]);
    h = circbuf_head_forward(c,3);
    TS_ASSERT_EQUALS('k',h[0]);
    TS_ASSERT_EQUALS('g',h[-4]);
    TS_ASSERT_EQUALS('n',h[3]);
    //circbuf_print(c);

    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    h = circbuf_head_forward(c,4);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('w',h[0]);

    h = circbuf_head_forward(c,3);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('z',h[0]);

    h = circbuf_head_forward(c,3);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);

    h = circbuf_head_forward(c,3);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);

    h = circbuf_head_forward(c,3);
    //circbuf_print(c);
    TS_ASSERT_EQUALS('\0',h[0]);
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
    circbuf* c = circbuf_create(b,size,read_size,fd);
    TS_ASSERT(c);

    c = circbuf_create(NULL,size,read_size,fd);
    TS_ASSERT(!c);

    c = circbuf_create(b,size,read_size,NULL);
    TS_ASSERT(!c);

    c = circbuf_create(b,8,read_size,fd);
    TS_ASSERT(!c);
  }

};
