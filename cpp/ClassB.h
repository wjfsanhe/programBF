#include <stdio.h>
#include <stdlib.h>
class B:public A{
public:
	void func_pub(void){ printf("overwrite virtual\n");}
	void call_pub(void){ func_pub(); }
};
