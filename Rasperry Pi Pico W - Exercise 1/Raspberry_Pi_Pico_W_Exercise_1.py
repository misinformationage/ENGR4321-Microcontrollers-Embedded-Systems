## Part 1 - Hello World

#import time
#time.sleep(3.5) 
#print("Hello, Pi Pico W! - Skylar")

## Part 2 - Blink Onboard LED

#import machine
#import time
#led = machine.Pin("LED", machine.Pin.OUT)

#while True:
#    led.value(1)
#    time.sleep(1)
#    led.value(0)
#    time.sleep(1)

## Part 3 - Blink External LED

#import machine
#import time
#led = machine.Pin(13, machine.Pin.OUT)

#while True:
#    led.value(1)
#    time.sleep(1)
#    led.value(0)
#    time.sleep(1)

## Part 4 - LED Reaction Game

from machine import Pin
import time
import random

led_red = Pin(13, Pin.OUT)
led_blue = Pin(12, Pin.OUT)
led_green = Pin(11, Pin.OUT)
led_yellow = Pin(10, Pin.OUT)
button_red = Pin(5, Pin.IN, Pin.PULL_UP)
button_blue = Pin(4, Pin.IN, Pin.PULL_UP)
button_green = Pin(3, Pin.IN, Pin.PULL_UP)
button_yellow = Pin(2, Pin.IN, Pin.PULL_UP)

num = 0; start = 0; end = 0; elapsed = 0; attempt = 0;

#Code could probably be optimized using matrices and indexing
while True:
    num = random.randint(0, 3)
    attempt = attempt + 1
    start = time.ticks_ms()

    if num == 0:
        led_red.value(1)
        while True:
            if button_red.value() == 0:
                end = time.ticks_ms()
                elapsed = time.ticks_diff(end, start)
                led_red.value(0)
                print("Attempt: " +str(attempt))
                print("Reaction Time: " + str(elapsed) + " ms")
                break

    if num == 1:
        led_blue.value(1)
        while True:
            if button_blue.value() == 0:
                end = time.ticks_ms()
                elapsed = time.ticks_diff(end, start)
                led_blue.value(0)
                print("Attempt: " +str(attempt))
                print("Reaction Time: " + str(elapsed) + " ms")
                break

    if num == 2:
        led_green.value(1)
        while True:
            if button_green.value() == 0:
                end = time.ticks_ms()
                elapsed = time.ticks_diff(end, start)
                led_green.value(0)
                print("Attempt: " +str(attempt))
                print("Reaction Time: " + str(elapsed) + " ms")
                break

    if num == 3:
        led_yellow.value(1)
        while True:
            if button_yellow.value() == 0:
                end = time.ticks_ms()
                elapsed = time.ticks_diff(end, start)
                led_yellow.value(0)
                print("Attempt: " +str(attempt))
                print("Reaction Time: " + str(elapsed) + " ms")
                break
