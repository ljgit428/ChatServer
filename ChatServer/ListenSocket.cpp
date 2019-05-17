#include "stdafx.h"
#include "ListenSocket.h"
#include "ChatServerDlg.h"

CListenSocket::CListenSocket()
{
}


CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类

	((CChatServerDlg*)AfxGetMainWnd())->OnAccept();

	CSocket::OnAccept(nErrorCode);
}
