package sodino.open.gl

import android.content.res.AssetManager

class JniHandler {
    companion object {
        init {
            System.loadLibrary("AppJNI")
        }
    }


    /**
     * A native method that is implemented by the 'myOpenGL' native library,
     * which is packaged with this application.
     */
    external fun printOpenGLInfos()
    external fun initGL(assetMgr : AssetManager, width: Int, height: Int)
    external fun resizeGL(width: Int, height: Int)
    external fun renderGL()
    external fun destroyGL()
    external fun onlyDrawLine(onlyLine : Boolean)

    external fun setPitchAngle(angle : Int)
    external fun setYawAngle(angle : Int)
    external fun setRollAngle(angle : Int)
}