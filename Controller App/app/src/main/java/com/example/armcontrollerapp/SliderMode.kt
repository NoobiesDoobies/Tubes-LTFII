package com.example.armcontrollerapp;

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.*
import androidx.appcompat.app.AppCompatActivity

class SliderMode : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        var mode: String = "Slider"
        super.onCreate(savedInstanceState)
        setContentView(R.layout.slider_layout)

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
                Toast.makeText(this@SliderMode,
                    getString(R.string.selected_mode) + " " +
                            "" + mode, Toast.LENGTH_SHORT).show()
                when(mode){
                    "Slider" -> {
                        val intent = Intent(this@SliderMode, SliderMode::class.java)
                        startActivity(intent)
                    }
                    "JoyStick" ->{
                        val intent = Intent(this@SliderMode, JoyStickMode::class.java)
                        startActivity(intent)
                    }
                }

            }

            override fun onNothingSelected(parent: AdapterView<*>) {
                // write code to perform some action
            }
        }


    }
}  