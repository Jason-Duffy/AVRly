EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Arduino Uno ISP Shield"
Date "2022-03-15"
Rev "1"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2750 3050 1    60   ~ 0
Vin
Text Label 3150 3050 1    60   ~ 0
IOREF
Text Label 2700 4100 0    60   ~ 0
A0
Text Label 2700 4200 0    60   ~ 0
A1
Text Label 2700 4300 0    60   ~ 0
A2
Text Label 2700 4400 0    60   ~ 0
A3
Text Label 2700 4500 0    60   ~ 0
A4(SDA)
Text Label 2700 4600 0    60   ~ 0
A5(SCL)
Text Label 4350 4600 0    60   ~ 0
0(Rx)
Text Label 4350 4400 0    60   ~ 0
2
Text Label 4350 4500 0    60   ~ 0
1(Tx)
Text Label 4350 4300 0    60   ~ 0
3(**)
Text Label 4350 4200 0    60   ~ 0
4
Text Label 4350 4100 0    60   ~ 0
5(**)
Text Label 4350 4000 0    60   ~ 0
6(**)
Text Label 4350 3900 0    60   ~ 0
7
Text Label 4350 3700 0    60   ~ 0
8
Text Label 4350 3600 0    60   ~ 0
9(**)
Text Label 4350 3000 0    60   ~ 0
AREF
NoConn ~ 3200 3200
Text Label 4350 2900 0    60   ~ 0
_A4(SDA)
Text Label 4350 2800 0    60   ~ 0
_A5(SCL)
Text Notes 5250 5000 0    60   ~ 0
Holes
Text Notes 2400 2300 0    79   ~ 0
Shield for Arduino Uno board Rev 3.
$Comp
L Connector_Generic:Conn_01x08 P1
U 1 1 56D70129
P 3400 3500
F 0 "P1" H 3400 3950 50  0000 C CNN
F 1 "Power" V 3500 3500 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 3550 3500 20  0000 C CNN
F 3 "" H 3400 3500 50  0000 C CNN
	1    3400 3500
	1    0    0    -1  
$EndComp
Text Label 2450 3400 0    60   ~ 0
Reset
$Comp
L power:+3.3V #PWR01
U 1 1 56D70538
P 2950 3050
F 0 "#PWR01" H 2950 2900 50  0001 C CNN
F 1 "+3.3V" V 2950 3300 50  0000 C CNN
F 2 "" H 2950 3050 50  0000 C CNN
F 3 "" H 2950 3050 50  0000 C CNN
	1    2950 3050
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR02
U 1 1 56D707BB
P 2850 2950
F 0 "#PWR02" H 2850 2800 50  0001 C CNN
F 1 "+5V" V 2850 3150 50  0000 C CNN
F 2 "" H 2850 2950 50  0000 C CNN
F 3 "" H 2850 2950 50  0000 C CNN
	1    2850 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 56D70CC2
P 3100 4750
F 0 "#PWR03" H 3100 4500 50  0001 C CNN
F 1 "GND" H 3100 4600 50  0000 C CNN
F 2 "" H 3100 4750 50  0000 C CNN
F 3 "" H 3100 4750 50  0000 C CNN
	1    3100 4750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR04
U 1 1 56D70CFF
P 4100 4750
F 0 "#PWR04" H 4100 4500 50  0001 C CNN
F 1 "GND" H 4100 4600 50  0000 C CNN
F 2 "" H 4100 4750 50  0000 C CNN
F 3 "" H 4100 4750 50  0000 C CNN
	1    4100 4750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x06 P2
U 1 1 56D70DD8
P 3400 4300
F 0 "P2" H 3400 3900 50  0000 C CNN
F 1 "Analog" V 3500 4300 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x06" V 3550 4350 20  0000 C CNN
F 3 "" H 3400 4300 50  0000 C CNN
	1    3400 4300
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P5
U 1 1 56D71177
P 5200 4650
F 0 "P5" V 5300 4650 50  0000 C CNN
F 1 "CONN_01X01" V 5300 4650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 5121 4724 20  0000 C CNN
F 3 "" H 5200 4650 50  0000 C CNN
	1    5200 4650
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P6
U 1 1 56D71274
P 5300 4650
F 0 "P6" V 5400 4650 50  0000 C CNN
F 1 "CONN_01X01" V 5400 4650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 5300 4650 20  0001 C CNN
F 3 "" H 5300 4650 50  0000 C CNN
	1    5300 4650
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P7
U 1 1 56D712A8
P 5400 4650
F 0 "P7" V 5500 4650 50  0000 C CNN
F 1 "CONN_01X01" V 5500 4650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" V 5400 4650 20  0001 C CNN
F 3 "" H 5400 4650 50  0000 C CNN
	1    5400 4650
	0    -1   -1   0   
$EndComp
$Comp
L Connector_Generic:Conn_01x01 P8
U 1 1 56D712DB
P 5500 4650
F 0 "P8" V 5600 4650 50  0000 C CNN
F 1 "CONN_01X01" V 5600 4650 50  0001 C CNN
F 2 "Socket_Arduino_Uno:Arduino_1pin" H 5424 4572 20  0000 C CNN
F 3 "" H 5500 4650 50  0000 C CNN
	1    5500 4650
	0    -1   -1   0   
$EndComp
NoConn ~ 5200 4850
NoConn ~ 5300 4850
NoConn ~ 5400 4850
NoConn ~ 5500 4850
$Comp
L Connector_Generic:Conn_01x08 P4
U 1 1 56D7164F
P 3800 4200
F 0 "P4" H 3800 3700 50  0000 C CNN
F 1 "Digital" V 3900 4200 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x08" V 3950 4150 20  0000 C CNN
F 3 "" H 3800 4200 50  0000 C CNN
	1    3800 4200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	3150 3050 3150 3300
Wire Wire Line
	3150 3300 3200 3300
Wire Wire Line
	3200 3500 2950 3500
Wire Wire Line
	3200 3600 2850 3600
Wire Wire Line
	3200 3900 2750 3900
Wire Wire Line
	3200 3700 3100 3700
Wire Wire Line
	3200 3800 3100 3800
Connection ~ 3100 3800
Wire Wire Line
	2750 3900 2750 3050
Wire Wire Line
	2850 3600 2850 2950
Wire Wire Line
	2950 3500 2950 3050
Wire Wire Line
	3200 4100 2700 4100
Wire Wire Line
	3200 4200 2700 4200
Wire Wire Line
	3200 4300 2700 4300
Wire Wire Line
	3200 4400 2700 4400
Wire Wire Line
	3200 4500 2700 4500
Wire Wire Line
	3200 4600 2700 4600
$Comp
L Connector_Generic:Conn_01x10 P3
U 1 1 56D721E0
P 3800 3200
F 0 "P3" H 3800 3750 50  0000 C CNN
F 1 "Digital" V 3900 3200 50  0000 C CNN
F 2 "Socket_Arduino_Uno:Socket_Strip_Arduino_1x10" V 3950 3200 20  0000 C CNN
F 3 "" H 3800 3200 50  0000 C CNN
	1    3800 3200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4000 3700 4350 3700
Wire Wire Line
	4000 3600 4350 3600
Wire Wire Line
	4000 3500 4350 3500
Wire Wire Line
	4000 3400 4350 3400
Wire Wire Line
	4000 3300 4350 3300
Wire Wire Line
	4000 3200 4350 3200
Wire Wire Line
	4000 3000 4350 3000
Wire Wire Line
	4000 2900 4350 2900
Wire Wire Line
	4000 2800 4350 2800
Wire Wire Line
	4000 4600 4350 4600
Wire Wire Line
	4000 4500 4350 4500
Wire Wire Line
	4000 4400 4350 4400
Wire Wire Line
	4000 4300 4350 4300
Wire Wire Line
	4000 4200 4350 4200
Wire Wire Line
	4000 4100 4350 4100
Wire Wire Line
	4000 4000 4350 4000
Wire Wire Line
	4000 3900 4350 3900
Wire Wire Line
	4000 3100 4100 3100
Wire Wire Line
	4100 3100 4100 4750
Wire Wire Line
	3100 3700 3100 3800
Wire Wire Line
	3100 3800 3100 4750
Wire Wire Line
	3200 3400 2450 3400
Text Notes 3500 3200 0    60   ~ 0
1
$Comp
L Connector:AVR-ISP-6 J1
U 1 1 61253484
P 7415 3085
F 0 "J1" H 7086 3181 50  0000 R CNN
F 1 "AVR-ISP-6" H 7086 3090 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x03_P2.54mm_Vertical" V 7165 3135 50  0001 C CNN
F 3 " ~" H 6140 2535 50  0001 C CNN
	1    7415 3085
	1    0    0    -1  
$EndComp
$Comp
L Connector:AVR-ISP-10 J2
U 1 1 6125409E
P 7395 4525
F 0 "J2" H 7065 4621 50  0000 R CNN
F 1 "AVR-ISP-10" H 7065 4530 50  0000 R CNN
F 2 "Connector_IDC:IDC-Header_2x05_P2.54mm_Vertical" V 7145 4575 50  0001 C CNN
F 3 " ~" H 6120 3975 50  0001 C CNN
	1    7395 4525
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR05
U 1 1 612551BE
P 7315 2585
F 0 "#PWR05" H 7315 2435 50  0001 C CNN
F 1 "+5V" H 7330 2758 50  0000 C CNN
F 2 "" H 7315 2585 50  0001 C CNN
F 3 "" H 7315 2585 50  0001 C CNN
	1    7315 2585
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR07
U 1 1 61255AB7
P 7295 4025
F 0 "#PWR07" H 7295 3875 50  0001 C CNN
F 1 "+5V" H 7310 4198 50  0000 C CNN
F 2 "" H 7295 4025 50  0001 C CNN
F 3 "" H 7295 4025 50  0001 C CNN
	1    7295 4025
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 612565FE
P 7315 3485
F 0 "#PWR06" H 7315 3235 50  0001 C CNN
F 1 "GND" H 7320 3312 50  0000 C CNN
F 2 "" H 7315 3485 50  0001 C CNN
F 3 "" H 7315 3485 50  0001 C CNN
	1    7315 3485
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 61257295
P 7295 4925
F 0 "#PWR08" H 7295 4675 50  0001 C CNN
F 1 "GND" H 7300 4752 50  0000 C CNN
F 2 "" H 7295 4925 50  0001 C CNN
F 3 "" H 7295 4925 50  0001 C CNN
	1    7295 4925
	1    0    0    -1  
$EndComp
Text GLabel 4400 3350 2    60   Input ~ 0
11(MOSI)
Text GLabel 4400 3250 2    60   Input ~ 0
12(MISO)
Text GLabel 4400 3150 2    60   Input ~ 0
13(SCK)
Text GLabel 4400 3450 2    60   Input ~ 0
10(SS)
Text GLabel 7795 4525 2    60   Input ~ 0
13(SCK)
Text GLabel 7795 4325 2    60   Input ~ 0
12(MISO)
Text GLabel 7815 2985 2    60   Input ~ 0
11(MOSI)
Text GLabel 7795 4625 2    60   Input ~ 0
10(SS)
Text GLabel 7795 4425 2    60   Input ~ 0
11(MOSI)
Text GLabel 7815 2885 2    60   Input ~ 0
12(MISO)
Text GLabel 7815 3185 2    60   Input ~ 0
10(SS)
Text GLabel 7815 3085 2    60   Input ~ 0
13(SCK)
Wire Notes Line
	5900 2050 5900 5250
Wire Notes Line
	5900 5250 2200 5250
Wire Notes Line
	2200 5250 2200 2050
Wire Notes Line
	2200 2050 5900 2050
Wire Notes Line
	6300 2050 9100 2050
Wire Notes Line
	9100 2050 9100 5250
Wire Notes Line
	9100 5250 6300 5250
Wire Notes Line
	6300 5250 6300 2050
Text Notes 6500 2300 0    79   ~ 0
ISP header sockets
Text Notes 7850 3400 0    79   ~ 0
6 pin variant
Text Notes 7850 4850 0    79   ~ 0
10 pin variant
Wire Wire Line
	4350 3500 4350 3450
Wire Wire Line
	4350 3450 4400 3450
Wire Wire Line
	4350 3400 4350 3350
Wire Wire Line
	4350 3350 4400 3350
Wire Wire Line
	4350 3300 4350 3250
Wire Wire Line
	4350 3250 4400 3250
Wire Wire Line
	4350 3200 4350 3150
Wire Wire Line
	4350 3150 4400 3150
$EndSCHEMATC
