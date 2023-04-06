package com.example.armcontrollerapp;

import android.content.Intent
import android.content.pm.ActivityInfo
import android.net.sip.SipErrorCode.TIME_OUT
import android.os.Bundle
import android.view.View
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import com.google.android.material.slider.RangeSlider
import com.google.android.material.slider.Slider
import kotlinx.coroutines.CoroutineScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.withTimeoutOrNull
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
        val url = URL(String.format("%s/posts?mode=%s&arm1=%.2f&arm2=%.2f&endeffector=%.2f", BASE_URL, mode, arm1Angle, arm2Angle, endEffectorAngle))
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
        val EndEffector = findViewById<Slider>(R.id.EndEffector)
        val arm1Text = findViewById<TextView>(R.id.arm1Text)
        val arm2Text = findViewById<TextView>(R.id.arm2Text)
        val endEffectorText = findViewById<TextView>(R.id.endEffectorText)

        btnReset.setOnClickListener{
            arm1Angle = 0.0
            arm2Angle = 0.0
            endEffectorAngle = 0.0
            arm1Text.text = String.format("Arm1: %.1f", arm1Angle)
            arm2Text.text = String.format("Arm2: %.1f", arm2Angle)
            endEffectorText.text = String.format("End Effector: %.1f", endEffectorAngle)
            alert("Reset successfully to (0,0,0)")
            Arm1.value = arm1Angle.toFloat()
            Arm2.value = arm2Angle.toFloat()
            EndEffector.value = endEffectorAngle.toFloat()
            CoroutineScope(Dispatchers.IO).launch{
                sendDataToESP()
            }
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

        EndEffector.addOnChangeListener(object: Slider.OnChangeListener{
            override fun onValueChange(slider: Slider, value: Float, fromUser: Boolean) {
                endEffectorAngle = slider.value.toDouble()
                endEffectorText.text = String.format("End Effector: %.1f", endEffectorAngle)
                CoroutineScope(Dispatchers.IO).launch{
                    sendDataToESP()
                }
            }
        })

        val spinner = findViewById<Spinner>(R.id.selectMode)
        val modes = resources.getStringArray(R.array.mode)
        var adapter: ArrayAdapter<CharSequence> = ArrayAdapter.createFromResource(this, R.array.mode, android.R.layout.simple_spinner_item)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_item)

        spinner.setAdapter(adapter)
        spinner.setSelection(2)

        spinner.onItemSelectedListener = object :
            AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>,
                                        view: View, position: Int, id: Long) {
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

            override fun onNothingSelected(parent: AdapterView<*>) {
                startActivity(intent)
            }
        }


    }
}  