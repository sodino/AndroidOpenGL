package sodino.open.gl

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet

class GL3SurfaceView : GLSurfaceView {
    constructor(context : Context) : super(context) {}
    constructor(context : Context, attr : AttributeSet) : super(context, attr) {}

    private val renderer : GL3Renderer
    init {
        setEGLContextClientVersion(3)
        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 2.0 or later backwards-compatible versions.
        setEGLConfigChooser(8, 8, 8, 0, 16, 0)
        renderer = GL3Renderer()
        setRenderer(renderer)
    }
}