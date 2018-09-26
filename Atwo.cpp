#include "Atwo.h"

BEGIN_MESSAGE_MAP(Atwo, CFrameWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()

Atwo::Atwo() {
	CreateEx(0, 0, 0, WS_POPUP, CRect(0, 0, 200, 200), 0, 0, 0);
	ModifyStyleEx(WS_EX_CLIENTEDGE, WS_EX_TOOLWINDOW, SWP_FRAMECHANGED);
	SetWindowPos(&wndTopMost, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	SetCursor(LoadCursor(0, IDC_ARROW));
	CenterWindow();
}

void Atwo::OnPaint() {
	CDC *pDC = GetDC();
	int c, x, y, z[] = { 0, 4, 4, 116, 86, 40, 56, 0 };

	for(y = 0; y < 8; y++) {
		for(x = 7; x >= 0; x--) {
			c = floor(z[y] / pow(2, x)) ? 255 : 0;
			CBrush cb(RGB(c, c, c));
			CRect cr(x * 25, y * 25, x * 25 + 25, y * 25 + 25);
			pDC->FillRect(&cr, &cb);
			z[y] %= (int)pow(2, x);
		}
	}

	ReleaseDC(pDC);
}