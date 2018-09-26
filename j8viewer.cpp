#include "j8viewer.h"

CPoint imgMargin = CPoint(0, 0);
CRect winSize = CRect(0, 0, 540, 360);

BOOL appin::InitInstance() {
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusInput, NULL);

	for(int i = 1; i < __argc; i++) {
		m_pMainWnd = new j8viewer(__argv[i]);
		m_pMainWnd->UpdateWindow();
		m_pMainWnd->ShowWindow(m_nCmdShow);
	}

	return true;
}

BOOL appin::ExitInstance() {
	delete m_pMainWnd;

	m_pMainWnd = new Atwo();
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	Sleep(2000);

	delete m_pMainWnd;
	m_pMainWnd = NULL;

	GdiplusShutdown(m_gdiplusToken);

	return false;
}

BEGIN_MESSAGE_MAP(j8viewer, CFrameWnd)
	ON_WM_DROPFILES()
	ON_WM_PAINT()
	ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()

j8viewer::j8viewer(char *iPath) {
	Create(NULL, _T("j8viewer"), WS_CAPTION | WS_SYSMENU, winSize);
	DragAcceptFiles(TRUE);

	imgPath = iPath;

	HICON m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	CRect clientRect, windowRect;
	GetClientRect(&clientRect);
	GetWindowRect(&windowRect);
	imgMargin.x = windowRect.right - windowRect.left - clientRect.right;
	imgMargin.y = windowRect.bottom - windowRect.top - clientRect.bottom;
}

void j8viewer::OnDropFiles(HDROP h) {
	DragQueryFile(h, 0, imgPath, 1024);
	DragFinish(h);

	OnShowWindow();
}

void j8viewer::OnPaint() {
	int ipLength = MultiByteToWideChar(CP_ACP, 0, imgPath, -1, NULL, 0);
	wchar_t *imgPath_wc = new wchar_t[ipLength];
	MultiByteToWideChar(CP_ACP, 0, imgPath, -1, imgPath_wc, ipLength);
	Image img(imgPath_wc);
	delete [] imgPath_wc;
	imgPath_wc = NULL;

	if(img.GetHeight() && img.GetWidth()) {
		autoSize(img.GetHeight(), img.GetWidth());
	} else {
		return;
	}

	CDC *pDC = GetDC();
	Graphics g(pDC->m_hDC);
	g.DrawImage(&img, 0, 0, winSize.right - imgMargin.x, winSize.bottom - imgMargin.y);
	ReleaseDC(pDC);
}

void j8viewer::OnShowWindow() {
	SetWindowText((CString)"j8viewer " + imgPath);
	SendMessage(WM_PAINT, 0, 0);

	MoveWindow(winSize);
	CenterWindow();
}

void j8viewer::autoSize(int imgHeight, int imgWidth) {
	winSize.bottom = imgHeight + imgMargin.y;
	winSize.right = imgWidth + imgMargin.x;

	RECT scrSize;
	SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&scrSize, 0);
	scrSize.bottom = scrSize.bottom * 3 / 4;
	scrSize.right = scrSize.right * 3 / 4;

	if(!(winSize.bottom < scrSize.bottom && winSize.right < scrSize.right)) {
		if((float)scrSize.right / scrSize.bottom > (float)imgWidth / imgHeight) {
			winSize.bottom = scrSize.bottom + imgMargin.y;
			winSize.right = scrSize.bottom * imgWidth / imgHeight + imgMargin.x;
		} else {
			winSize.bottom = scrSize.right * imgHeight / imgWidth + imgMargin.y;
			winSize.right = scrSize.right + imgMargin.x;
		}
	}
}

appin jobar_20180910132101;