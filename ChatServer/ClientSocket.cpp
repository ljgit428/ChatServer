#include "stdafx.h"
#include "ClientSocket.h"
#include "ChatServerDlg.h"
#include "ChatServer.h"

CClientSocket::CClientSocket()
{
}


CClientSocket::~CClientSocket()
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	Command cmd;
	Receive(&cmd, sizeof(cmd));

	CString strIPAddress;
	UINT uPort;

	CChatServerDlg* pMainDlg = (CChatServerDlg*)AfxGetMainWnd();


	switch (cmd.cmd) {
	case LOGIN:
	{
		GetPeerName(strIPAddress,uPort);

		wchar_t szUsername[30] = {0};
		Receive(szUsername, sizeof(szUsername));

		pMainDlg->m_list.InsertItem(0,szUsername);
		pMainDlg->m_list.SetItemText(0, 1, strIPAddress);

		CString strPort;
		strPort.Format(_T("%d"),uPort);
		pMainDlg->m_list.SetItemText(0, 2, strPort);
	}
		break;
	case SENDNEWMESSAGE:{
				  wchar_t newmessage[500] = { 0 };
				  Receive(newmessage, sizeof(newmessage));

				  Command cmd;
				  cmd.cmd = POSTNEWMESSAGE;
				  cmd.nDataSize = sizeof(newmessage) * 2;

				  theApp.m_pClientSocket->Send(&cmd, sizeof(cmd));

				  theApp.m_pClientSocket->Send(newmessage, sizeof(newmessage) * 2);
	}
		break;
	}
	CSocket::OnReceive(nErrorCode);
}
