struct Joystick{
  int x;
  int y;
};

Joystick joystick = {0, 0};

void updatePositionXY(){
  x += joystick.x * 1e-4;
  y += joystick.y * 1e-4;
}
