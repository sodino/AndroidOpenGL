package sodino.open.gl

import android.content.res.AssetManager
import android.opengl.GLSurfaceView
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GL3Renderer(
    val assetMgr : AssetManager
) : GLSurfaceView.Renderer {
    private val jni = JniHandler()

    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        val version = gl.glGetString(GL10.GL_VERSION)
        val vendor = gl.glGetString(GL10.GL_VENDOR)
        val renderer = gl.glGetString(GL10.GL_RENDERER)
        val extensions = gl.glGetString(GL10.GL_EXTENSIONS)
        Log.d("appGL", "version=$version")
        Log.d("appGL", "vendor=$vendor")
        Log.d("appGL", "renderer=$renderer")
        Log.d("appGL", "extensions=$extensions")

        jni.printOpenGLInfos()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        Log.d("appGL", "Renderer : onSurfaceChanged w=$width, h=$height")
        jni.initGL(assetMgr)
        jni.resizeGL(width, height)

    }

    override fun onDrawFrame(gl: GL10) {
        jni.renderGL()
    }

    fun destroyGL() {
        jni.destroyGL()
    }

    fun onlyDrawLine(onlyLine : Boolean) {
        jni.onlyDrawLine(onlyLine)
    }
}
