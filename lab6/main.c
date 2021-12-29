#include <windows.h>
#include <gl/gl.h>
#include <math.h>

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

float vert[] = {1,1,0, 1,-1,0, -1,-1,0, -1,1,0};
float xAlfa = 60;
float zAlfa = 0;
POINTFLOAT pos = {0,-5};


float pyramid[] = {0,0,2, 1,1,0, 1,-1,0, -1,-1,0, -1,1,0, 1,1,0};

int width, height;

void AddMenus(HWND hwnd) {

     HMENU hMenubar = CreateMenu();
            HMENU hMenu = CreateMenu();

            AppendMenu(hMenubar, MF_POPUP, (UINT_PTR)hMenu, "Zoom");
            AppendMenu(hMenu, MF_STRING, 1, "+");
            AppendMenu(hMenu, MF_STRING, 2, "-");

            SetMenu(hwnd, hMenubar);
}

void zoom(int zoomIndex) {
    switch(zoomIndex){
    case 1:
        pos.y = ++pos.y;
        break;

        case 2:
        pos.y = --pos.y;
        break;
    }

}

void showWorld() {
    glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vert);
        for(int i = -20; i < 20; i++) {
            for(int j = -20; j < 20; j++){
                glPushMatrix();
                    float dc = ((j+i)*4 % 20) * 0.01;

                    //glColor3f(0.31 + dc, 0.5 + dc, 0.13 + dc);
                    if((i + j)%2 == 0) {
                        glColor3f(0, 0, 0);
                    }else {
                        glColor3f(1, 1, 1);
                    }

                    glTranslatef(i*2, j*2, 0);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
                glPopMatrix();
            }
        }
         glVertexPointer(3, GL_FLOAT, 0, &pyramid);
         glColor3f(1,0,0);
         glDrawArrays(GL_TRIANGLE_FAN , 0,6);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void moveCamera() {
   // if(GetKeyState(VK_UP) < 0) xAlfa = ++xAlfa > 180 ? 180 : xAlfa;
   // if(GetKeyState(VK_DOWN) < 0) xAlfa = --xAlfa < 0 ? 0 : xAlfa;
    //if(GetKeyState(VK_LEFT) < 0) zAlfa = ++zAlfa;
    //if(GetKeyState(VK_RIGHT) < 0) zAlfa = --zAlfa;

    float ugol = -zAlfa / 180 * M_PI;
    float speed = 0;

    if(GetKeyState('W') < 0) {
            speed = 0.1;
            pyramid[1] +=0.1;
            pyramid[4] +=0.1;
            pyramid[7] +=0.1;
            pyramid[10] +=0.1;
            pyramid[13] +=0.1;
            pyramid[16] +=0.1;
    }

    if(GetKeyState('S') < 0) {
            speed = -0.1;
            pyramid[1] -=0.1;
            pyramid[4] -=0.1;
            pyramid[7] -=0.1;
            pyramid[10] -=0.1;
            pyramid[13] -=0.1;
            pyramid[16] -=0.1;
    };
    if(GetKeyState('A') < 0) {
            speed = 0.1; ugol-=M_PI*0.5;
            pyramid[0] -=0.1;
            pyramid[3] -=0.1;
            pyramid[6] -=0.1;
            pyramid[9] -=0.1;
            pyramid[12] -=0.1;
            pyramid[15] -=0.1;
    }

    if(GetKeyState('D') < 0) {
            speed = 0.1; ugol+=M_PI*0.5;
            pyramid[0] +=0.1;
            pyramid[3] +=0.1;
            pyramid[6] +=0.1;
            pyramid[9] +=0.1;
            pyramid[12] +=0.1;
            pyramid[15] +=0.1;
    }

    if(speed !=0) {
        pos.x += sin(ugol) * speed;
        pos.y += cos(ugol) * speed;
    }

    glRotatef(-xAlfa, 1,0,0);
    glRotatef(-zAlfa, 0,0,1);
    glTranslatef(-pos.x, -pos.y, -3);
}


int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          500,
                          500,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);
    glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    glFrustum(-1,1, -1,1, 2,100);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */

            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            glPushMatrix();
                moveCamera();
                showWorld();
            glPopMatrix();

            SwapBuffers(hDC);

            theta += 1.0f;
            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CREATE:
          AddMenus(hwnd);
          break;

        case WM_CLOSE:
            PostQuitMessage(0);
        break;

        case WM_COMMAND:
            zoom(wParam);

            break;

        case WM_SIZE:
            glViewport(0,0, LOWORD(lParam), HIWORD(lParam));

            width = LOWORD(lParam);
            height = HIWORD(lParam);
            //glLoadIdentity();
           // float k = LOWORD(lParam) /  (float)HIWORD(lParam);
         //   glOrtho(-k,k, -1,1, -1,1);

        case WM_DESTROY:
            return 0;

        case WM_KEYDOWN:
        {
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;
            }
        }
        break;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

