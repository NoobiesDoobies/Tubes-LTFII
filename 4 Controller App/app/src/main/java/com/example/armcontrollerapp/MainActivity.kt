package com.example.armcontrollerapp

import android.content.Intent
import android.content.pm.ActivityInfo
import android.os.Bundle
import android.os.Handler
import android.view.View
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import com.example.armcontrollerapp.Globals.Companion.BASE_URL
import com.example.armcontrollerapp.Globals.Companion.x
import com.example.armcontrollerapp.Globals.Companion.y
import com.example.armcontrollerapp.Globals.Companion.z
import com.example.armcontrollerapp.Globals.Companion.zIncrement

import kotlinx.coroutines.*
import kotlinx.coroutines.Dispatchers.IO
import java.io.IOException
import java.net.HttpURLConnection
import java.net.URL
import kotlin.math.cos
import kotlin.math.sin

class MainActivity : AppCompatActivity() {
    val TIME_OUT_PING = 1500L
    val TIME_OUT = 1500L
    val DELAY_PING_MS = 1000L
    private var xIncrement: Double = 0.5
    private var yIncrement: Double = 0.5

    private var mode: String = "Arrows"
    private val handler = Handler()
    private var runnable: Runnable? = null


    public suspend fun sendPing(): Unit{
        val url = URL(BASE_URL)
        val job = withTimeoutOrNull(TIME_OUT_PING){
            with(url.openConnection() as HttpURLConnection) {
                requestMethod = "GET"  // optional default is GET

                println("\nPING TO : $url; Response Code : $responseCode")

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
    public fun pingServer(): Unit{
        runnable = object : Runnable {
            override fun run() {
                CoroutineScope(IO).launch{
                    sendPing()
                }
                // Schedule the task to run again after a delay
                handler.postDelayed(this, DELAY_PING_MS)
            }
        }
        handler.post(runnable!!)
    }

    public suspend fun sendDataToESP(): Unit{
        try{
            val url = URL(String.format("%s/posts?mode=%s&x=%.2f&y=%.2f&z=%d", BASE_URL, mode, x, y, z))
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
        }catch (e: IOException) {
            println("IOException occurred: ${e.message}")
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

//        pingServer()

        val btnLeft = findViewById<Button>(R.id.btnLeft)
        val btnRight = findViewById<Button>(R.id.btnRight)
        val btnUp = findViewById<Button>(R.id.btnUp)
        val btnDown = findViewById<Button>(R.id.btnDown)
        val btnUpRight = findViewById<Button>(R.id.btnUpRight)
        val btnUpLeft = findViewById<Button>(R.id.btnUpLeft)
        val btnDownRight = findViewById<Button>(R.id.btnDownRight)
        val btnDownLeft = findViewById<Button>(R.id.btnDownLeft)

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

        xText.text = String.format("x: %.1f", x)
        yText.text = String.format("y: %.1f", y)
        zText.text = String.format("z: %d", z)

        spinner.setAdapter(adapter)

        spinner.onItemSelectedListener = object :
            AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>,
                                        view: View?, position: Int, id: Long) {
                if(view != null){
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


            }

            override fun onNothingSelected(parent: AdapterView<*>) {
                // write code to perform some action
            }
        }

        btnLeft.setOnClickListener{
            x-=xIncrement
            x = x.coerceIn(0.0, 30.0)
            xText.text = String.format("x: %.1f", x)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnRight.setOnClickListener{
            x+=xIncrement
            x = x.coerceIn(0.0, 30.0)
            xText.text = String.format("x: %.1f", x)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnUp.setOnClickListener{
            y+=yIncrement
            y = y.coerceIn(0.0, 30.0)
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnDown.setOnClickListener{
            y-=yIncrement
            y = y.coerceIn(0.0, 30.0)
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }

        }

        btnUpRight.setOnClickListener{
            x+=xIncrement
            x = x.coerceIn(0.0, 30.0)
            y+=yIncrement
            y = y.coerceIn(0.0, 30.0)
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }
        btnUpLeft.setOnClickListener{
            x-=xIncrement
            x = x.coerceIn(0.0, 30.0)
            y+=yIncrement
            y = y.coerceIn(0.0, 30.0)
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }
        btnDownLeft.setOnClickListener{
            x-=xIncrement
            x = x.coerceIn(0.0, 30.0)
            y-=yIncrement
            y = y.coerceIn(0.0, 30.0)
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }
        btnDownRight.setOnClickListener{
            x+=xIncrement
            x = x.coerceIn(0.0, 30.0)
            y-=yIncrement
            y = y.coerceIn(0.0, 30.0)
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnZPos.setOnClickListener{
            z += zIncrement
            z = z.coerceIn(0, 2)
            zText.text = String.format("z: %d", z)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }

        }

        btnZNeg.setOnClickListener{
            z -= zIncrement
            z = z.coerceIn(0, 2)
            zText.text = String.format("z: %d", z)
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }

        btnCalibrate.setOnClickListener{
            x = 0.0
            y = 30.0
            z = 0
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            zText.text = String.format("z: %d", z)
            alert("Calibrated successfully to (0,0,0)")
            CoroutineScope(IO).launch{
                sendDataToESP()
            }
        }
    }


}