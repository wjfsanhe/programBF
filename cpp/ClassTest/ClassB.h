#include <stdio.h>
#include <stdlib.h>
class B:public A{
public:
//	void func_pub(void){ printf("overwrite virtual\n");}
	void call_pub(void){ func_pub();printf("req :%d\n",aaa); }
	void call_pri(void){ func_pri(); }
	void call_protect_vir(void){func_protected_vir();}
//	void dupName(void) {  printf("dupNameB\n");}
protected:
	//virtual int func_protected_vir(void){printf("ClassB func protected virtual\n");}
private:
	static const char *mName;
	static const int aaa=7;
	int func_pri(void){ printf("virtual pri,%d\n",aaa);}
	virtual void InterfaceCall(){printf("Interface call in B\n");};
};
const char *B::mName="BBB";
