#include  "ClassA.h"
#include  "ClassB.h"
#include <stdio.h>
#include <stdlib.h>


int  main(void){
  B  test;
  E  *itf=(E*)&test;
  A  *org= &test ;
  org->getVir();
/*  itf->InterfaceCall();
  test.call_pub();
  test.call_pri();
  test.getName();
  test.dupName();*/
  return 1;
}

