package sodino.open.gl

import android.opengl.GLSurfaceView
import android.util.Log
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GL3Renderer : GLSurfaceView.Renderer {
    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
        val version = gl.glGetString(GL10.GL_VERSION)
        val vendor = gl.glGetString(GL10.GL_VENDOR)
        val renderer = gl.glGetString(GL10.GL_RENDERER)
        val extensions = gl.glGetString(GL10.GL_EXTENSIONS)
        Log.d("appGL", "version=$version")
        Log.d("appGL", "vendor=$vendor")
        Log.d("appGL", "renderer=$renderer")
        Log.d("appGL", "extensions=$extensions")

//        val jni = JniHandler()
//        jni.printOpenGLInfos()
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
    }

    override fun onDrawFrame(gl: GL10) {
    }
}