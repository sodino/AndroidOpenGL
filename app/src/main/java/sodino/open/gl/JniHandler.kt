package sodino.open.gl

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
    external fun initGL()
    external fun resizeGL(width: Int, height: Int)
    external fun renderGL()
    external fun destroyGL()
    external fun onlyDrawLine(onlyLine : Boolean)
}