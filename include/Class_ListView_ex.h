#pragma once
#include "help_ex.h"

struct listview_s
{
	int width_item_;//项目宽度
	int height_item_;
	int width_split_;//间隔宽度
	int height_split_;
	int width_spec_;//特殊项目宽度
	int height_spec_;
	int width_view_;//项目总宽度
	int height_view_;
	int count_selects_;//选中项目数
	int count_items_;//项目总数
	int count_view_;//可视总数量
	int count_view_h_;//可视横向数量
	int count_view_v_; //可视纵向数量
	int index_select_;//当前选中
	int index_mouse_;//热点项目
	int index_start_;
	int index_end_;
	int index_track_start_;
	int index_track_end_;
	int nHittest_;
	int nOffsetX_;
	int nOffsetY_;
	void* lpItems_;
};

void _ListView_regsiter();
void _lv_updatesbvalue(HEXOBJ hObj, obj_s* pObj, listview_s* pOwner, RECT* lpRcClient);
void _lv_updateviewindex(HEXOBJ hObj, obj_s* pObj, listview_s* pOwner, bool bHView, RECT* lpRcClient);
bool _lv_checkitem(listview_s* pOwner, int iItem);
bool _lv_checkitem_view(listview_s* pOwner, int iItem);
void _lv_rectfromiitem(obj_s* pObj, listview_s* pOwner, int iItem, bool bHView, RECT* rcItem);
void _lv_lprectfromiitem(obj_s* pObj, listview_s* pOwner, int iItem, bool bHView, RECT* lpRc);
int _lv_itemfrompos(obj_s* pObj, listview_s* pOwner, int x, int y, int* offsetPosX, int* offsetPosY);
int _lv_getitemstate(void* lpItems, int iItem);
void _lv_setitemstate(void* lpItems, int iItem, int dwState, bool bRemove);
bool _lv_queryitemstate(void* lpItems, int iItem, int dwState);
void _lv_getsbvalue(obj_s* pObj, listview_s* pOwner, bool bHSB, HEXOBJ* hSB, int* oPos, int* nLine, int* nPage, int* nView);
int _lv_checkpos(int nPos, int nView, int nPage);
void _lv_redrawitem(obj_s* pObj, listview_s* pOwner, int iItem);
void _lv_item_changestate(HWND hWnd, HEXOBJ hObj, obj_s* pObj, listview_s* pOwner, void* lpItems, int iItem, int state, bool bRemove, int nEvent, WPARAM wParam, LPARAM lParam);
size_t _lv_setitemcount(HWND hWnd, HEXOBJ hObj, obj_s* pObj, int nCount, LPARAM lParam);
void _lv_onvscrollbar(HWND hWnd, HEXOBJ hObj, obj_s* pObj, INT uMsg, WPARAM wParam, LPARAM lParam);
size_t _lv_showitem(HWND hWnd, HEXOBJ hObj, obj_s* pObj, int iItem, bool bCheck);
size_t _lv_reselect(HWND hWnd, HEXOBJ hObj, obj_s* pObj, listview_s* pOwner, int iItem, bool bShow);
void _lv_btndown(HWND hWnd, HEXOBJ hObj, obj_s* pObj, INT uMsg, size_t wParram, LPARAM lParam);
void _lv_mouseleave(HWND hWnd, HEXOBJ hObj, obj_s* pObj);
void _lv_mousemove(HWND hWnd, HEXOBJ hObj, obj_s* pObj, WPARAM wParam, LPARAM lParam);
void _lv_drawitem(HWND hWnd, HEXOBJ hObj, obj_s* pObj, listview_s* pOwner, EX_PAINTSTRUCT2 ps, int iItem, RECT rcClip, RECT rcItem);
size_t _lv_paint(HWND hWnd, HEXOBJ hObj, obj_s* pObj);
size_t _lv_size(HWND hWnd, HEXOBJ hObj, obj_s* pObj);
void _lv_lvm_setitemstate(obj_s* pObj, listview_s* pOwner, int iItem, int dwState);
LRESULT CALLBACK _lv_proc(HWND hWnd, HEXOBJ hObj, INT uMsg, WPARAM wParam, LPARAM lParam);