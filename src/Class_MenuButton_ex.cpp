#include "Class_MenuButton_ex.h"

void _menubutton_regsiter()
{
	Ex_ObjRegister(L"MenuButton", EOS_VISIBLE, EOS_EX_FOCUSABLE, DT_CENTER | DT_VCENTER | DT_SINGLELINE, 0, 0, 0, _menubutton_proc);
}

LRESULT CALLBACK _menubutton_menu_proc(HWND hWnd, HEXDUI hExDUI, INT uMsg, WPARAM wParam, LPARAM lParam, LRESULT* lpResult)
{
	menu_s* lpMenuParams;
	wnd_s* pWnd;
	INT nError = 0;
	POINT point = { 0 };
	obj_s* pObj;
	obj_s* pObj2;
	HWND currentWnd;
	HEXOBJ hObj = 0;
	
	if (uMsg == MBM_SELECTITEM && LODWORD(wParam) == -1)
	{
		if (_handle_validate(hExDUI, HT_DUI, (LPVOID*)&pWnd, &nError))
		{
			
			lpMenuParams = pWnd->lpMenuParams_;
			if (!lpMenuParams)
			{
				return 0;
			}
			GetCursorPos(&point);
			currentWnd = WindowFromPoint(point);
			if ((HWND)lpMenuParams->nReserved_ != currentWnd)
			{
				return 0;
			}
			ScreenToClient(currentWnd, &point);
			hObj = Ex_DUIGetObjFromPoint((EXHANDLE)currentWnd, point.x, point.y);

			if (!hObj || hObj == lpMenuParams->handle_)
			{
				return 0;
			}

			if (!_handle_validate(hObj, HT_OBJECT, (LPVOID*)&pObj, &nError))
			{
				return 0;
			}

			if (pObj->pCls_->atomName != ATOM_MENUBUTTON)
			{
				return 0;
			}
			nError = 0;

			if (!_handle_validate(lpMenuParams->handle_, HT_OBJECT, (LPVOID*)&pObj2, &nError))
			{
				return 0;
			}

			if (pObj->objParent_ == pObj2->objParent_ && pObj->dwUserData_ == pObj2->dwUserData_)
			{

				EndMenu();
				
				_obj_postmessage(currentWnd, hObj, pObj, MBM_DOWNITEM, (size_t)pObj->dwUserData_, 0, 0);
			}
		}
	}
	return 0;
}

void _menubutton_paint(HEXOBJ hObj, obj_s* pObj)
{
	EX_PAINTSTRUCT ps{ 0 };
	INT fontColor = 0;
	INT bkgColor = 0;
	if (Ex_ObjBeginPaint(hObj, &ps))
	{
		if (FLAGS_CHECK(pObj->dwState_, STATE_DOWN) || FLAGS_CHECK(pObj->dwState_, STATE_CHECKED))
		{
			fontColor = _obj_getcolor(pObj, COLOR_EX_TEXT_DOWN);
		}
		else if (FLAGS_CHECK(pObj->dwState_, STATE_HOVER))
		{
			fontColor = _obj_getcolor(pObj, COLOR_EX_TEXT_HOVER);
		}
		else {
			fontColor = _obj_getcolor(pObj, COLOR_EX_TEXT_NORMAL);
		}

		bkgColor = _obj_getcolor(pObj, COLOR_EX_BACKGROUND);

		if (bkgColor)
		{
			_canvas_clear(ps.hCanvas, bkgColor);
		}
		_canvas_drawtext(ps.hCanvas, pObj->hFont_, fontColor, pObj->pstrTitle_, -1, ps.dwTextFormat, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right + ps.rcPaint.left, ps.rcPaint.bottom + ps.rcPaint.top);
		Ex_ObjEndPaint(hObj, &ps);
	}
}

LRESULT CALLBACK _menubutton_proc(HWND hWnd, HEXOBJ hObj, INT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT lpRect = { 0 };
	INT nError = 0;
	obj_s* pObj = nullptr;
	if (_handle_validate(hObj, HT_OBJECT, (LPVOID*)&pObj, &nError))
	{
		
		if (uMsg == WM_PAINT)
		{
			_menubutton_paint(hObj, pObj);
			
		}
		else if (uMsg == WM_MOUSEHOVER)
		{
			_obj_setuistate(pObj, STATE_HOVER, FALSE, NULL, TRUE, NULL);
		}
		else if (uMsg == WM_MOUSELEAVE)
		{
			_obj_setuistate(pObj, STATE_HOVER, TRUE, NULL, TRUE, NULL);
		}
		else if (uMsg == WM_LBUTTONDOWN)
		{
			_obj_setuistate(pObj, STATE_DOWN, FALSE, NULL, TRUE, NULL);
			_obj_postmessage(hWnd, hObj, pObj, MBM_DOWNITEM, (size_t)pObj->dwUserData_, pObj->lParam_, NULL);
		}
		else if (uMsg == WM_LBUTTONUP)
		{
			_obj_setuistate(pObj, STATE_DOWN, TRUE, NULL, TRUE, NULL);
		}
		/*else if (uMsg == WM_ERASEBKGND)
		{
			
			return 1;
		}*/
		
		else if (uMsg == MBM_DOWNITEM && wParam == (size_t)pObj->dwUserData_)
		{
			
			if (!lParam)
			{
				lParam = pObj->lParam_;
			}
			
			if (IsMenu((HMENU)lParam) && !FLAGS_CHECK(pObj->dwState_, STATE_CHECKED))
			{
				
				EndMenu();
				_obj_setuistate(pObj, STATE_CHECKED , FALSE, NULL, FALSE, NULL);
				if (!_obj_dispatchnotify(hWnd, pObj, hObj, pObj->id_, MBN_POPUP, wParam, lParam))
				{
					GetWindowRect(hWnd, &lpRect);
					Ex_TrackPopupMenu((HMENU)lParam, 0, lpRect.left + pObj->w_left_, lpRect.top + pObj->w_bottom_, (size_t)hWnd, hObj, NULL, _menubutton_menu_proc, 0);
				}
				_obj_setuistate(pObj, STATE_CHECKED | STATE_DOWN, TRUE, NULL, TRUE, NULL);
			}
		}
	}
	return Ex_ObjDefProc(hWnd, hObj, uMsg, wParam, lParam);
}
