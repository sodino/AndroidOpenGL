# AndroidOpenGL


## feature/print_openGL_infos
 2021.06.16  
print openGL infos by glGetString.   
Only four field values can be read :   
`GL_VERSION` `GL_VENDOR` `GL_RENDERER` `GL_EXTENSIONS`.  
And it makes sense to invoke `glGetString` after `GLSurfaceView` is initialized, otherwise it returns null.  

Both Java(see `GL3Renderer`) and C++(see `printOpenGL.cpp`) implementations are dealt with separately.  

