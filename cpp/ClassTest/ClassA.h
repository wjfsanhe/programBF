#include <stdio.h>
#include <stdlib.h>
#include "ClassE.h"
class A:public E {
public:
	void getName(){ printf("name:%s\n",mName);}
	void dupName(){ printf("dupNameA\n"); }
	void getVir(){func_protected_vir();}
protected:
	int ttt;
	static const int aaa=8;
	void func_pub(){printf("public func aAA,aaa=%d\n",ttt);}
	virtual int func_protected_vir(void){printf("Class A protected virtual\n");}
private:
	static const char* mName;
	void func_pri(){printf("private func b\n");}
	virtual void InterfaceCall(){printf("interface call in A\n");}

};
const char* A::mName="AAA";
