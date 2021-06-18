# AndroidOpenGL


## feature/glsl_in_out
 2021.06.18  
'in' 'out' variable usage :  
OpenGL will link those variables together and then it it possible to send data from vertex shader to fragment shader after linking a program object.  
In this demo, define a `purple` color (mix red and blue) in vertex shader as the input parameter of fragment vertex.


Learning focus :
* Shader Language always begin with a version declaration.
  The default version value is `version 100`.  
  Adding a `\n` as a line separator is necessary.
* Declare an output variable `out vec4 colorFromVertex` in vertex shader,
  and a similar input variable `in vec4 colorFromVertex` in fragment shader with same name and same type.
* `gl_FragColor` is deprecated.  
  The modern way of writing to the output buffers from a fragment shader,  
  is to declare user-defined output variable,  
  such as `out vec4 fragColor` in demo code.

preview :  
The color of <span style="color:purple">triangle</span> will become <span style="color:purple">purple</span>.  
<span style="color:purple"><font size="150">▲</font></span>

## feature/openGL_helloSquare_IBO
 2021.06.18  
IBO/EBO usage : drawing a square composed of two triangles.

Learning focus :
* Specify the unique [4 vertices](app/src/main/cpp/AppOpenGL.cpp#L26-L31) and the [6 indices](app/src/main/cpp/AppOpenGL.cpp#L33-L36) to define two triangle, two of them form a square.
* Create `Index Buffer Object(IBO) / Element Buffer Object(EBO)`
* Bind `IBO/EBO` with `glBindBuffer`, copy [6 indices](app/src/main/cpp/AppOpenGL.cpp#L33-L36) into the buffer with `glBufferData`, specify `GL_ELEMENT_ARRAY_BUFFER` as the buffer type.
* Replace the ~~`glDrawArrays`~~ with `glDrawElements` to indicate we want to render the triangles from an index buffer.
* Remember to delete `IBO/EBO` by invoking `glDeleteBuffers`

preview :  
<img src="./preview/hello.square.IBO.png" alt="drawing" width="500"/>


## feature/openGL_helloTriangle
 2021.06.17

use VAO/VBO to draw triangle

Learning focus :
* generate VAO first then VBO, because any subsequent vertex attribute calls after `glGenVertexArrays` wil be stored inside the VAO
* bind the VAO first, then bind and set vertex buffers(s), and then configure vertex attribute(s). Finally, DON'T forget to unbind : `glBind****(0)`.
* when doing rendering, there's no need to `glUseProgram` and `glBindVertexArray` every time, BUT we'll do so JUST keep things a bit more organized.

  preview :
<img src="./preview/hello.triangle.2mode.png" alt="drawing" width="500"/>

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

