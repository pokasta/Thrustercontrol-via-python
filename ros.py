#! /usr/bin/env python

import tsys01
from time import sleep
from sensor_connect.msg import sensor

import rospy


sensor_data = tsys01.TSYS01()

if not sensor_data.init():
    print("Error initializing sensor")
    exit(1)


pub = rospy.Publisher('data12',sensor,queue_size=20)

rospy.init_node('sender',anonymous=True)

rate = rospy.Rate(1)
while True:
    if not sensor_data.read():
        print("Error reading sensor")
        exit(1)
    data = sensor_data.temperature()

    print("Temperature:",data)
    sens =sensor()
    sens.sensor1 = data
        #print(type(sensor_data.temperature()))
    pub.publish(sens)
    sleep(2)
