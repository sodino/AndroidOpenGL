package sodino.open.gl

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import sodino.open.gl.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = "Hello World, myOpenGL."
    }



}