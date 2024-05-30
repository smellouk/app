#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <stdio.h>

// Function to handle errors
void checkError(const char* msg) {
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf(stderr, "Error %s: %d\n", msg, error);
    }
}

int main() {
    // Initialize EGL
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, 0, 0);

    // Select an EGL configuration
    EGLConfig config;
    EGLint numConfigs;
    EGLint configAttribs[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 24,
        EGL_STENCIL_SIZE, 8,
        EGL_NONE
    };
    eglChooseConfig(display, configAttribs, &config, 1, &numConfigs);

    // Create an EGL rendering context
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, NULL);

    // Create a window surface
    EGLSurface surface = eglCreateWindowSurface(display, config, (EGLNativeWindowType)NULL, NULL);

    // Make the context current
    eglMakeCurrent(display, surface, surface, context);

    // Set the clear color to blue
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);

    // Clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Swap buffers
    eglSwapBuffers(display, surface);

    // Clean up
    eglDestroySurface(display, surface);
    eglDestroyContext(display, context);
    eglTerminate(display);

    return 0;
}
