#include "cApplicationStartup.h"
#include <exception>

CLoginServer *loginServer;

LRESULT CALLBACK BackgroundWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {

	case WM_CLOSE:
		IsOnCloseProcess = TRUE;
		if (MessageBox(NULL, "Player data not saved! Shutdown server now?", "Shutdown?", MB_ICONEXCLAMATION | MB_YESNO) == IDYES)
		{
			//SAFEDELETE(Server);
			exit(EXIT_SUCCESS);
		}
		else IsOnCloseProcess = FALSE;
		break;

	case WM_PAINT:
		//OnPaint();
		break;

	case WM_KEYDOWN:
		//if (Server) Server->OnKeyDown(wParam);
		return(DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_KEYUP:
		//if (Server) Server->OnKeyUp(wParam);
		return(DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_DESTROY:
		//OnDestroy();
		break;

	case WM_USER_ACCEPT:
		//Server->OnUserAccept(hWnd);
		break;

	case WM_GATESERVER_ACCEPT:
		//Server->OnGateServerAccept(hWnd);
		break;

	default:
		if ((message >= WM_ONCLIENTSOCKETEVENT) && (message < WM_ONCLIENTSOCKETEVENT + MAXCLIENTS)) {
			//Server->OnClientSocketEvent(message, wParam, lParam);
		}
		else if ((message >= WM_ONGAMESERVERSOCKETEVENT) && (message < WM_ONGAMESERVERSOCKETEVENT + MAXGAMESERVERSOCKETS)) {
			//Server->OnGameServerSocketEvent(message, wParam, lParam);
		}
		else {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	return NULL;
}

void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2)
{
	loginServer->OnTimer();
}

void cApplicationStartup::Startup()
{
	cLogging::LogToConsole("Starting up Helbreath Login Server \n");
	try {
		ConnectToDatabase();
		StartLoginServer();		
	}
	catch (std::exception &e) {
		cLogging::LogToConsole((char*)e.what());
	}
	cLogging::LogToConsole("Entering to main loop \n");
	while (1) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&Message, NULL, 0, 0)) {
				//return static_cast<int>(Message.wParam);
			}
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else WaitMessage();
	}
	scanf("%d");
}

void cApplicationStartup::ConnectToDatabase()
{
	ZeroMemory(loginServer->mySqlUser, sizeof(loginServer->mySqlUser));
	ZeroMemory(loginServer->mySqlPwd, sizeof(loginServer->mySqlPwd));
	if (!loginServer->ReadProgramConfigFile("LServer.cfg")) {
		//return FALSE;
	}

	cLogging::LogToConsole("Connecting to mySql database... \n");
	PutLogList("(!) Connecting to mySql database...");

	if (loginServer == NULL) {
		throw "Unknown error occured! Server = NULL";
	}
	UINT iResult = 0;
	mysql_init(&mySQL);
	if (!mysql_real_connect(&mySQL, loginServer->mySqlAddress, loginServer->mySqlUser, loginServer->mySqlPwd, "helbreath", loginServer->mySqlPort, NULL, NULL)) {
		iResult = loginServer->MyAux_Get_Error(&mySQL);
		mysql_close(&mySQL);
	}
	if (iResult != NULL) {
		if (iResult == 2003) PutLogList("(!!!) mySql server seems to be offline, please check the IP", WARN_MSG);
		mysql_close(&mySQL);
	}
	PutLogList("-Connection to mySQL database was sucessfully established!");
}

void cApplicationStartup::StartLoginServer()
{
	cLogging::LogToConsole("Login Server initialization \n");
	HWND hwnd = CreateBackgroundWindow();
	MMRESULT timer = _StartTimer();
	if (!loginServer->InitServer(hwnd, timer)) {
		//SAFEDELETE(Server);
	}
}

HWND cApplicationStartup::CreateBackgroundWindow()
{
	WNDCLASS wndclass;
	CHAR *ProviderClass = "AsyncSelect";
	HWND Window;
	char cTitle[100];

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = &BackgroundWindowProcess;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = NULL;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = ProviderClass;

	if (RegisterClass(&wndclass) == 0)
	{
		printf("RegisterClass() failed with error %d\n", GetLastError());
		return NULL;
	}
	else {
		printf("RegisterClass() is OK!\n");
	}

	// Create a window
	Window = CreateWindowEx(
		0,
		ProviderClass,
		cTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		NULL,
		NULL);

	if (Window == NULL)
	{
		printf("CreateWindow() failed with error %d\n", GetLastError());
		return NULL;
	}
	else {
		printf("CreateWindow() is OK!\n");
	}
	return Window;
}

MMRESULT cApplicationStartup::_StartTimer()
{
	TIMECAPS caps;
	MMRESULT timerid;

	timeGetDevCaps(&caps, sizeof(caps));
	timeBeginPeriod(caps.wPeriodMin);
	timerid = timeSetEvent(MAINTIMERSIZE, 0, _TimerFunc, 0, (UINT)TIME_PERIODIC);
	return timerid;
}

cApplicationStartup::cApplicationStartup()
{
	loginServer = new CLoginServer;
	serverTimer = new cServerTimer;
}


cApplicationStartup::~cApplicationStartup()
{
}
