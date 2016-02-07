#include "OGLWindow.h"
#include "ViewerState.h"

#include "Resource.h"

#include <cctype>
#include <iostream>
#include <gl/GL.h>

const wchar_t* OGLWindow::WINDOW_TITLE = L"3D Model Viewer";

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height) {
	initWindow(hInstance, width, height);

	gui = GUI::createContext(width, height);
	gui->setState(new ViewerState("ViewerState", gui, modelViewer));
}

OGLWindow::~OGLWindow() {
	destroyOGLContext();
}

HGLRC OGLWindow::createOpenGLContext(HDC hdc) {
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd))
	 || !SetPixelFormat(hdc, pixelformat, &pfd)
	 || !(hglrc = wglCreateContext(hdc))
	 || !wglMakeCurrent(hdc, hglrc)) {
		return 0;
	}
	return hglrc;
}

void OGLWindow::destroyOGLWindow() {
	destroyOGLContext();
	DestroyWindow(m_hwnd);

	m_hwnd = NULL;
	m_hdc = NULL;
}

BOOL OGLWindow::destroyOGLContext() {
	if (m_hglrc) {
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_hglrc);
		m_hglrc = NULL;
	}
	return ReleaseDC(m_hwnd, m_hdc);
}

BOOL OGLWindow::initWindow(HINSTANCE hInstance, int width, int height) {
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
							OGLWindow::WINDOW_TITLE, OGLWindow::WINDOW_TITLE, WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
							0, 0, width, height, NULL, NULL, hInstance, NULL);

	if (!m_hwnd) {
		return FALSE;
	}

	m_hdc = GetDC(m_hwnd);

	if (!(m_hglrc = createOpenGLContext(m_hdc))) {
		return FALSE;
	}

	m_width = width;
	m_height = height;
	initOGLState();

	return TRUE;
}

void OGLWindow::setVisible(BOOL visible) {
	ShowWindow(m_hwnd, visible? SW_SHOW : SW_HIDE);
}

void OGLWindow::transform3D() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-fW, fW, -fH, fH, 1.0f, 400.0f);

	// glMatrixMode(GL_MODELVIEW);
	// glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void OGLWindow::transform2D() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-oW, oW, -oH, oH, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glDisable(GL_LIGHTING);
}

void OGLWindow::render() {
	gui->update();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	transform3D();
	modelViewer.render();

	transform2D();
	gui->render();
	glFlush();
	SwapBuffers(m_hdc);
}

void OGLWindow::calculatePerspectives() {
	// Based on example code found at http://nehe.gamedev.net/article/replacement_for_gluperspective/21002/
	// Makes life easier without depending on glu!
	fH = (float) tan(45.0f / 360 * 3.1415926535897932384626433832795);
	fW = fH * ((float) m_width / (float) m_height);
	oW = 0.5f * (float) m_width;
	oH = 0.5f * (float) m_height;
}

void OGLWindow::resize(int width, int height) {
	initOGLState();
}

void OGLWindow::initOGLState() {
	glViewport(0, 0, m_width, m_height);
	calculatePerspectives();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

BOOL OGLWindow::processMouse(MouseButton button, MouseAction action, int x, int y) {
	if (button == MIDDLE) {
		ViewerState* viewerState = static_cast<ViewerState*>(gui->getState());

		viewerState->scrollZ(action == PRESSED);
		return true;
	}
	return gui->processMouseAction(button, action, x, y);
}

BOOL OGLWindow::processKey(KeyState state, char character, UINT msg) {
	if (msg == WM_CHAR) {
		return gui->processCharacter(state, character);
	}
	if (character < 0 || !std::isalnum(character)) {
		return gui->processKey(state, character);
	}
	return true;
}
