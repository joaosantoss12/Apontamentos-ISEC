#include <tchar.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <windows.h>

/*
#define PIPE_NAME TEXT("\\\\.\\pipe\\teste")
#define N 10

typedef struct {
	HANDLE hPipe[N];
	HANDLE hMutex; //para controlar o numClientes
	int numClientes;
	int terminar;
}ThreadDados;

//envia mensagem para todos os leitores que est�o disponiveis
DWORD WINAPI ThreadMensagens(LPVOID param) {
	ThreadDados* dados = (ThreadDados*)param;
	TCHAR buf[256];
	DWORD n;
	int i;

	//aqui , o servidor j� recebeu um cliente
	do {
		//vai buscar informa��o � consola
		_tprintf(TEXT("[ESCRITOR] Frase: "));
		_fgetts(buf, 256, stdin);
		buf[_tcslen(buf) - 1] = '\0';

		//bloqueamos aqui porque � uma regiao critica
		WaitForSingleObject(dados->hMutex,INFINITE);

		//escreve no named pipe
		for (i = 0; i < dados->numClientes; i++) {
			if (!WriteFile(dados->hPipe[i], buf, _tcslen(buf) * sizeof(TCHAR), &n, NULL)) {
				_tprintf(TEXT("[ERRO] Escrever no pipe! (WriteFile)\n"));
				exit(-1);
			}

			_tprintf(TEXT("[ESCRITOR] Enviei %d bytes ao leitor [%d]... (WriteFile)\n"), n,i);
		}
		//libertamos o mutex
		ReleaseMutex(dados->hMutex);


	} while (_tcscmp(buf, TEXT("fim")));

	dados->terminar = 1;

	return 0;

}

int _tmain(int argc, LPTSTR argv[]) {

	HANDLE hPipe, hThread;
	ThreadDados dados;

#ifdef UNICODE
	_setmode(_fileno(stdin), _O_WTEXT);
	_setmode(_fileno(stdout), _O_WTEXT);
#endif

	dados.numClientes = 0;
	dados.terminar = 0;
	dados.hMutex = CreateMutex(NULL, FALSE, NULL); //Cria��o do mutex

	if (dados.hMutex == NULL) {
		_tprintf(TEXT("[Erro] ao criar mutex!\n"));
		return -1;
	}

	//criacao da thread
	hThread = CreateThread(NULL, 0, ThreadMensagens, &dados, 0, NULL);
	if (hThread == NULL) {
		_tprintf(TEXT("[Erro] ao criar thread!\n"));
		return -1;
	}

	_tprintf(TEXT("[ESCRITOR] Criar uma c�pia do pipe '%s' ... (CreateNamedPipe)\n"), PIPE_NAME);


	
	while (!dados.terminar) {

		// PIPE_ACCESS_OUTBOUND -> o ESCRITOR escreve e o LEITOR recebe
		//1� nome do named pipe, 2�configura��o da abertura, 3�configura��es do pipe,4� numero maximo de instancias,5� e 6�tamanho do buffer de entrada e de saida
		//7� timeout, 8� security atributes
		hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_OUTBOUND, PIPE_WAIT | PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE, N, 256 * sizeof(TCHAR), 256 * sizeof(TCHAR), 1000, NULL);

		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(TEXT("[ERRO] Criar Named Pipe! (CreateNamedPipe)"));
			exit(-1);
		}


		_tprintf(TEXT("[ESCRITOR] Esperar liga��o de um leitor... (ConnectNamedPipe)\n"));

		//o servidor espera at� ter um cliente conectado a esta inst�ncia
		//bloqueia aqui
		if (!ConnectNamedPipe(hPipe, NULL)) {
			_tprintf(TEXT("[ERRO] Liga��o ao leitor! (ConnectNamedPipe\n"));
			exit(-1);
		}

		//bloqueamos no mutex
		WaitForSingleObject(dados.hMutex,INFINITE);

		//preenchemos o array
		dados.hPipe[dados.numClientes] = hPipe;
		dados.numClientes++;
		
		//libertamos o mutex
		ReleaseMutex(dados.hMutex);

	}

	//esperar que a thread termine
	WaitForSingleObject(hThread, INFINITE);

	//desligamos todos os clientes que se ligaram
	for (int i = 0; i < dados.numClientes; i++) {
		_tprintf(TEXT("[ESCRITOR] Desligar o pipe (DisconnectNamedPipe)\n"));

		//desliga a instancia ao named pipe
		if (!DisconnectNamedPipe(dados.hPipe[i])) {
			_tprintf(TEXT("[ERRO] Desligar o pipe! (DisconnectNamedPipe)"));
			exit(-1);
		}
	}


	exit(0);
}
*/