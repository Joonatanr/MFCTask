
// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	myGraph = new CGraph(2, 2);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	/* Set default values for the init boxes. */
	SetDlgItemText(IDC_EDIT_UVALUE, L"1");
	SetDlgItemText(IDC_EDIT_FREQ, L"2");
	SetDlgItemText(IDC_EDIT_OFFSET, L"0");
	SetDlgItemText(IDC_EDIT_XMIN, L"0");
	SetDlgItemText(IDC_EDIT_XMAX, L"10");
	SetDlgItemText(IDC_EDIT_YMIN, L"-2");
	SetDlgItemText(IDC_EDIT_YMAX, L"2");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/* Custom function for calculating the necessary datapoints for the graph display. */
void CMFCApplication1Dlg::calculateValues(GraphicPair* dest, float beginX, float endX)
{
	/* We calculate 600 value pairs. */
	float interval = endX - beginX;
	float singleInterval = interval / 600;

	float currentX = beginX;
	float currentY;
	
	/* Lets get numeric values from the inputs also. */
	float Uvalue;
	float FrqValue;
	float OffsetValue;

	CString parseString;

	GetDlgItemText(IDC_EDIT_UVALUE, parseString);
	Uvalue = _ttof(parseString);

	GetDlgItemText(IDC_EDIT_FREQ, parseString);
	FrqValue = _ttof(parseString);

	GetDlgItemText(IDC_EDIT_OFFSET, parseString);
	OffsetValue = _ttof(parseString);


	for (int x = 0; x < 600; x++) 
	{
		currentY = sinf(2 * 3.14 * FrqValue * currentX);
		currentY *= Uvalue;
		currentY += OffsetValue;

		dest[x].xValue = currentX;
		dest[x].yValue = currentY;

		currentX += singleInterval;
	}

}

void CMFCApplication1Dlg::OnBnClickedButton1()
{
	float beginX;
	float endX;
	CString parseString;

	GetDlgItemText(IDC_EDIT_XMIN, parseString);
	beginX = _ttof(parseString);

	GetDlgItemText(IDC_EDIT_XMAX, parseString);
	endX = _ttof(parseString);

	/* Here we do the actual calculations. */
	calculateValues(myArray, beginX, endX);

	/*Set the value pairs here. */
	myGraph->setMeasurementValues(myArray);

	/* Finally we draw the graph. */
	if (myGraph != NULL)
	{
		//CPaintDC dc(this);
		CClientDC dc(this);
		myGraph->draw(&dc);
	}
}
