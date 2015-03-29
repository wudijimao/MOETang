#include "MOEClient.h"
#include <windows.h>
#include <time.h>
int main(int argc, char* argv[])
{
	MOEClient myclient=MOEClient(4500,"192.168.1.111");
	while(true)
	{
		clock_t myclock = clock(); 
		NumberSend sendmsg2;
		sendmsg2.num = 3;
		myclient.Send(sendmsg2);
		NumberSend sendmsg1;
		sendmsg1.num = 3;
		myclient.Send(sendmsg1);
		/*ClientMapMessage abcd;
		myclient.Recv(abcd);*/
		int a = clock()-myclock;
		cout<<"time:"<<float(a)/1000.0<<endl;
		//Sleep(100);
	}
	

}