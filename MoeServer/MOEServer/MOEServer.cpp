#include "MOEServer.h"

int main(int argc, char* argv[])
{
	MOEServer newServer = MOEServer(4500,"192.168.1.111");
	newServer.SetThread(MOEServer::ClientThread);
	newServer.run();
}