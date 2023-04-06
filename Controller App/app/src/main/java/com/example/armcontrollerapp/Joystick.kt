package com.example.armcontrollerapp

import android.content.Context
import android.graphics.Canvas
import android.graphics.Color
import android.graphics.Paint
import android.graphics.PointF
import android.util.AttributeSet
import android.view.MotionEvent
import android.view.View
import kotlin.math.atan2
import kotlin.math.hypot

class Joystick(context: Context?, attrs: AttributeSet?) : View(context, attrs) {

    private val outerCirclePaint = Paint().apply {
        color = Color.GRAY
        style = Paint.Style.FILL
    }
    private val innerCirclePaint = Paint().apply {
        color = Color.RED
        style = Paint.Style.FILL
    }
    private val linePaint = Paint().apply {
        color = Color.BLACK
        style = Paint.Style.STROKE
        strokeWidth = 10f
    }

    private var outerRadius = 0f
    private var innerRadius = 0f
    private var centerX = 0f
    private var centerY = 0f
    private var joystickCallback: JoystickListener? = null

    interface JoystickListener {
        fun onJoystickMoved(xPercent: Float, yPercent: Float)
    }

    fun setJoystickListener(joystickCallback: JoystickListener) {
        this.joystickCallback = joystickCallback
    }

    override fun onDraw(canvas: Canvas?) {
        super.onDraw(canvas)
        canvas?.apply {
            drawCircle(centerX, centerY, outerRadius, outerCirclePaint)
            drawCircle(centerX, centerY, innerRadius, innerCirclePaint)
            drawLine(centerX, centerY, touchX, touchY, linePaint)
        }
    }

    override fun onSizeChanged(w: Int, h: Int, oldw: Int, oldh: Int) {
        super.onSizeChanged(w, h, oldw, oldh)
        outerRadius = (w / 2).toFloat()
        innerRadius = (w / 4).toFloat()
        centerX = (w / 2).toFloat()
        centerY = (h / 2).toFloat()
    }

    private var touchX = centerX
    private var touchY = centerY

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        event?.apply {
            when (action) {
                MotionEvent.ACTION_DOWN, MotionEvent.ACTION_MOVE -> {
                    val distance = hypot(event.x - centerX, event.y - centerY)
                    if (distance < outerRadius) {
                        touchX = event.x
                        touchY = event.y
                        invalidate()
                    } else {
                        val angle = atan2(event.y - centerY, event.x - centerX)
                        touchX = (centerX + outerRadius * kotlin.math.cos(angle)).toFloat()
                        touchY = (centerY + outerRadius * kotlin.math.sin(angle)).toFloat()
                        invalidate()
                    }
                    val xPercent = (touchX - centerX) / outerRadius
                    val yPercent = (touchY - centerY) / outerRadius
                    joystickCallback?.onJoystickMoved(xPercent, yPercent)
                }
                MotionEvent.ACTION_UP -> {
                    touchX = centerX
                    touchY = centerY
                    invalidate()
                    joystickCallback?.onJoystickMoved(0f, 0f)
                }
            }
        }
        return true
    }
}
