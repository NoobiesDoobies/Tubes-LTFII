package com.example.armcontrollerapp

import android.content.pm.ActivityInfo
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import okhttp3.*
import okhttp3.MediaType.Companion.toMediaType
import okhttp3.MediaType.Companion.toMediaTypeOrNull
import java.io.IOException
import java.net.URL

class MainActivity : AppCompatActivity() {
    private var x: Double = 0.0
    private var y: Double = 0.0
    private var z: Double = 0.0
    private var xIncrement: Double = 0.5
    private var yIncrement: Double = 0.7
    private var zIncrement: Double = 0.3

    var client: OkHttpClient = OkHttpClient();
    private var url: String = "http://192.168.4.1/posts"

    private fun sendJoyStickPosition(x: Double, y: Double, z: Double): String {
        println("SENDING DATA TO ARDUINO")
//        var body = FormBody.Builder()
//            .add("x", x.toString())
//            .add("y", y.toString())
//            .add("z", z.toString())
//            .build()
        var json: String = String.format("{\"x\":%.1f,\"y\":%.1f,\"z\":%.1f}", x, y, z)
        var body = RequestBody.create("application/json".toMediaTypeOrNull(), json)

        var request = Request.Builder()
            .url(url)
            .post(body)
            .build()
        client.newCall(request).execute().use { response ->
            if (!response.isSuccessful) throw IOException("Unexpected code $response")

            println(response.body!!.string())
            return response.body!!.string()
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


        btnLeft.setOnClickListener{
            x-=xIncrement
            xText.text = String.format("x: %.1f", x)
            sendJoyStickPosition(x, y, z)
        }

        btnRight.setOnClickListener{
            x+=xIncrement
            xText.text = String.format("x: %.1f", x)
        }

        btnUp.setOnClickListener{
            y+=yIncrement
            yText.text = String.format("y: %.1f", y)
        }

        btnDown.setOnClickListener{
            y-=yIncrement
            yText.text = String.format("y: %.1f", y)
        }

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
            y = 0.0
            z = 0.0

            var positionString = String.format("%.1f %.1f %.1f\n", x, y, z)
            xText.text = String.format("x: %.1f", x)
            yText.text = String.format("y: %.1f", y)
            zText.text = String.format("z: %.1f", z)
            alert("Calibrated successfully to (0,0,0)")
        }
    }
}