package com.example.armcontrollerapp;

import android.content.Intent
import android.content.pm.ActivityInfo
import android.net.sip.SipErrorCode.TIME_OUT
import android.os.Bundle
import android.view.View
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import com.example.armcontrollerapp.Globals.Companion.calibrate
import com.example.armcontrollerapp.Globals.Companion.sliderRange
import com.example.armcontrollerapp.Globals.Companion.x
import com.example.armcontrollerapp.Globals.Companion.y
import com.example.armcontrollerapp.Globals.Companion.z
import com.example.armcontrollerapp.Globals.Companion.zIncrement
import com.example.armcontrollerapp.Globals.Companion.zLowerLimit
import com.example.armcontrollerapp.Globals.Companion.zUpperLimit
import com.google.android.material.slider.RangeSlider
import com.google.android.material.slider.Slider
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withTimeoutOrNull
import org.w3c.dom.Text
import java.lang.Math.abs
import java.net.HttpURLConnection
import java.net.URL

class SliderMode : AppCompatActivity() {
    var arm1Angle: Double = 0.0
    var arm2Angle: Double = 0.0
    var endEffectorAngle: Double = 0.0
    private var BASE_URL: String = "http://192.168.4.1"
    var mode: String = "Slider"
    val TIME_OUT = 1000L
    public suspend fun sendDataToESP(): Unit{
        val url = URL(String.format("%s/posts?mode=%s&arm1=%.2f&arm2=%.2f&z=%d&calibrate=%d", BASE_URL, mode, arm1Angle, arm2Angle, z, calibrate))
        calibrate = 0
        val job = withTimeoutOrNull(TIME_OUT){
            with(url.openConnection() as HttpURLConnection) {
                requestMethod = "GET"  // optional default is GET

                println("\nSent 'GET' request to URL : $url; Response Code : $responseCode")

                inputStream.bufferedReader().use {
                    it.lines().forEach { line ->
                        println(line)
                    }
                }
            }
        }
        if(job == null){
            val cancelMessage = "Job took longer than $TIME_OUT"
            println("debug: $cancelMessage")
        }

    }

    fun alert(message: String) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT)
            .show()
    }


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.slider_layout)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE

        val btnReset = findViewById<Button>(R.id.btnReset)
        val Arm1 = findViewById<Slider>(R.id.Arm1)
        val Arm2 = findViewById<Slider>(R.id.Arm2)
        val sliderRangeSlider = findViewById<Slider>(R.id.sliderRange)
        val btnZPos = findViewById<Button>(R.id.btnZPos)
        val btnZNeg = findViewById<Button>(R.id.btnZNeg)
        val arm1Text = findViewById<TextView>(R.id.arm1Text)
        val arm2Text = findViewById<TextView>(R.id.arm2Text)
        val endEffectorText = findViewById<TextView>(R.id.endEffectorText)
        val sliderRangeText = findViewById<TextView>(R.id.sliderRangeText)

        Arm1.valueFrom = -sliderRange
        Arm1.valueTo = sliderRange
        Arm2.valueFrom = -sliderRange
        Arm2.valueTo = sliderRange
        sliderRangeSlider.value = sliderRange
        sliderRangeText.text = String.format("Range: -%.1f to %.1f", sliderRange, sliderRange)

        btnReset.setOnClickListener{
            arm1Angle = 0.0
            arm2Angle = 0.0
            endEffectorAngle = 0.0
            arm1Text.text = String.format("Arm1: %.1f", arm1Angle)
            arm2Text.text = String.format("Arm2: %.1f", arm2Angle)
            endEffectorText.text = String.format("End Effector: %d", z)
            alert("Reset successfully to (0,0,0)")
            Arm1.value = arm1Angle.toFloat()
            Arm2.value = arm2Angle.toFloat()

            x = 0.0
            y = 30.0
            z = 0
            calibrate = 1
        }

       Arm1.addOnChangeListener(object: Slider.OnChangeListener{
           override fun onValueChange(slider: Slider, value: Float, fromUser: Boolean) {
               arm1Angle = slider.value.toDouble()
               arm1Text.text = String.format("Arm1: %.1f", arm1Angle)
               CoroutineScope(Dispatchers.IO).launch{
                   sendDataToESP()
               }
           }
       })

        Arm2.addOnChangeListener(object: Slider.OnChangeListener{
            override fun onValueChange(slider: Slider, value: Float, fromUser: Boolean) {
                arm2Angle = slider.value.toDouble()
                arm2Text.text = String.format("Arm2: %.1f", arm2Angle)
                CoroutineScope(Dispatchers.IO).launch{
                    sendDataToESP()
                }
            }
        })

        sliderRangeSlider.addOnChangeListener(object: Slider.OnChangeListener{
            override fun onValueChange(slider: Slider, value: Float, fromUser: Boolean) {
                try {
                    sliderRange = abs(slider.value)
                    sliderRangeText.text = String.format("Range: -%.1f to %.1f", sliderRange, sliderRange)
                    Arm1.valueFrom = -sliderRange
                    Arm1.valueTo = sliderRange
                    Arm2.valueFrom = -sliderRange
                    Arm2.valueTo = sliderRange
                } catch (e: IllegalStateException) {
                    // Handle the exception here
                    if(slider.value < abs(Arm1.value)){
                        slider.value = abs(Arm1.value) + 1F
                    }
                    if(slider.value < abs(Arm2.value)){
                        slider.value = abs(Arm2.value) + 1F
                    }
                    e.printStackTrace()
                }
            }
        })


        btnZPos.setOnClickListener{
            z += zIncrement
            z = z.coerceIn(zLowerLimit, zUpperLimit)
            endEffectorText.text = String.format("End Effector: %d", z)
            CoroutineScope(Dispatchers.IO).launch{
                sendDataToESP()
            }
        }

        btnZNeg.setOnClickListener{
            z -= zIncrement
            z = z.coerceIn(zLowerLimit, zUpperLimit)
            endEffectorText.text = String.format("End Effector: %d", z)
            CoroutineScope(Dispatchers.IO).launch{
                sendDataToESP()
            }
        }

        val spinner = findViewById<Spinner>(R.id.selectMode)
        val modes = resources.getStringArray(R.array.mode)
        var adapter: ArrayAdapter<CharSequence> = ArrayAdapter.createFromResource(this, R.array.mode, android.R.layout.simple_spinner_item)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_item)

        spinner.setAdapter(adapter)
        spinner.setSelection(2)

        spinner.onItemSelectedListener = object :
            AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>,
                                        view: View?, position: Int, id: Long) {
                if(view != null){
                    mode = modes[position]
                    Toast.makeText(this@SliderMode,
                        getString(R.string.selected_mode) + " " +
                                "" + mode, Toast.LENGTH_SHORT).show()
                    when(mode){
                        "JoyStick" -> {
                            val intent = Intent(this@SliderMode, JoyStickMode::class.java)
                            startActivity(intent)
                        }
                        "Arrows" ->{
                            val intent = Intent(this@SliderMode, MainActivity::class.java)
                            startActivity(intent)
                        }
                    }
                }


            }

            override fun onNothingSelected(parent: AdapterView<*>) {
                startActivity(intent)
            }
        }


    }
}  