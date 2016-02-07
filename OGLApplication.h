#pragma once

#include <Windows.h>

class OGLWindow;

class OGLApplication {
	private:
		OGLWindow* m_appwnd;
		
		BOOL m_terminate;
		static OGLApplication* s_oglapp;

		OGLApplication();
		virtual ~OGLApplication();
		void createWindow(int width, int height );
		BOOL registerClass(HINSTANCE hinst);

	public:
		HINSTANCE m_hInst;

		static OGLApplication* createApplication(HINSTANCE hInst);
		static void	destroyApplication();
		static OGLApplication* getApplication();

		int run();
		void kill();

		inline OGLWindow* getWindow() {
			return m_appwnd;
		}

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
};