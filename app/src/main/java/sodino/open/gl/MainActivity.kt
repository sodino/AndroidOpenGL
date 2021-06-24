package sodino.open.gl

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.SeekBar
import sodino.open.gl.databinding.ActivityMainBinding

class MainActivity :
    AppCompatActivity(),
    View.OnClickListener,
    SeekBar.OnSeekBarChangeListener {

    private lateinit var binding: ActivityMainBinding

    private val jniHandler by lazy {
        binding.surfaceView.jniHandler
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "Hello World, myOpenGL."
        binding.btnDrawLineSwitch.setOnClickListener(this)
        setDrawLineText(false)

        binding.seekBarPitch.setOnSeekBarChangeListener(this)
        binding.seekBarYaw.setOnSeekBarChangeListener(this)
        binding.seekBarRoll.setOnSeekBarChangeListener(this)
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

    override fun onProgressChanged(seekBar: SeekBar, progress: Int, fromUser: Boolean) {
        if (!fromUser) {
            // only handle user actions
            return
        }

        if (seekBar == binding.seekBarPitch) {
            binding.txtPitch.text = "Angle of Pitch : ${progress}º"
            jniHandler.setPitchAngle(progress)
        } else if (seekBar == binding.seekBarYaw) {
            binding.txtYaw.text = "Angle of Yaw : ${progress}º"
            jniHandler.setYawAngle(progress)
        } else if (seekBar == binding.seekBarRoll) {
            binding.txtYaw.text = "Angle of Roll : ${progress}º"
            jniHandler.setRollAngle(progress)
        }
    }

    override fun onStartTrackingTouch(seekBar: SeekBar) {
    }

    override fun onStopTrackingTouch(seekBar: SeekBar) {
    }


}