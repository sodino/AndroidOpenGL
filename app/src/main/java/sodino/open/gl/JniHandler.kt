package sodino.open.gl

class JniHandler {
    companion object {
        init {
            System.loadLibrary("myOpenGL")
        }
    }


    /**
     * A native method that is implemented by the 'myOpenGL' native library,
     * which is packaged with this application.
     */
    external fun printOpenGLInfos()
    external fun resizeGL(width: Int, height: Int)
    external fun renderGL()
}