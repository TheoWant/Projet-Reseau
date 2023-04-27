#include "framework.h"

using namespace std;

int main()
{
	// ========== faut ranger ca ==========
	ClientSide client;
	HANDLE hThread;
	DWORD dwThreadId;
	hThread = CreateThread(NULL, 0, ClientSide::ClientToServerThread, NULL, 0, &dwThreadId);

	client.MainThread();

	return 0;
}