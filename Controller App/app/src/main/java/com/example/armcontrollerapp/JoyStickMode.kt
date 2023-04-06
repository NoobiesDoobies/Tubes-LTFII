package com.example.armcontrollerapp
import android.content.Context
import android.content.Intent
import android.content.pm.ActivityInfo
import android.os.Bundle
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

class JoyStickMode : AppCompatActivity(), JoyStick.JoyStickListener {
    var mode: String = "JoyStick"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.joystick_layout)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        val joystick = findViewById<JoyStick>(R.id.Joystick)

        joystick.setListener(this)
//        joystick.enableStayPut(true);


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
                Toast.makeText(this@JoyStickMode,
                    getString(R.string.selected_mode) + " " +
                            "" + mode, Toast.LENGTH_SHORT).show()
                when(mode){
                    "Slider" -> {
                        val intent = Intent(this@JoyStickMode, SliderMode::class.java)
                        startActivity(intent)
                    }
                    "JoyStick" ->{
                        val intent = Intent(this@JoyStickMode, JoyStickMode::class.java)
                        startActivity(intent)
                    }
                }

            }

            override fun onNothingSelected(parent: AdapterView<*>) {
                // write code to perform some action
            }
        }
    }

    override fun onMove(joyStick: JoyStick?, angle: Double, power: Double, direction: Int) {
        println(String.format("Angle: $angle\tPower: $power"))
    }

    override fun onTap() {
        println("nothing")
    }

    override fun onDoubleTap() {
        println("nothing")
    }
}