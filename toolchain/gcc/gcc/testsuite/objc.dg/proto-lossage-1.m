/* Test for situations in which protocol conformance information
   may be lost, leading to superfluous warnings.  */
/* Author: Ziemowit Laski <zlaski@apple.com>.  */
/* { dg-do compile } */

/* One-line substitute for objc/objc.h */
typedef struct objc_object { struct objc_class *class_pointer; } *id;

@protocol NSObject
- (int)someValue;
@end

@interface NSObject <NSObject>
@end

@protocol PlateMethods
- (void)someMethod;
@end

@interface Foo {
  NSObject <PlateMethods> *plate;
  id <PlateMethods> plate1;
  NSObject *plate2;
}
- (id <PlateMethods>) getPlate;
- (id <NSObject>) getPlate1;
- (int) getValue;
@end

@implementation Foo
- (id <PlateMethods>) getPlate {
  return plate;  /* { dg-bogus "does not implement" } */
}
- (id <NSObject>) getPlate1 {
  return (id <NSObject>)plate1; /* { dg-bogus "does not conform" } */
}
- (int) getValue {
  int i = [plate1 someValue];   /* { dg-warning ".\\-someValue. not implemented by protocol\\(s\\)" } */
     /* { dg-warning "\\(Messages without a matching method signature" "" { target *-*-* } 38 } */
     /* { dg-warning "will be assumed to return .id. and accept" "" { target *-*-* } 38 } */
     /* { dg-warning ".\.\.\.. as arguments\.\\)" "" { target *-*-* } 38 } */
     /* { dg-warning "initialization makes integer from pointer without a cast" "" { target *-*-* } 38 } */

  int j = [(id <NSObject>)plate1 someValue];  /* { dg-bogus "not implemented by protocol" } */
  int k = [(id)plate1 someValue]; /* { dg-bogus "not implemented by protocol" } */
  return i + j + k;
}
@end
