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
        renderer = GL3Renderer()
        setRenderer(renderer)
    }
}