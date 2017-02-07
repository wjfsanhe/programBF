#include <stdio.h>
#include <stdlib.h>
class A {
public:
	int ttt;
virtual	void func_pub(){}//{printf("public func a\n");}
private:
	int aaa;
	void func_pri(){printf("private func b\n");}

};
