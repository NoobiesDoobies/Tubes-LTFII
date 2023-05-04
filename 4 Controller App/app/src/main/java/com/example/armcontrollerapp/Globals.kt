package com.example.armcontrollerapp

class Globals {
    companion object {
        var x: Double = 0.0
        var y: Double = 23.7
        var z: Int = 2
        const val zIncrement: Int = 1
        var calibrate: Int = 0
        val BASE_URL: String = "http://192.168.4.1"
        const val xLowerLimit: Double = 0.0
        const val xUpperLimit: Double = 23.7
        const val yLowerLimit: Double = 0.0
        const val yUpperLimit: Double = 23.7
        const val zLowerLimit: Int = 0
        const val zUpperLimit: Int = 2
        var sliderRange: Float = 20.0F
        var speed: Double = 0.0001
    }
}