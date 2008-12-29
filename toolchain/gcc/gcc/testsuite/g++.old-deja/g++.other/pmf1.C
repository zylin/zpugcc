// { dg-do run  }
struct foo {};
typedef long unsigned int & (foo::*pmf)(void);
/* ZPU: what does void foo(...) mean anyway? */
void fn (pmf) {}
int main ()
{
  pmf y = 0;
  fn (y);
}
