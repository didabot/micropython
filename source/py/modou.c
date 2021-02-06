#include <stdint.h>
const char mp_frozen_str_names[] = {
"modou.py\0"
"\0"};
const uint32_t mp_frozen_str_sizes[] = {
3652,
0};
const char mp_frozen_str_content[] = {
"# \xe5\x9c\xa8\xe8\xbf\x99\xe9\x87\x8c\xe5\x86\x99\xe4\xb8\x8a\xe4\xbd\xa0\xe7\x9a\x84\xe4\xbb\xa3\xe7\xa0\x81" " :-)\nfrom microbit import i2c, pin1, pin8, pin14, pin15, pin16\nfrom machine import time_pulse_us\nfrom micropython import const\nfrom neopixel import NeoPixel\nfrom utime import sleep_us\nfrom gc import collect\n\ncollect()\nneo = NeoPixel(pin1, 3)\n\n# light definition\nLIGHT1 = const(8)\nLIGHT2 = const(9)\nLIGHT3 = const(7)\nLIGHT4 = const(5)\n\n# led definition\nLED1 = const(0)\nLED2 = const(1)\nLED3 = const(2)\n\n# stardard color\nRED = const((255, 0, 0))\nORANGE = const((255, 165, 0))\nYELLOW = const((255, 255, 0))\nGREEN = const((0, 255, 0))\nCYAN = const((0, 255, 255))\nBLUE = const((0, 0, 255))\nPURPLE = const((160, 32, 240))\nWHITE = const((255, 255, 255))\nBLACK = const((0, 0, 0))\n\n# wheel definition\nLEFT = const(0)\nRIGHT = const(1)\n\ndef pwm_init():\n    i2c.write(0x40, bytearray([0x00, 0x00]))\n    # set frequence to 50hz\n    i2c.write(0x40, bytearray([0x00]))\n    old_mode = i2c.read(0x40, 1)[0]\n    new_mode = (old_mode & 0x7F) | 0x10\n    i2c.write(0x40, bytearray([0x00, new_mode]))\n    i2c.write(0x40, bytearray([0xFE, 126]))\n    i2c.write(0x40, bytearray([0x00, old_mode]))\n    sleep_us(5)\n    i2c.write(0x40, bytearray([0x00, (old_mode | 0xA1)]))\n\ndef pwm_set(ch, on, off):\n    buffer = [0, 0, 0, 0, 0]\n    buffer[0] = int(0x06 + 4 * ch)\n    buffer[1] = int(on & 0xFF)\n    buffer[2] = int((on >> 8) & 0xFF)\n    buffer[3] = int(off & 0xFF)\n    buffer[4] = int((off >> 8) & 0xFF)\n    i2c.write(0x40, bytearray(buffer))\n\ndef set_header_angle(angle):\n    if angle < 0 or angle > 180:\n        raise ValueError('invalid header angle, use 0~180')\n    # 50hz: 20,000 us\n    v_us = (angle * 10 + 600.0)\n    value = v_us * 4096.0 / 20000.0\n    pwm_set(6, 0, int(value))\n\ndef set_led_color(n, color):\n    if n < LED1 or n > LED3:\n        raise ValueError('invalid led name, use LED1, LED2, LED3')\n    neo[n] = color\n    neo.show()\n\ndef set_light(light, brightness):\n    if (light != LIGHT1) \\\n    and (light != LIGHT2) \\\n    and (light != LIGHT3) \\\n    and (light != LIGHT4):\n        raise ValueError('invalid light name, e.g. LIGHT1')\n\n    if brightness < 0 or brightness > 100:\n        raise ValueError('invalid brightness value, use 0~100')\n\n    level = brightness * 40.96\n    pwm_set(light, 0, int(level))\n\ndef set_wheel(wheel, speed):\n    if wheel != LEFT and wheel != RIGHT:\n        raise ValueError('invalid wheel name: use LEFT or RIGHT')\n\n    if speed < -100 or speed > 100:\n        raise ValueError('invalid speed value: use -100~100')\n\n    level = speed * 40.96\n    if wheel == LEFT and level > 0:\n        pwm_set(2, 0, int(level))\n        pwm_set(3, 0, 0)\n\n    elif wheel == LEFT and level <= 0:\n        pwm_set(2, 0, 0)\n        pwm_set(3, 0, int(-level))\n\n    elif wheel == RIGHT and level > 0:\n        pwm_set(0, 0, 0)\n        pwm_set(1, 0, int(level))\n\n    elif wheel == RIGHT and level <= 0:\n        pwm_set(0, 0, int(-level))\n        pwm_set(1, 0, 0)\n\ndef run(left_speed, right_speed):\n    set_wheel(LEFT, left_speed)\n    set_wheel(RIGHT, right_speed)\n\ndef stop():\n    run(0, 0)\n\ndef sonar():\n    pin15.read_digital()\n    pin14.write_digital(1)\n    sleep_us(10)\n    pin14.write_digital(0)\n    ts = time_pulse_us(pin15, 1, 25000)\n    return ts * 9 / 6 / 58\n\ndef tracking():\n    left = pin16.read_digital()\n    right = pin8.read_digital()\n    if left == 0 and right == 0:\n        return '11'\n    elif left == 0 and right == 1:\n        return '10'\n    elif left == 1 and right == 0:\n        return '01'\n    else:\n        return '00'\n\ndef init():\n    pwm_init()\n    for ch in range(16):\n        pwm_set(ch, 0, 0)\n    set_led_color(LED1, BLACK)\n    set_led_color(LED2, BLACK)\n    set_led_color(LED3, BLACK)\n\ninit()\n\n\n\n\n\n\n\n\n\n\0"
"\0"};
