package sodino.open.gl

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import sodino.open.gl.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity(), View.OnClickListener {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "Hello World, myOpenGL."
        binding.btnDrawLineSwitch.setOnClickListener(this)
        setDrawLineText(false)
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