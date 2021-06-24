package sodino.open.gl

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import android.view.SurfaceHolder

class GL3SurfaceView : GLSurfaceView {
    constructor(context : Context) : super(context) {}
    constructor(context : Context, attr : AttributeSet) : super(context, attr) {}

    private val renderer : GL3Renderer
    val jniHandler: JniHandler
    init {
        setEGLContextClientVersion(3)
        // Pick an EGLConfig with RGB8 color, 16-bit depth, no stencil,
        // supporting OpenGL ES 2.0 or later backwards-compatible versions.
        setEGLConfigChooser(8, 8, 8, 0, 16, 0)
        renderer = GL3Renderer(context.assets)
        setRenderer(renderer)

        jniHandler = renderer.jni
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        super.surfaceCreated(holder)
        Log.d("appGL", "SurfaceView : surfaceCreated")
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        super.surfaceChanged(holder, format, w, h)
        Log.d("appGL", "SurfaceView : surfaceChanged w=$w, h=$h")
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
        super.surfaceDestroyed(holder)
        Log.d("appGL", "SurfaceView : surfaceDestroyed")
        renderer.destroyGL()
    }

    fun onlyDrawLine(onlyLine: Boolean) {
        renderer.onlyDrawLine(onlyLine)
    }
}