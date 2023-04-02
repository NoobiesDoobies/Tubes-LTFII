package com.plcoding.ktorclientandroid

//import android.R
import android.content.pm.ActivityInfo
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import androidx.compose.foundation.layout.*
import androidx.compose.foundation.lazy.LazyColumn
import androidx.compose.foundation.lazy.items
import androidx.compose.material.MaterialTheme
import androidx.compose.material.Surface
import androidx.compose.material.Text
import androidx.compose.runtime.produceState
import androidx.compose.ui.Modifier
import androidx.compose.ui.unit.dp
import androidx.compose.ui.unit.sp
import com.plcoding.ktorclientandroid.data.remote.PostsService
import com.plcoding.ktorclientandroid.data.remote.dto.PostRequest
import com.plcoding.ktorclientandroid.data.remote.dto.PostResponse
import com.plcoding.ktorclientandroid.ui.theme.KtorClientAndroidTheme
import kotlinx.serialization.json.Json
import io.ktor.client.request.*
import io.ktor.client.statement.*
import io.ktor.http.*
import kotlinx.coroutines.runBlocking
class MainActivity : ComponentActivity() {
    private var x: Double = 0.0
    private var y: Double = 0.0
    private var z: Double = 0.0
    private var xIncrement: Double = 0.5
    private var yIncrement: Double = 0.7
    private var zIncrement: Double = 0.3
    private var lastMessageSentTime: Long = 0

    private val service = PostsService.create()

    OkHttpClient client;
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
            runBlocking {
//                service.createPost(PostRequest(1,2,3))
                val get = service.getPosts()
                print(get)
            }
            x-=xIncrement
            xText.text = String.format("x: %.1f", x)
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
//            if(connected){
//                sendBluetoothMessage(positionString)

//            }
            alert("Calibrated successfully to (0,0,0)")
        }


//        setContent {
//            val posts = produceState<List<PostResponse>>(
//                initialValue = emptyList(),
//                producer = {
//                    value = service.getPosts()
//                }
//            )
//            KtorClientAndroidTheme {
//                Surface(color = MaterialTheme.colors.background) {
//                    LazyColumn {
//                        items(posts.value) {
//                            Column(
//                                modifier = Modifier
//                                    .fillMaxWidth()
//                                    .padding(16.dp)
//                            ) {
//                                Text(text = it.title, fontSize = 20.sp)
//                                Spacer(modifier = Modifier.height(4.dp))
//                                Text(text = it.body, fontSize = 14.sp)
//                            }
//                        }
//                    }
//                }
//            }
//        }
    }
}