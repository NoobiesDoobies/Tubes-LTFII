package com.example.armcontrollerapp

import android.content.Intent
import android.content.pm.ActivityInfo
import android.os.Bundle
import android.view.View
import android.widget.*
import androidx.appcompat.app.AppCompatActivity

import kotlinx.coroutines.*
import kotlinx.coroutines.Dispatchers.IO
import java.net.HttpURLConnection
import java.net.URL

class MainActivity : AppCompatActivity() {
    val TIME_OUT = 1000L
    private var x: Double = 0.0
    private var y: Double = 0.0
    private var z: Double = 0.0
    private var xIncrement: Double = 0.5
    private var yIncrement: Double = 0.7
    private var zIncrement: Double = 0.3

    private var BASE_URL: String = "http://192.168.4.1"
    private var mode: String = "Arrows"

    public suspend fun sendDataToESP(): Unit{
        val url = URL(String.format("%s/posts?mode=%s&x=%.2f&y=%.2f&z=%.2f", BASE_URL, mode, x, y, z))
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
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        val btnLeft = findViewById<Button>(R.id.btnLeft)
        val btnRight = findViewById<Button>(R.id.btnRight)
        val btnUp = findViewById<Button>(R.id.btnUp)
        val btnDown = findViewById<Button>(R.id.btnDown)
        val btnZPos = findViewById<Button>(R.id.btnZPos)
        val btnZNeg = findViewById<Button>(R.id.btnZNeg)
        val btnCalibrate = findViewById<Button>(R.id.calibrate)

        val xText = findViewById<TextView>(R.id.xText)
        val yText = findViewById<TextView>(R.id.yText)
        val zText = findViewById<TextView>(R.id.zText)
        val spinner = findViewById<Spinner>(R.id.selectMode)
        val modes = resources.getStringArray(R.array.mode)
        var adapter: ArrayAdapter<CharSequence> = ArrayAdapter.createFromResource(this, R.array.mode, android.R.layout.simple_spinner_item)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_item)

        spinner.setAdapter(adapter)

        spinner.onItemSelectedListener = object :
            AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>,
                                        view: View, position: Int, id: Long) {
                mode = modes[position]
                Toast.makeText(this@MainActivity,
                    getString(R.string.selected_mode) + " " +
                            "" + mode, Toast.LENGTH_SHORT).show()
                println(mode)
                when(mode){
                    "Slider" -> {
                        val intent = Intent(this@MainActivity, SliderMode::class.java)
                        startActivity(intent)
                    }
                    "JoyStick" ->{
                        val intent = Intent(this@MainActivity, JoyStickMode::class.java)
                        startActivity(intent)
                    }
                }

            }

            override fun onNothingSelected(parent: AdapterView<*>) {
                // write code to perform some action
            }
        }

        btnLeft.setOnClickListener{
            x-=xIncrement
            xText.text = String.format("x: %.1f", x)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnRight.setOnClickListener{
            x+=xIncrement
            xText.text = String.format("x: %.1f", x)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnUp.setOnClickListener{
            y+=yIncrement
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnDown.setOnClickListener{
            y-=yIncrement
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }

        }

        btnZPos.setOnClickListener{
            z += zIncrement
            zText.text = String.format("z: %.1f", z)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }

        }

        btnZNeg.setOnClickListener{
            z -= zIncrement
            zText.text = String.format("z: %.1f", z)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnCalibrate.setOnClickListener{
            x = 0.0
            y = 0.0
            z = 0.0
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            zText.text = String.format("z: %.1f", z)
            alert("Calibrated successfully to (0,0,0)")
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }
    }


}