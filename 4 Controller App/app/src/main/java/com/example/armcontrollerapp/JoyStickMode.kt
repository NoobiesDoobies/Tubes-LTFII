package com.example.armcontrollerapp
import android.content.ContentValues.TAG
import android.content.Context
import android.content.Intent
import android.content.pm.ActivityInfo
import android.os.Bundle
import android.os.Handler
import android.util.Log
import android.view.View
import android.view.Window
import android.widget.*
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat

import kotlinx.coroutines.*
import kotlinx.coroutines.Dispatchers.IO
import java.io.DataOutputStream
import java.io.IOException
import java.net.HttpURLConnection
import java.net.URL
import com.erz.joysticklibrary.JoyStick;
import kotlin.math.cos
import kotlin.math.sin
import androidx.lifecycle.lifecycleScope
import com.example.armcontrollerapp.Globals.Companion.x
import com.example.armcontrollerapp.Globals.Companion.y
import com.example.armcontrollerapp.Globals.Companion.z
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch
import kotlinx.coroutines.sync.Mutex
import kotlinx.coroutines.sync.withLock


class JoyStickMode : AppCompatActivity(), JoyStick.JoyStickListener {
    val DELAY_MS: Long = 50
    val TIME_OUT = 1000L
    val SCALE_DOWN: Double = 0.000001
    val zIncrement = 0.3
    var joystickAngle: Double = 0.0
    var joystickPower: Double = 0.0
    private var BASE_URL: String = "http://192.168.4.1"
    private var mode: String = "JoyStick"
    private val handler = Handler()
    private var runnable: Runnable? = null




    public fun updatePositionUI(): Unit{
        runnable = object : Runnable {

            val xText = findViewById<TextView>(R.id.xText)
            val yText = findViewById<TextView>(R.id.yText)
            override fun run() {
                // Call your function here
                x += -joystickPower*cos(joystickAngle)*SCALE_DOWN
                y += joystickPower*sin(joystickAngle)*SCALE_DOWN
                x = x.coerceIn(0.0, 30.0)
                y = y.coerceIn(0.0, 30.0)
                xText.text = String.format("x: %.1f", x)
                yText.text = String.format("y: %.1f", y)


                // Schedule the task to run again after a delay
                handler.postDelayed(this, DELAY_MS)
            }
        }

        handler.post(runnable!!)
    }
    fun alert(message: String) {
        Toast.makeText(this, message, Toast.LENGTH_SHORT)
            .show()
    }

    val mutex = Mutex()
    public suspend fun sendDataToESP(x: Double, y: Double, z:Double): Unit{
        mutex.withLock {
            val url =URL(String.format("%s/posts?mode=JoyStick&x=%.2f&y=%.2f&z=%.2f", BASE_URL, x, y, z))
//            println(url)
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

    }

    private var sendJob: Job? = null

    override fun onResume() {
        super.onResume()
        sendJob = CoroutineScope(Dispatchers.IO).launch {
            while (isActive) {
                updatePositionUI()
                sendDataToESP(x, y, z)
                delay(DELAY_MS)
            }
        }
    }

    override fun onDestroy() {
        super.onDestroy()
        sendJob?.cancel()
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.joystick_layout)

        updatePositionUI()

        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        val joystick = findViewById<JoyStick>(R.id.Joystick)
        val btnZPos = findViewById<Button>(R.id.btnZPos)
        val btnZNeg = findViewById<Button>(R.id.btnZNeg)
        val btnCalibrate = findViewById<Button>(R.id.calibrate)
        val xText = findViewById<TextView>(R.id.xText)
        val yText = findViewById<TextView>(R.id.yText)
        val zText = findViewById<TextView>(R.id.zText)
        joystick.setListener(this)
//        joystick.enableStayPut(true);

        btnZPos.setOnClickListener{
            z += zIncrement
            zText.text = String.format("z: %.1f", z)

        }

        btnZNeg.setOnClickListener{
            z -= zIncrement
            zText.text = String.format("z: %.1f", z)
        }

        btnCalibrate.setOnClickListener{
            x = 0.0
            y = 30.0
            z = 0.0
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            zText.text = String.format("z: %.1f", z)
            alert("Calibrated successfully to (0,0,0)")
        }

        val spinner = findViewById<Spinner>(R.id.selectMode)
        val modes = resources.getStringArray(R.array.mode)
        var adapter: ArrayAdapter<CharSequence> = ArrayAdapter.createFromResource(this, R.array.mode, android.R.layout.simple_spinner_item)
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_item)


        spinner.setAdapter(adapter)
        spinner.setSelection(1)

        spinner.onItemSelectedListener = object :


            AdapterView.OnItemSelectedListener {
            override fun onItemSelected(parent: AdapterView<*>,
                                        view: View?, position: Int, id: Long) {
                if(view != null){
                    mode = modes[position]

                    Toast.makeText(this@JoyStickMode,
                        getString(R.string.selected_mode) + " " +
                                "" + mode, Toast.LENGTH_SHORT).show()
                    when(mode){
                        "Slider" -> {
                            if (runnable != null) {
                                handler.removeCallbacks(runnable!!)
                                runnable = null
                            }
                            finish()
                            val intent = Intent(this@JoyStickMode, SliderMode::class.java)
                            startActivity(intent)
                        }
                        "Arrows" ->{
                            if (runnable != null) {
                                handler.removeCallbacks(runnable!!)
                                runnable = null
                            }
                            finish()
                            val intent = Intent(this@JoyStickMode, MainActivity::class.java)
                            startActivity(intent)
                        }
                    }
                }


            }

            override fun onNothingSelected(parent: AdapterView<*>) {
                // write code to perform some action
            }
        }
    }

    override fun onMove(joyStick: JoyStick?, angle: Double, power: Double, direction: Int) {
//        println(String.format("Angle: $angle\tPower: $power"))
        joystickAngle = angle
        joystickPower = power
    }

    override fun onTap() {
        println("nothing")
    }

    override fun onDoubleTap() {
        println("nothing")
    }


}