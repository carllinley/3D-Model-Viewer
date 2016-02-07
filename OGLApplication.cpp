#include "OGLApplication.h"
#include "OGLWindow.h"
#include "Resource.h"
#include <Windowsx.h>

OGLApplication* OGLApplication::s_oglapp = NULL;

const int WINDOW_SIZE_X = 1024,
		  WINDOW_SIZE_Y = 768;

OGLApplication::OGLApplication() {
	m_appwnd = NULL;
	m_hInst = 0;
	m_terminate = FALSE;
}

OGLApplication::~OGLApplication() {
	if (m_appwnd) {
		delete m_appwnd;
	}
}

BOOL OGLApplication::registerClass(HINSTANCE hinst) {
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= this->WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hinst;
	wcex.hIcon			= LoadIcon(hinst, MAKEINTRESOURCE(IDI_OGLWIN32));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= OGLWindow::WINDOW_TITLE;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	
	if (!RegisterClassEx(&wcex)) {
		return FALSE;
	}
	return TRUE;
}

OGLApplication* OGLApplication::createApplication(HINSTANCE hinst) {
	if (!s_oglapp) {
		s_oglapp = new OGLApplication();

		s_oglapp->m_hInst = hinst;
		s_oglapp->registerClass(hinst);
		s_oglapp->createWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y); // Create an OGLWindow for this application
	}
	return s_oglapp;
}

void OGLApplication::destroyApplication() {
	if (s_oglapp) {
		delete s_oglapp;
	}
}

OGLApplication* OGLApplication::getApplication() {
	return s_oglapp;
}

void OGLApplication::createWindow(int width, int height) {
	if (!m_appwnd) {
		m_appwnd = new OGLWindow(m_hInst, width, height);
		m_appwnd->setVisible(TRUE);
	}
}

int OGLApplication::run() {
	MSG msg;

	while (!m_terminate) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				kill();
			}
			else {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else {
			m_appwnd->render();
		}
	}
	return (int) msg.wParam;
}

void OGLApplication::kill() {
	m_terminate = TRUE;
}

LRESULT CALLBACK OGLApplication::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch(msg) {
		case WM_SIZE:
			s_oglapp->getWindow()->resize(LOWORD(lparam), HIWORD(lparam));
		break;

		case WM_CLOSE:
			s_oglapp->getWindow()->destroyOGLWindow();
		break;

		case WM_MOUSEWHEEL:
			s_oglapp->getWindow()->processMouse(MIDDLE, GET_WHEEL_DELTA_WPARAM(wparam) < 0 ? PRESSED : RELEASED, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

		case WM_MOUSEMOVE:
			s_oglapp->getWindow()->processMouse(NA, MOVED, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

		case WM_LBUTTONUP:
			s_oglapp->getWindow()->processMouse(LEFT, RELEASED, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

		case WM_LBUTTONDOWN:
			s_oglapp->getWindow()->processMouse(LEFT, PRESSED, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

		case WM_RBUTTONUP:
			s_oglapp->getWindow()->processMouse(RIGHT, RELEASED, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

		case WM_RBUTTONDOWN:
			s_oglapp->getWindow()->processMouse(RIGHT, PRESSED, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
		break;

		case WM_KEYDOWN:
		case WM_CHAR:
			s_oglapp->getWindow()->processKey(DOWN, (char) wparam, msg);
		break;

		case WM_KEYUP:
			s_oglapp->getWindow()->processKey(UP, (char) wparam, msg);
		break;

		case WM_DESTROY:
			PostQuitMessage(0);
		break;

		default:
			return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	return 0;
}