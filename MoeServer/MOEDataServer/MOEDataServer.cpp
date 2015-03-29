#include "MOEDataServer.h"
void main(){
	MOEDataServer data;
	//bool a = data.myinsert("login","username,password","'wudijima2446','12322'");
	//bool a = data.myupdate("login","username=admin","password=235");

	data.myselect("login","username='adm'");
	MyType type[2];
	type[0] = MyType::mystring;
	type[1] = MyType::mystring;
	data.showAll(type,2);
}
