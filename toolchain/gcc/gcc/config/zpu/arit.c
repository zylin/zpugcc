typedef unsigned int USItype		__attribute__ ((mode (SI)));
typedef unsigned int UDItype		__attribute__ ((mode (DI)));

#if defined (L_mulsi3) 

USItype
__mulsi3 (USItype a, USItype b)
{
  USItype c = 0;

  do 
    {
		/* use mask & unroll a bit */
		c+=b&~(((a&1)-1));
		a >>= 1;
		b <<= 1;

    } while (a != 0);

  return c;
}
#endif

#if defined (L_xordi3) 
UDItype
__xordi3 (UDItype a, UDItype b)
{
  return (a&~b)|(~a&b);
}
#endif


