package sodino.open.gl

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.MainScope
import kotlinx.coroutines.launch
import sodino.open.gl.databinding.ActivityMainBinding
import java.io.File
import java.io.FileOutputStream
import java.io.IOException

class MainActivity
    : AppCompatActivity(),
    CoroutineScope by MainScope(),
    View.OnClickListener {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "Hello World, myOpenGL."
        binding.btnDrawLineSwitch.setOnClickListener(this)
        setDrawLineText(false)

        copyAsset2Storage()
    }

    private fun copyAsset2Storage() = launch(Dispatchers.IO) {
        val fDest = File(cacheDir, "wall.jpg")
        Log.d("appGL", "wall.jpg path=${fDest.absolutePath}")
        if (fDest.exists()) {
            return@launch
        }
        try {
            val fParent = fDest.parentFile
            if (!fParent.exists()) {
                fDest.mkdirs()
            }
            if (fDest.exists()) {
                fDest.delete()
            }
            fDest.createNewFile()

            val inputStream = assets.open("wall.jpg")
            val fos = FileOutputStream(fDest)

            val buffer = ByteArray(1024 * 8)
            var read = 0
            while(true) {
                read = inputStream.read(buffer)
                if (read < 0) {
                    break
                }
                fos.write(buffer, 0, read)
                fos.flush()
            }
            Log.d("appGL", "write successfully, path=${fDest.absolutePath}")

            inputStream.close()
            fos.close()
        } catch(e : IOException) {
            fDest.delete()
            e.printStackTrace()
        }
    }

    private fun setDrawLineText(onlyLine : Boolean = false) {
        binding.btnDrawLineSwitch.text = "OnlyLine : ${onlyLine.toString().uppercase()}"
        binding.btnDrawLineSwitch.setTag(R.id.surfaceView, false)
    }

    override fun onClick(v: View) {
        when(v.id) {
            R.id.btnDrawLineSwitch -> {
                val view = binding.surfaceView
                var now = false
                val tmp = view.getTag(R.id.surfaceView)
                if (tmp is Boolean) {
                    now = tmp
                }

                val next = !now
                view.setTag(R.id.surfaceView, next)
                view.onlyDrawLine(next)
                setDrawLineText(next)
            }
        }
    }


}