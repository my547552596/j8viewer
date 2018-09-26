#include "Atwo.h"
#define IDR_MAINFRAME 128

class appin : public CWinApp {
public:
	virtual BOOL ExitInstance();
	virtual BOOL InitInstance();

protected:
	GdiplusStartupInput m_gdiplusInput;
	ULONG_PTR m_gdiplusToken;
};

class j8viewer : public CFrameWnd {
public:
	j8viewer(char *iPath);

protected:
	afx_msg void OnDropFiles(HDROP h);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow();
	DECLARE_MESSAGE_MAP();

private:
	char *imgPath;
	void autoSize(int imgHeight, int imgWidth);
};