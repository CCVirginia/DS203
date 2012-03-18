#ifndef __WND_H__
#define __WND_H__

#include <Source/HwLayer/Types.h>
#include <Source/HwLayer/Bios.h>
#include <Source/Framework/Classes.h>

class CWnd
{
public:
	class CTimer 
	{
	public:
		CTimer( CWnd* pWnd, ui32 nInterval ) :
			m_pWnd( pWnd ), m_nInterval( nInterval ), m_nLast(0)
		{
		}
		CTimer()
		{
		}

	public:
		CWnd*		m_pWnd;		
		ui32		m_nInterval;
		ui32		m_nLast;
	};

public:
	enum {
		WmPaint = 1,
		WmKey = 2,
		WmTick = 3,

		WsHidden = 0,
		WsVisible = 1,
		WsNoActivate = 2,
		WsNeedRedraw = 4,
		WsModal = 8,
		
		SwShow = 1,
		SwHide = 0
	};

public:
	static CWnd*	m_pTop;					
	static CWnd*	m_pFocus;
	static ui16		m_nInstances;
	static CTimer	m_arrTimers_[16];
	static CArray<CTimer>	m_arrTimers;

	CRect	m_rcClient;						// 16
    CWnd*	m_pParent;						// 4
	CWnd*	m_pFirst;						// 4
	CWnd*	m_pNext;						// 4
	ui16	m_dwFlags;						// 4
	const char* m_pszId;					// 4
	// Total 36 bytes per window

	CWnd();
	CWnd* GetLast();
	CWnd* GetPrev();
	void Destroy();
	void Create( const char* pszId, ui16 dwFlags, const CRect& rc, CWnd* pParent );
	virtual void OnPaint();
	virtual void OnKey(ui16 nKey);
	virtual void OnMessage(CWnd* pSender, ui16 code, ui32 data);
	virtual void WindowMessage(int nMsg, int nParam = 0);
	virtual void OnTimer();
	void SetFocus();
	ui8 HasFocus();
	CWnd* GetActiveWindow();
	void Invalidate();
	void Update();
	void SendMessage(CWnd* pTarget, ui16 code, ui32 data);
	void ShowWindow(ui8 sh);
	void SetTimer(ui32 nInterval);
	void KillTimer();

private:
	CWnd* _GetNextActiveWindow();
	CWnd* _GetPrevActiveWindow();
	void _UpdateTimers();
};                                 

#endif