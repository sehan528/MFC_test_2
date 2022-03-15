
// MFCApplication2View.cpp: CMFCApplication2View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <cstdlib>
#include <ctime>


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CMFCApplication2View 생성/소멸

CMFCApplication2View::CMFCApplication2View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned)time(NULL));
	count = 0;
	//p = 0;
}

CMFCApplication2View::~CMFCApplication2View()
{
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View 그리기

void CMFCApplication2View::OnDraw(CDC* /*pDC*/)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	// vector property 봐야 될듯. + 옵티마이징 (상자채우기알고맂므)
	// 여기에 더블형 정의 후, 매 카운트 개수 마다 평균값이 달라지는 것을 결정.
	double checkcount = 0;

	CClientDC dc(this);
	// CBrush 기능으로 Red, Blue 정의할 수 있음. 
	CBrush brush1, brush2;
	brush1.CreateSolidBrush(RGB(0, 0, 255)); // Blue
	brush2.CreateSolidBrush(RGB(255, 0, 0)); // Red
	
	



	for (int i = 0; i < count; i++) {
		dc.Ellipse(p[i].x - r[i], p[i].y - r[i], p[i].x + r[i], p[i].y + r[i]);
	}
	// str.format과 textout을 이용하여 결과값 출력 시킬 수 있음.
}



// CMFCApplication2View 인쇄

BOOL CMFCApplication2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMFCApplication2View 진단

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View 메시지 처리기


void CMFCApplication2View::OnLButtonDown(UINT nFlags, CPoint point) {
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	p[count] = point;
	r[count] = rand() % 46 + 5;
	count++;
	Invalidate();

	//CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication2View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*
	교수님은 switch(nChar)를 input으로 받아 VK_F3, Vk_F4 의 경우를 모두 할당시킴.
	F3이나 F4를 누르면 크기가 변하는? 구글링 해봐야 할듯.
	*/
	
	if (nChar == VK_F3) {
		for (int i = 0; i < count; i++) {
			r[i] = r[i] * 0.9;
		}
		Invalidate();
	}


	if (nChar == VK_F4) {
		for (int i = 0; i < count; i++) {
			r[i] = r[i] * 1.1;
		}
		Invalidate();
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

