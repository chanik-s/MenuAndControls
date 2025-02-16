﻿
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once

#include <string>
#include <functional>
#include <unordered_map>
#include <utility>
#include <vector>

#include "EventListener.h"

// CChildView 창

class CChildView : public CWnd
{

private:
	//CRect m_rect;  // 사각형을 저장하는 멤버 변수
	CPoint m_startPoint;  // 드래그 시작 지점을 저장하는 멤버 변수
	bool m_isDrawingRect;  // 현재 사각형을 그리고 있는지 여부를 나타내는 플래그
	// 새로운 멤버 변수 추가: 직사각형 정보를 저장하는 변수
	//CRect m_drawnRect;   // 그려진 직사각형의 정보를 저장
	// 새로운 멤버 변수 추가: 직사각형 정보를 저장하는 변수
	std::vector<CPoint> startv;   // 그려진 직사각형의 정보를 저장
	std::vector<CPoint > endv;

	std::vector<CRect> v_rect;
	std::vector<std::pair<CPoint,int>> v_circle;
	std::vector<std::pair<CPoint, CPoint> > v_line;
	std::vector<std::pair<CPoint, CPoint> > v_curve;
	std::vector<CRect> v_selarea;

public:
	CChildView();

	enum ToolbarMode {
		kToolbarNone,
		kToolbarSelectArea,
		kToolbarRemoveSelected,
		kToolbarDrawLine,
		kToolbarDrawCurve,
		kToolbarDrawRectangle,
		kToolbarDrawCircle,
	};

	ToolbarMode m_toolbar_mode = kToolbarNone;

public:
	CPoint m_mouse_pos;
	CString m_mouse_event{"None"};
	CString m_current_time;

	UINT m_keyboard = -1;

	// 공 정보
	CPoint m_ball_pos;
	int m_ball_radius = 10;
	CPoint m_ball_velocity{5, -5};

	// 고무벽 정보
	CRect m_wall_rect{CPoint{}, CSize{20, 200}};

	//벽 정보

	void CalculateBall();

public:

	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CChildView();

protected:
	afx_msg void OnPaint();
	afx_msg void OnMyPaint(CDC* dc);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// 새로운 멤버 함수 추가: 직사각형 그리기 함수
	void DrawRectangle(CDC* dc, CRect rect, COLORREF color);

	enum TimerEvent {
		kTimerClock,
		kTimerPhysics,
	};

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	EventListener<TimerEvent> m_timer_event_listeners;

	enum MouseEvent {
		kMouseMove,

		kMouseLButtonDown,
		kMouseLButtonUp,
		kMouseLButtonDblClk,

		kMouseRButtonDown,
		kMouseRButtonUp,
		kMouseRButtonDblClk,

		kMouseMButtonDown,
		kMouseMButtonUp,
		kMouseMButtonDblClk,
	};
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);

	EventListener<MouseEvent, UINT, CPoint> m_mouse_event_listeners;

	afx_msg void OnSelectArea();
	afx_msg void OnUpdateSelectarea(CCmdUI* pCmdUI);
	afx_msg void OnDrawLine();
	afx_msg void OnUpdateDrawLine(CCmdUI* pCmdUI);
	afx_msg void OnRemoveSelected();
	afx_msg void OnDrawRectangle();
	afx_msg void OnUpdateDrawRectangle(CCmdUI* pCmdUI);
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnDrawCurve();
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);

	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	EventListener<UINT, UINT, UINT> m_keyboard_listeners;

	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

