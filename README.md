# AndroidOpenGL

## feature/openGL_helloTriangle_legacy
 2021.06.17

legacy way for Triangle Drawing

Learning focus :
*  [app_initGL](app/src/main/cpp/AppOpenGL.cpp#L172-L172) :  
   1. [loadGLShader](app/src/main/cpp/AppOpenGL.cpp#L44-L44)  
       `glCreateShader`  
       `glShaderSource`  
       `glCompileShader`
   2. `glCreateProgram`
   3. `glAttachShader`
   4. `glLinkProgram`
   5. (optional) `glDeleteShader`
* [app_renderTriangle](app/src/main/cpp/AppOpenGL.cpp#L152-L152) :
  1. `glUseProgram`
  2. `glDrawArrays`
* [app_destroyGL](app/src/main/cpp/AppOpenGL.cpp#L198-L198)

The last parameter of `glVertexAttribPointer` has the type of `pointer` just for compatibility.  
In **legacy** OpenGL, specify a data pointer directly without being bound a buffer object,  
because the pointer should not be treated as a byte offset into the buffer.

preview :  
![legacy.drawing.triangle](./preview/hello.triangle.legacy.png)

## feature/openGL_renderClearColor
 2021.06.16
Understand and practise of function `glClearColor` and `glClear`.

preview :  
![renderClearColor.gif](./preview/openGL.renderClearColor.gif)

## feature/print_openGL_infos
 2021.06.16  
print openGL infos by glGetString.   
Only four field values can be read :   
`GL_VERSION` `GL_VENDOR` `GL_RENDERER` `GL_EXTENSIONS`.  
And it makes sense to invoke `glGetString` after `GLSurfaceView` is initialized, otherwise it returns null.  

Both Java(see `GL3Renderer`) and C++(see `printOpenGL.cpp`) implementations are dealt with separately.  

