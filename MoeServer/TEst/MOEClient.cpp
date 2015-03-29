#include "../MOEClient/MOEClient.h"
#include <windows.h>
#include <time.h>
using namespace std;
SessionMessage recmsg1;
HallServerWorkload hsw;
int main(int argc, char* argv[])
{
	LoginMessage sendmsg1;
	sendmsg1.setID("admin");
	sendmsg1.setPassword("123");
	MOEClient myclient=MOEClient(4000,"192.168.1.111");
	myclient.Send(sendmsg1);
	myclient.Recv(recmsg1);
	ServerMessage sermsg1;
	myclient.Recv(sermsg1);
	myclient.~MOEClient();
	MOEClient myclient1=MOEClient(sermsg1.port,sermsg1.IP);
	SessionMessage recmsg=recmsg1;
	myclient1.Send(recmsg);
	CheckMessage chkmsg1;
	myclient1.Recv(chkmsg1);
	if(chkmsg1.IsOk){
		myclient1.Recv(hsw);
		cout<<"login success"<<endl;
		int mychoose=0;
		MOEClient myclient=MOEClient(hsw.server[mychoose].port,hsw.server[mychoose].IP);
		SessionMessage recmsg2=recmsg1;
		myclient.Send(recmsg2);
		CheckMessage chkmsg1;
		myclient.Recv(chkmsg1);
		if(chkmsg1.IsOk){
			HouseSimpleMessage hsm;
			NumberSend num;
			num.num=0;
			myclient.Send(num);
			myclient.Recv(hsm);
			cout<<"choose area success"<<endl;
			MOEClient myclient=MOEClient(hsw.server[mychoose].port,hsw.server[mychoose].IP);
			SessionMessage recmsg=recmsg1;
			myclient.Send(recmsg);
			CheckMessage chkmsg1;
			myclient.Recv(chkmsg1);
			if(chkmsg1.IsOk)
			{
				NumberSend num;
				num.num=1;
				myclient.Send(num);
				CheckMessage chkmsg2;
				myclient.Recv(chkmsg2);
				if(chkmsg2.IsOk)
				{
					myclient.Recv(num);
					int roomnum=num.num;
					MOEClient myclient1=MOEClient(hsw.server[mychoose].port,hsw.server[mychoose].IP);
					SessionMessage recmsg2=recmsg1;
					myclient1.Send(recmsg2);
					CheckMessage chkmsg3;
					myclient1.Recv(chkmsg3);
					if(chkmsg3.IsOk)
					{
						NumberSend num1;
						num1.num=3;
						myclient1.Send(num1);
						CheckMessage chkmsg4;
						NumberSend num3;
						num3.num=roomnum;
						myclient1.Send(num3);
						myclient1.Recv(chkmsg4);
						if(chkmsg4.IsOk)
						{
							ServerMessage roomserver1;
							myclient1.Recv(roomserver1);//收到游戏服务器地址
							MOEClient roomclient1=MOEClient(roomserver1.port,roomserver1.IP);
							NumberSend num2;
							num2.num=0;
							SessionMessage recmsg3=recmsg1;
							roomclient1.Send(recmsg3);
							CheckMessage chkmsg5;
							roomclient1.Recv(chkmsg5);
							if(chkmsg5.IsOk){
								roomclient1.Send(num2);
								//获取房间信息
								oneHouseMessage ohm;
								roomclient1.Recv(ohm);
								NumberSend num99;
								num99.num=6;
								roomclient1.Send(num99);
								cout<<"create room success"<<endl;
								MOEClient gameclient=MOEClient(roomserver1.port,roomserver1.IP);
								SessionMessage recmsg=recmsg1;
								gameclient.Send(recmsg);
								CheckMessage chkmsg2;
								gameclient.Recv(chkmsg2);
								if(chkmsg2.IsOk)
								{
									
									NumberSend num1;
									num1.num=1;
									CheckMessage chkmsg1;
									gameclient.Send(num1);
									NumberSend num2;
									num2.num=5;
									gameclient.Send(num2);
									gameclient.Recv(chkmsg1);
									ClientMapMessage cmm1;
									gameclient.Recv(cmm1);
									MOEClient gameclient1=MOEClient(roomserver1.port,roomserver1.IP);
									SessionMessage recmsg=recmsg1;
									gameclient1.Send(recmsg);
									CheckMessage chkmsg;
									gameclient1.Recv(chkmsg);
									while(true)
									{
										clock_t myclock = clock();
										NumberSend num1;
										num1.num=4;
										gameclient1.Send(num1);
										ClientKeysMessage ckm;
										ckm.Space=0;
										ckm.Dir=0;
										gameclient1.Send(ckm);
										ClientMapMessage cmm2;
										gameclient1.Recv(cmm2);
										int a = clock()-myclock;
										cout<<"time:"<<float(a)/1000.0;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	int i=0;
	cin>>i;
}