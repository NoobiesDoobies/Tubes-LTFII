package com.example.armcontrollerapp

class Globals {
    companion object {
        const val L1: Double = 13.2
        const val L2: Double = 10.5
        const val R: Double = L1+ L2
        const val R2: Double = R*R
        var x: Double = 0.0
        var y: Double = L1+L2
        var z: Int = 2
        const val zIncrement: Int = 1
        var calibrate: Int = 0
        val BASE_URL: String = "http://192.168.4.1"

        const val xLowerLimit: Double = -(L1+L2)
        const val xUpperLimit: Double = L1+L2
        const val yLowerLimit: Double = 0.0
        const val yUpperLimit: Double = L1+L2
        const val zLowerLimit: Int = 0
        const val zUpperLimit: Int = 2
        var sliderRange: Float = 20.0F
        const val SCALE_DOWN: Double = 0.0000001
        var speed: Double = 0.000001

    }
}