#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class test{
public:
	 test(char *data){
	 	name=data;
	 };
	 test()
	 :name("www.google.cn"){
		
	 }
	 
	 string* GetName(){
	 return &name ;
	}
private:
	 string name;
};
void *aacDecoder_Open ( unsigned int 
        transportFmt, unsigned  nrOfLayers ) {
	cout <<"right"<<endl;
	return NULL;
}
int  aacDecoder_ConfigRaw(void *self,const char conf[], const unsigned int length ) {
	
	return -1;
}
int  main()
{
	class test *a=new test("www.baidu.com");
	class test *b=new test();
	char  *name=new char[40];
	cout<<*(a->GetName())<<endl;
	cout<<*(b->GetName())<<endl;
	strcpy(name,a->GetName()->c_str());
	cout<<"host name:"<<name<<endl;
	aacDecoder_Open(1,1);
	aacDecoder_ConfigRaw(NULL,"list",1);
	memset(name,0,strlen(name));
	gethostname(name,40);
	cout<<"return host:"<<name<<endl;
	return 0;
}
