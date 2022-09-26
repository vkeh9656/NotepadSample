
// NotepadSampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "NotepadSample.h"
#include "NotepadSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CNotepadSampleDlg 대화 상자



CNotepadSampleDlg::CNotepadSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NOTEPADSAMPLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotepadSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNotepadSampleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN_BTN, &CNotepadSampleDlg::OnBnClickedOpenBtn)
	ON_BN_CLICKED(IDC_SAVE_BTN, &CNotepadSampleDlg::OnBnClickedSaveBtn)
END_MESSAGE_MAP()


// CNotepadSampleDlg 메시지 처리기

BOOL CNotepadSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CNotepadSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CNotepadSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotepadSampleDlg::OnBnClickedOpenBtn()
{
	wchar_t name_filter[] = L"모든 파일 (*.*)|*.*|C++ 파일 (*.cpp)|*.cpp|Header 파일 (*.h)|*.h|텍스트 파일 (*.txt)|*.txt||";
	CFileDialog ins_dlg(TRUE, L"cpp", L"*.cpp", OFN_HIDEREADONLY | OFN_NOCHANGEDIR, name_filter );
	ins_dlg.m_ofn.nFilterIndex = 2;

	if (IDOK == ins_dlg.DoModal())
	{
		SetDlgItemText(IDC_PATH_EDIT, ins_dlg.GetPathName());

		FILE* p_file = NULL;
		CString str;
		if (0 == _wfopen_s(&p_file, ins_dlg.GetPathName(), L"rt")) // error가 없다면 0을 반환
		{
			char temp_str[1024];
			int length;
			wchar_t unicode_str[1024];

			while (fgets(temp_str, 1024, p_file) != NULL) // fgets -> 한줄씩 읽다가 공백 나오면 NULL 반환
			{
				length = MultiByteToWideChar(CP_UTF8, 0, temp_str, -1, NULL, 0);
				MultiByteToWideChar(CP_UTF8, 0, temp_str, -1, unicode_str, length); // UTF-8 -> Unicode
				str += unicode_str;
			}
			str.Replace(L"\n", L"\r\n"); // 줄바꿈 세팅

			SetDlgItemText(IDC_NOTE_EDIT, str);
			fclose(p_file);
		}
	}
}


void CNotepadSampleDlg::OnBnClickedSaveBtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
