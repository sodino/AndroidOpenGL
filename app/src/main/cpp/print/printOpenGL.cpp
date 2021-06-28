#include "print/printOpenGL.h"
#include <GLES3/gl3.h>

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error = glGetError()) {
        logD("after %s() glError (0x%x)\n", op, error);
    }
}


// @param : glName : only one of the follow four values can be taken.
//                   GL_VERSION GL_VENDOR GL_RENDERER GL_EXTENSIONS
static void printGLString(const char* name, GLenum glName) {
    // It makes sense to invoke after GLSurfaceView is initialized, otherwise it returns null.
    const char* v = (const char*) glGetString(glName);
    logD("%s=%s", name, v);
    // glGetString() return a pointer to a static string, so MUST NOT 'free' v.
    // free(v);
}

void printOpenGLInfos() {
    printGLString("version", GL_VERSION);
    printGLString("vendor", GL_VENDOR);
    printGLString("renderer", GL_RENDERER);
    printGLString("extensions", GL_EXTENSIONS);
}
