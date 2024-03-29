EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr USLetter 11000 8500
encoding utf-8
Sheet 1 1
Title "Retro WiFi modem"
Date "2022-10-21"
Rev "2.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L RetroWiFiModem:CONN_02X05 P1
U 1 1 5E50B2EC
P 1550 5200
F 0 "P1" H 1550 5500 50  0000 C CNN
F 1 "CONN_02X05" H 1550 4900 50  0000 C CNN
F 2 "modules:IDC_Header_Straight_10pins" H 1550 4000 50  0001 C CNN
F 3 "http://www.on-shore.com/wp-content/uploads/2018/04/302-SXX1.pdf" H 1550 4000 50  0001 C CNN
F 4 "ED1543-ND" H 1550 5200 60  0001 C CNN "DigiKey PN"
F 5 "0.40" H 1550 5200 60  0001 C CNN "Price"
	1    1550 5200
	-1   0    0    1   
$EndComp
$Comp
L RetroWiFiModem:74LS32 U3
U 1 1 5E50B4BC
P 5700 5000
F 0 "U3" H 5700 5050 50  0000 C CNN
F 1 "74HC32" H 5700 4950 50  0000 C CNN
F 2 "modules:SOIC-14_3.9x8.7mm_P1.27mm" H 5700 5000 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74hc32" H 5700 5000 50  0001 C CNN
F 4 "296-1589-5-ND" H 5700 5000 60  0001 C CNN "DigiKey PN"
F 5 "0.63" H 5700 5000 60  0001 C CNN "Price"
	1    5700 5000
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LM2931AZ-3.3_5.0 U4
U 1 1 5E50B652
P 7300 2850
F 0 "U4" H 7300 3150 50  0000 C CNN
F 1 "L4931CZ33-AP" H 7300 3050 50  0000 C CNN
F 2 "modules:TO-92_Inline_Wide" H 7300 2950 50  0001 C CIN
F 3 "https://www.onsemi.com/pub/Collateral/LP2950-D.PDF" H 7300 2850 50  0001 C CNN
F 4 "LP2950ACZ-3.3GOS-ND" H 7300 2850 60  0001 C CNN "DigiKey PN"
F 5 "1.14" H 7300 2850 60  0001 C CNN "Price"
	1    7300 2850
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+3V3 #PWR01
U 1 1 5E50BA2F
P 8200 3950
F 0 "#PWR01" H 8200 3800 50  0001 C CNN
F 1 "+3V3" H 8200 4090 50  0000 C CNN
F 2 "" H 8200 3950 50  0001 C CNN
F 3 "" H 8200 3950 50  0001 C CNN
	1    8200 3950
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D3
U 1 1 5E50BCDD
P 1450 2100
F 0 "D3" H 1450 2200 50  0000 C CNN
F 1 "TLPR5600" H 1450 2000 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 2100 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 2100 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 2100 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 2100 60  0001 C CNN "Price"
	1    1450 2100
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D4
U 1 1 5E50BD48
P 1450 2400
F 0 "D4" H 1450 2500 50  0000 C CNN
F 1 "TLPR5600" H 1450 2300 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 2400 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 2400 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 2400 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 2400 60  0001 C CNN "Price"
	1    1450 2400
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D2
U 1 1 5E50BD80
P 1450 1800
F 0 "D2" H 1450 1900 50  0000 C CNN
F 1 "TLPR5600" H 1450 1700 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 1800 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 1800 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 1800 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 1800 60  0001 C CNN "Price"
	1    1450 1800
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D1
U 1 1 5E50BDC1
P 1450 1500
F 0 "D1" H 1450 1600 50  0000 C CNN
F 1 "TLPR5600" H 1450 1400 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 1500 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 1500 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 1500 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 1500 60  0001 C CNN "Price"
	1    1450 1500
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D5
U 1 1 5E50BE1F
P 1450 2700
F 0 "D5" H 1450 2800 50  0000 C CNN
F 1 "TLPR5600" H 1450 2600 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 2700 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 2700 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 2700 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 2700 60  0001 C CNN "Price"
	1    1450 2700
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D6
U 1 1 5E50BE68
P 1450 3000
F 0 "D6" H 1450 3100 50  0000 C CNN
F 1 "TLPR5600" H 1450 2900 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 3000 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 3000 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 3000 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 3000 60  0001 C CNN "Price"
	1    1450 3000
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D7
U 1 1 5E50BEAA
P 1450 3300
F 0 "D7" H 1450 3400 50  0000 C CNN
F 1 "TLPR5600" H 1450 3200 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 3300 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 3300 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 3300 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 3300 60  0001 C CNN "Price"
	1    1450 3300
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:LED D8
U 1 1 5E50BEEF
P 1450 3600
F 0 "D8" H 1450 3700 50  0000 C CNN
F 1 "TLPR5600" H 1450 3500 50  0000 C CNN
F 2 "modules:LED-3MM" H 1450 3600 50  0001 C CNN
F 3 "http://www.vishay.com/docs/83043/tlpg5600.pdf" H 1450 3600 50  0001 C CNN
F 4 "TLPR5600-ND" H 1450 3600 60  0001 C CNN "DigiKey PN"
F 5 "0.81" H 1450 3600 60  0001 C CNN "Price"
	1    1450 3600
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+5V #PWR02
U 1 1 5E50C40A
P 1100 1300
F 0 "#PWR02" H 1100 1150 50  0001 C CNN
F 1 "+5V" H 1100 1440 50  0000 C CNN
F 2 "" H 1100 1300 50  0001 C CNN
F 3 "" H 1100 1300 50  0001 C CNN
	1    1100 1300
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR03
U 1 1 5E510262
P 3000 2900
F 0 "#PWR03" H 3000 2650 50  0001 C CNN
F 1 "GND" H 3000 2750 50  0000 C CNN
F 2 "" H 3000 2900 50  0000 C CNN
F 3 "" H 3000 2900 50  0001 C CNN
	1    3000 2900
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C1
U 1 1 5E5104FF
P 2500 4050
F 0 "C1" H 2510 4120 50  0000 L CNN
F 1 "100nF" H 2510 3970 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 2500 4050 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C315C104M5U5TA7303.pdf" H 2500 4050 50  0001 C CNN
F 4 "399-9859-1-ND" H 2500 4050 60  0001 C CNN "DigiKey PN"
F 5 "0.37" H 2500 4050 60  0001 C CNN "Price"
	1    2500 4050
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C6
U 1 1 5E5105D7
P 4200 4200
F 0 "C6" H 4225 4275 50  0000 L CNN
F 1 "100nF" H 4050 4050 50  0000 L CNN
F 2 "modules:R3" H 4200 4200 50  0001 C CNN
F 3 "https://content.kemet.com/datasheets/KEM_C1042_AXIMAX_Z5U.pdf" H 4200 4200 50  0001 C CNN
F 4 "399-9843-ND" H 4200 4200 60  0001 C CNN "DigiKey PN"
F 5 "0.34" H 4200 4200 60  0001 C CNN "Price"
	1    4200 4200
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C2
U 1 1 5E51065C
P 2300 4300
F 0 "C2" V 2350 4350 50  0000 L CNN
F 1 "100nF" V 2200 4200 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 2300 4300 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C315C104M5U5TA7303.pdf" H 2300 4300 50  0001 C CNN
F 4 "399-9859-1-ND" V 2300 4300 60  0001 C CNN "DigiKey PN"
F 5 "0.37" V 2300 4300 60  0001 C CNN "Price"
	1    2300 4300
	0    1    1    0   
$EndComp
$Comp
L RetroWiFiModem:GND #PWR04
U 1 1 5E510D98
P 1975 4650
F 0 "#PWR04" H 1975 4400 50  0001 C CNN
F 1 "GND" H 2125 4600 50  0000 C CNN
F 2 "" H 1975 4650 50  0001 C CNN
F 3 "" H 1975 4650 50  0001 C CNN
	1    1975 4650
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C5
U 1 1 5E511436
P 3300 1300
F 0 "C5" H 3310 1370 50  0000 L CNN
F 1 "100nF" H 3310 1220 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 3300 1300 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C315C104M5U5TA7303.pdf" H 3300 1300 50  0001 C CNN
F 4 "399-9859-1-ND" H 3300 1300 60  0001 C CNN "DigiKey PN"
F 5 "0.37" H 3300 1300 60  0001 C CNN "Price"
	1    3300 1300
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR05
U 1 1 5E5114B1
P 3300 1500
F 0 "#PWR05" H 3300 1250 50  0001 C CNN
F 1 "GND" H 3300 1350 50  0000 C CNN
F 2 "" H 3300 1500 50  0001 C CNN
F 3 "" H 3300 1500 50  0001 C CNN
	1    3300 1500
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+5V #PWR06
U 1 1 5E511510
P 3300 1100
F 0 "#PWR06" H 3300 950 50  0001 C CNN
F 1 "+5V" H 3300 1240 50  0000 C CNN
F 2 "" H 3300 1100 50  0001 C CNN
F 3 "" H 3300 1100 50  0001 C CNN
	1    3300 1100
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C4
U 1 1 5E5119BD
P 3250 3350
F 0 "C4" H 3260 3420 50  0000 L CNN
F 1 "100nF" H 3260 3270 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 3250 3350 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C315C104M5U5TA7303.pdf" H 3250 3350 50  0001 C CNN
F 4 "399-9859-1-ND" H 3250 3350 60  0001 C CNN "DigiKey PN"
F 5 "0.37" H 3250 3350 60  0001 C CNN "Price"
	1    3250 3350
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR07
U 1 1 5E5119C3
P 3250 3550
F 0 "#PWR07" H 3250 3300 50  0001 C CNN
F 1 "GND" H 3250 3400 50  0000 C CNN
F 2 "" H 3250 3550 50  0001 C CNN
F 3 "" H 3250 3550 50  0001 C CNN
	1    3250 3550
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+3V3 #PWR08
U 1 1 5E511AB3
P 3250 3150
F 0 "#PWR08" H 3250 3000 50  0001 C CNN
F 1 "+3V3" H 3250 3290 50  0000 C CNN
F 2 "" H 3250 3150 50  0001 C CNN
F 3 "" H 3250 3150 50  0001 C CNN
	1    3250 3150
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR09
U 1 1 5E512027
P 6500 4250
F 0 "#PWR09" H 6500 4000 50  0001 C CNN
F 1 "GND" H 6350 4200 50  0000 C CNN
F 2 "" H 6500 4250 50  0001 C CNN
F 3 "" H 6500 4250 50  0001 C CNN
	1    6500 4250
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+5V #PWR010
U 1 1 5E512301
P 6500 4000
F 0 "#PWR010" H 6500 3850 50  0001 C CNN
F 1 "+5V" H 6500 4140 50  0000 C CNN
F 2 "" H 6500 4000 50  0001 C CNN
F 3 "" H 6500 4000 50  0001 C CNN
	1    6500 4000
	1    0    0    -1  
$EndComp
NoConn ~ 7700 4100
NoConn ~ 7700 4700
NoConn ~ 7700 4800
$Comp
L RetroWiFiModem:GND #PWR011
U 1 1 5E5128D4
P 7300 3300
F 0 "#PWR011" H 7300 3050 50  0001 C CNN
F 1 "GND" H 7300 3150 50  0000 C CNN
F 2 "" H 7300 3300 50  0001 C CNN
F 3 "" H 7300 3300 50  0001 C CNN
	1    7300 3300
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+5V #PWR012
U 1 1 5E512A31
P 6800 2600
F 0 "#PWR012" H 6800 2450 50  0001 C CNN
F 1 "+5V" H 6800 2740 50  0000 C CNN
F 2 "" H 6800 2600 50  0001 C CNN
F 3 "" H 6800 2600 50  0001 C CNN
	1    6800 2600
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+3V3 #PWR013
U 1 1 5E512B5E
P 7800 2600
F 0 "#PWR013" H 7800 2450 50  0001 C CNN
F 1 "+3V3" H 7800 2740 50  0000 C CNN
F 2 "" H 7800 2600 50  0001 C CNN
F 3 "" H 7800 2600 50  0001 C CNN
	1    7800 2600
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C7
U 1 1 5E51312D
P 7800 3050
F 0 "C7" H 7810 3120 50  0000 L CNN
F 1 "1uF" H 7810 2970 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 7800 3050 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/datasheet/T350A105K035AT.pdf" H 7800 3050 50  0001 C CNN
F 4 "399-3529-ND" H 7800 3050 60  0001 C CNN "DigiKey PN"
F 5 "1.16" H 7800 3050 60  0001 C CNN "Price"
	1    7800 3050
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR014
U 1 1 5E5131EF
P 7800 3300
F 0 "#PWR014" H 7800 3050 50  0001 C CNN
F 1 "GND" H 7800 3150 50  0000 C CNN
F 2 "" H 7800 3300 50  0001 C CNN
F 3 "" H 7800 3300 50  0001 C CNN
	1    7800 3300
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR015
U 1 1 5E5140A7
P 3500 5800
F 0 "#PWR015" H 3500 5550 50  0001 C CNN
F 1 "GND" H 3500 5650 50  0000 C CNN
F 2 "" H 3500 5800 50  0001 C CNN
F 3 "" H 3500 5800 50  0001 C CNN
	1    3500 5800
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+3V3 #PWR016
U 1 1 5E51674A
P 5900 4375
F 0 "#PWR016" H 5900 4225 50  0001 C CNN
F 1 "+3V3" H 5900 4515 50  0000 C CNN
F 2 "" H 5900 4375 50  0001 C CNN
F 3 "" H 5900 4375 50  0001 C CNN
	1    5900 4375
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR017
U 1 1 5E51A647
P 5900 5350
F 0 "#PWR017" H 5900 5100 50  0001 C CNN
F 1 "GND" H 5900 5200 50  0000 C CNN
F 2 "" H 5900 5350 50  0001 C CNN
F 3 "" H 5900 5350 50  0001 C CNN
	1    5900 5350
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:PWR_FLAG #FLG018
U 1 1 5E51AA10
P 7000 3300
F 0 "#FLG018" H 7000 3395 50  0001 C CNN
F 1 "PWR_FLAG" H 7000 3480 50  0000 C CNN
F 2 "" H 7000 3300 50  0001 C CNN
F 3 "" H 7000 3300 50  0001 C CNN
	1    7000 3300
	-1   0    0    1   
$EndComp
Text Notes 4125 4900 0    50   ~ 0
RTS
Text Notes 4125 4800 0    50   ~ 0
TxD
Text Notes 4125 4600 0    50   ~ 0
CTS
Text Notes 4125 4500 0    50   ~ 0
RxD
Text Notes 1150 3600 0    50   ~ 0
RS
Text Notes 1150 3300 0    50   ~ 0
CS
$Comp
L RetroWiFiModem:74LS32 U3
U 2 1 5E515F0D
P 9000 2675
F 0 "U3" H 9000 2725 50  0000 C CNN
F 1 "74HC32" H 9000 2625 50  0000 C CNN
F 2 "modules:SOIC-14_3.9x8.7mm_P1.27mm" H 9000 2675 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74hc32" H 9000 2675 50  0001 C CNN
F 4 "296-1589-5-ND" H 9000 2675 60  0001 C CNN "DigiKey PN"
F 5 "0.63" H 9000 2675 60  0001 C CNN "Price"
	2    9000 2675
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:74LS32 U3
U 3 1 5E516004
P 9000 1675
F 0 "U3" H 9000 1725 50  0000 C CNN
F 1 "74HC32" H 9000 1625 50  0000 C CNN
F 2 "modules:SOIC-14_3.9x8.7mm_P1.27mm" H 9000 1675 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74hc32" H 9000 1675 50  0001 C CNN
F 4 "296-1589-5-ND" H 9000 1675 60  0001 C CNN "DigiKey PN"
F 5 "0.63" H 9000 1675 60  0001 C CNN "Price"
	3    9000 1675
	-1   0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:74LS32 U3
U 4 1 5E5160DA
P 9000 2175
F 0 "U3" H 9000 2225 50  0000 C CNN
F 1 "74HC32" H 9000 2125 50  0000 C CNN
F 2 "modules:SOIC-14_3.9x8.7mm_P1.27mm" H 9000 2175 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74hc32" H 9000 2175 50  0001 C CNN
F 4 "296-1589-5-ND" H 9000 2175 60  0001 C CNN "DigiKey PN"
F 5 "0.63" H 9000 2175 60  0001 C CNN "Price"
	4    9000 2175
	-1   0    0    -1  
$EndComp
NoConn ~ 8400 1675
NoConn ~ 8400 2175
$Comp
L RetroWiFiModem:C_Small C8
U 1 1 5E6067DF
P 9050 1025
F 0 "C8" H 9060 1095 50  0000 L CNN
F 1 "100nF" H 9060 945 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 9050 1025 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C315C104M5U5TA7303.pdf" H 9050 1025 50  0001 C CNN
F 4 "399-9859-1-ND" H 9050 1025 60  0001 C CNN "DigiKey PN"
F 5 "0.37" H 9050 1025 60  0001 C CNN "Price"
	1    9050 1025
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR019
U 1 1 5E6067E5
P 9050 1225
F 0 "#PWR019" H 9050 975 50  0001 C CNN
F 1 "GND" H 9050 1075 50  0000 C CNN
F 2 "" H 9050 1225 50  0001 C CNN
F 3 "" H 9050 1225 50  0001 C CNN
	1    9050 1225
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+3V3 #PWR020
U 1 1 5E6068E2
P 9050 825
F 0 "#PWR020" H 9050 675 50  0001 C CNN
F 1 "+3V3" H 9050 965 50  0000 C CNN
F 2 "" H 9050 825 50  0001 C CNN
F 3 "" H 9050 825 50  0001 C CNN
	1    9050 825 
	1    0    0    -1  
$EndComp
Text Notes 1825 5300 0    50   ~ 0
RxD
Text Notes 1150 5200 0    50   ~ 0
CTS
Text Notes 1825 5200 0    50   ~ 0
TxD
Text Notes 1150 5300 0    50   ~ 0
RTS
Text Notes 1150 3000 0    50   ~ 0
CD
Text Notes 1175 2700 0    50   ~ 0
RI
Text Notes 1150 2400 0    50   ~ 0
RD
Text Notes 1150 2100 0    50   ~ 0
SD
Text Notes 1150 1800 0    50   ~ 0
TR
Text Notes 1150 1500 0    50   ~ 0
MR
$Comp
L RetroWiFiModem:+5V #PWR021
U 1 1 5E60C057
P 3600 1550
F 0 "#PWR021" H 3600 1400 50  0001 C CNN
F 1 "+5V" H 3600 1690 50  0000 C CNN
F 2 "" H 3600 1550 50  0001 C CNN
F 3 "" H 3600 1550 50  0001 C CNN
	1    3600 1550
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR022
U 1 1 5E60CB2A
P 3600 3050
F 0 "#PWR022" H 3600 2800 50  0001 C CNN
F 1 "GND" H 3600 2900 50  0000 C CNN
F 2 "" H 3600 3050 50  0000 C CNN
F 3 "" H 3600 3050 50  0001 C CNN
	1    3600 3050
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR023
U 1 1 5E71271D
P 6600 2300
F 0 "#PWR023" H 6600 2050 50  0001 C CNN
F 1 "GND" H 6600 2150 50  0000 C CNN
F 2 "" H 6600 2300 50  0001 C CNN
F 3 "" H 6600 2300 50  0001 C CNN
	1    6600 2300
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:PWR_FLAG #FLG024
U 1 1 5E712943
P 6500 3000
F 0 "#FLG024" H 6500 3095 50  0001 C CNN
F 1 "PWR_FLAG" H 6500 3180 50  0000 C CNN
F 2 "" H 6500 3000 50  0001 C CNN
F 3 "" H 6500 3000 50  0001 C CNN
	1    6500 3000
	-1   0    0    1   
$EndComp
$Comp
L RetroWiFiModem:BARREL_JACK CON1
U 1 1 5E71A7E2
P 7000 2000
F 0 "CON1" H 7000 2250 50  0000 C CNN
F 1 "BARREL_JACK" H 7000 1800 50  0000 C CNN
F 2 "modules:BARREL_JACK" H 7000 2000 50  0001 C CNN
F 3 "http://www.tensility.com/pdffiles/54-00166.pdf" H 7000 2000 50  0001 C CNN
F 4 "839-54-00166-ND" H 7000 2000 60  0001 C CNN "DigiKey PN"
F 5 "0.72" H 7000 2000 60  0001 C CNN "Price"
	1    7000 2000
	-1   0    0    -1  
$EndComp
NoConn ~ 6700 2000
NoConn ~ 8400 2675
$Comp
L RetroWiFiModem:GND #PWR025
U 1 1 5E76ACDD
P 9700 2875
F 0 "#PWR025" H 9700 2625 50  0001 C CNN
F 1 "GND" H 9700 2725 50  0000 C CNN
F 2 "" H 9700 2875 50  0001 C CNN
F 3 "" H 9700 2875 50  0001 C CNN
	1    9700 2875
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 8 1 5E880893
P 1900 3600
F 0 "R1" V 1980 3600 50  0000 C CNN
F 1 "560R" V 1820 3600 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 3600 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 3600 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 3600 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 3600 60  0001 C CNN "Price"
	8    1900 3600
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 7 1 5E880A81
P 1900 3300
F 0 "R1" V 1980 3300 50  0000 C CNN
F 1 "560R" V 1820 3300 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 3300 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 3300 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 3300 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 3300 60  0001 C CNN "Price"
	7    1900 3300
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 6 1 5E880BA6
P 1900 3000
F 0 "R1" V 1980 3000 50  0000 C CNN
F 1 "560R" V 1820 3000 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 3000 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 3000 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 3000 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 3000 60  0001 C CNN "Price"
	6    1900 3000
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 5 1 5E880CB0
P 1900 2700
F 0 "R1" V 1980 2700 50  0000 C CNN
F 1 "560R" V 1820 2700 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 2700 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 2700 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 2700 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 2700 60  0001 C CNN "Price"
	5    1900 2700
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 4 1 5E880E1F
P 1900 2400
F 0 "R1" V 1980 2400 50  0000 C CNN
F 1 "560R" V 1820 2400 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 2400 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 2400 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 2400 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 2400 60  0001 C CNN "Price"
	4    1900 2400
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 3 1 5E880FF5
P 1900 2100
F 0 "R1" V 1980 2100 50  0000 C CNN
F 1 "560R" V 1820 2100 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 2100 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 2100 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 2100 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 2100 60  0001 C CNN "Price"
	3    1900 2100
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 2 1 5E8810FD
P 1900 1800
F 0 "R1" V 1980 1800 50  0000 C CNN
F 1 "560R" V 1820 1800 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 1800 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 1800 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 1800 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 1800 60  0001 C CNN "Price"
	2    1900 1800
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_Pack08_US_Split R1
U 1 1 5E881203
P 1900 1500
F 0 "R1" V 1980 1500 50  0000 C CNN
F 1 "560R" V 1820 1500 50  0000 C CNN
F 2 "modules:DIP-16_W7.62mm_LongPads" H 1900 1500 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 1900 1500 60  0001 C CNN
F 4 "CF18JT560RCT-ND" V 1900 1500 60  0001 C CNN "DigiKey PN"
F 5 "0.16" V 1900 1500 60  0001 C CNN "Price"
	1    1900 1500
	0    -1   -1   0   
$EndComp
$Comp
L RetroWiFiModem:R_US R9
U 1 1 5E8813FD
P 8200 4200
F 0 "R9" H 8050 4375 50  0000 C CNN
F 1 "10K" H 8075 4275 50  0000 C CNN
F 2 "modules:R3" H 8200 4200 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 8200 4200 60  0001 C CNN
F 4 "CF18JT10K0CT-ND" H 8200 4200 60  0001 C CNN "DigiKey PN"
F 5 "0.16" H 8200 4200 60  0001 C CNN "Price"
	1    8200 4200
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:MAX3237CAI+ U1
U 1 1 635356A1
P 3500 4700
F 0 "U1" H 3125 5550 60  0000 C CNN
F 1 "MAX3237CAI+" H 3125 5450 60  0000 C CNN
F 2 "modules:SOIC-28W_7.5x17.9mm_Pitch1.27mm" H 3000 5450 60  0001 C CNN
F 3 "" H 2750 5300 60  0000 C CNN
	1    3500 4700
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:74LS245A U2
U 1 1 635358A6
P 3600 2300
F 0 "U2" H 3700 2875 50  0000 L BNN
F 1 "74HCT245" H 3650 1725 50  0000 L TNN
F 2 "modules:SOIC-20W_7.5x12.8mm_P1.27mm" H 3600 2300 50  0001 C CNN
F 3 "" H 3600 2300 50  0000 C CNN
	1    3600 2300
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+5V #PWR026
U 1 1 63535B3F
P 3000 2650
F 0 "#PWR026" H 3000 2500 50  0001 C CNN
F 1 "+5V" H 2900 2675 50  0000 C CNN
F 2 "" H 3000 2650 50  0001 C CNN
F 3 "" H 3000 2650 50  0001 C CNN
	1    3000 2650
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:C_Small C3
U 1 1 5E5106EA
P 4100 3875
F 0 "C3" H 4125 3950 50  0000 L CNN
F 1 "100nF" H 4125 3800 50  0000 L CNN
F 2 "modules:C_Disc_D3_P2.5" H 4100 3875 50  0001 C CNN
F 3 "https://api.kemet.com/component-edge/download/specsheet/C315C104M5U5TA7303.pdf" H 4100 3875 50  0001 C CNN
F 4 "399-9859-1-ND" V 4100 3875 60  0001 C CNN "DigiKey PN"
F 5 "0.37" V 4100 3875 60  0001 C CNN "Price"
	1    4100 3875
	1    0    0    -1  
$EndComp
Text Notes 1150 5100 0    50   ~ 0
RI
NoConn ~ 1300 5000
Text Notes 1150 5400 0    50   ~ 0
DSR
Text Notes 1825 5100 0    50   ~ 0
DTR
Text Notes 1825 5400 0    50   ~ 0
DCD
$Comp
L RetroWiFiModem:+3V3 #PWR027
U 1 1 6353B51F
P 2875 5350
F 0 "#PWR027" H 2875 5200 50  0001 C CNN
F 1 "+3V3" H 2725 5400 50  0000 C CNN
F 2 "" H 2875 5350 50  0001 C CNN
F 3 "" H 2875 5350 50  0001 C CNN
	1    2875 5350
	1    0    0    -1  
$EndComp
Text Notes 4125 5100 0    50   ~ 0
DTR
Text Notes 4125 4700 0    50   ~ 0
DCD
Text Notes 4125 5200 0    50   ~ 0
RI
Text Notes 4125 5000 0    50   ~ 0
DSR
NoConn ~ 4050 5400
$Comp
L RetroWiFiModem:GND #PWR028
U 1 1 6353CD19
P 4100 5575
F 0 "#PWR028" H 4100 5325 50  0001 C CNN
F 1 "GND" H 4100 5425 50  0000 C CNN
F 2 "" H 4100 5575 50  0001 C CNN
F 3 "" H 4100 5575 50  0001 C CNN
	1    4100 5575
	1    0    0    -1  
$EndComp
Text Notes 7675 4200 0    50   ~ 0
CTS
Text Notes 7675 4300 0    50   ~ 0
RTS
Text Notes 7675 4400 0    50   ~ 0
RI
Text Notes 6600 4500 0    50   ~ 0
DSR
Text Notes 6600 4600 0    50   ~ 0
DCD
Text Notes 7675 4500 0    50   ~ 0
TXEN
Wire Wire Line
	1800 5200 2350 5200
Connection ~ 8200 4500
Wire Wire Line
	8200 3950 8200 4100
Wire Wire Line
	1100 1300 1100 1500
Wire Wire Line
	1100 3600 1300 3600
Wire Wire Line
	1300 3300 1100 3300
Connection ~ 1100 3300
Wire Wire Line
	1300 3000 1100 3000
Connection ~ 1100 3000
Wire Wire Line
	1300 2700 1100 2700
Connection ~ 1100 2700
Wire Wire Line
	1300 2400 1100 2400
Connection ~ 1100 2400
Wire Wire Line
	1300 2100 1100 2100
Connection ~ 1100 2100
Wire Wire Line
	1300 1800 1100 1800
Connection ~ 1100 1800
Wire Wire Line
	1300 1500 1100 1500
Connection ~ 1100 1500
Wire Wire Line
	1600 1500 1800 1500
Wire Wire Line
	1800 1800 1600 1800
Wire Wire Line
	1600 2100 1800 2100
Wire Wire Line
	1800 2400 1600 2400
Wire Wire Line
	1600 2700 1800 2700
Wire Wire Line
	1800 3000 1600 3000
Wire Wire Line
	1600 3300 1800 3300
Wire Wire Line
	1600 3600 1800 3600
Wire Wire Line
	2200 1800 3100 1800
Wire Wire Line
	2200 1800 2200 1500
Wire Wire Line
	2200 1500 2000 1500
Wire Wire Line
	2000 1800 2100 1800
Wire Wire Line
	2100 1800 2100 1900
Wire Wire Line
	2100 1900 3100 1900
Wire Wire Line
	2100 2000 3100 2000
Wire Wire Line
	2100 2000 2100 2100
Wire Wire Line
	2100 2100 2000 2100
Wire Wire Line
	2000 2400 2200 2400
Wire Wire Line
	2200 2400 2200 2100
Wire Wire Line
	2200 2100 3100 2100
Wire Wire Line
	2300 2200 3100 2200
Wire Wire Line
	2300 2200 2300 2700
Wire Wire Line
	2300 2700 2000 2700
Wire Wire Line
	2400 2300 3100 2300
Wire Wire Line
	2400 2300 2400 3000
Wire Wire Line
	2400 3000 2000 3000
Wire Wire Line
	2000 3300 2500 3300
Wire Wire Line
	2500 3300 2500 2400
Wire Wire Line
	2500 2400 3100 2400
Wire Wire Line
	2600 2500 3100 2500
Wire Wire Line
	2600 2500 2600 3600
Wire Wire Line
	2600 3600 2000 3600
Wire Wire Line
	7700 4200 8000 4200
Wire Wire Line
	8000 4200 8000 5775
Wire Wire Line
	8200 4300 8200 4500
Wire Wire Line
	6300 5100 8200 5100
Wire Wire Line
	7700 4400 8100 4400
Wire Wire Line
	3100 2800 3000 2800
Wire Wire Line
	2400 4300 2950 4300
Wire Wire Line
	1975 4300 1975 4550
Wire Wire Line
	1975 4300 2200 4300
Wire Wire Line
	3300 1100 3300 1200
Wire Wire Line
	3300 1400 3300 1500
Wire Wire Line
	3250 3450 3250 3550
Wire Wire Line
	3250 3150 3250 3200
Wire Wire Line
	3250 3200 3500 3200
Wire Wire Line
	3500 3200 3500 3675
Connection ~ 3250 3200
Wire Wire Line
	6500 4250 6500 4200
Wire Wire Line
	6500 4200 6700 4200
Wire Wire Line
	6500 4000 6500 4100
Wire Wire Line
	6500 4100 6700 4100
Wire Wire Line
	7300 3100 7300 3200
Wire Wire Line
	6800 2800 6800 2600
Wire Wire Line
	7800 2600 7800 2800
Wire Wire Line
	7800 3300 7800 3150
Connection ~ 7800 2800
Wire Wire Line
	3500 5800 3500 5700
Wire Wire Line
	6500 2800 6800 2800
Wire Wire Line
	7800 2800 7700 2800
Wire Wire Line
	5900 4375 5900 4800
Wire Wire Line
	7700 4300 7900 4300
Wire Wire Line
	7900 4300 7900 5700
Wire Wire Line
	5900 5350 5900 5200
Wire Wire Line
	7000 3300 7000 3200
Wire Wire Line
	7000 3200 7300 3200
Connection ~ 7300 3200
Wire Wire Line
	4850 2000 4850 4800
Wire Wire Line
	4850 5600 6550 5600
Wire Wire Line
	6550 5600 6550 4700
Wire Wire Line
	6500 1900 6500 2800
Connection ~ 6800 2800
Wire Wire Line
	9700 1775 9600 1775
Connection ~ 9700 1775
Wire Wire Line
	9600 1575 9700 1575
Wire Wire Line
	9700 2075 9600 2075
Connection ~ 9700 2075
Wire Wire Line
	8200 4500 7700 4500
Wire Wire Line
	9050 825  9050 925 
Wire Wire Line
	9050 1125 9050 1225
Wire Wire Line
	3600 1550 3600 1650
Wire Wire Line
	3600 3050 3600 2950
Wire Wire Line
	6600 2100 6600 2300
Connection ~ 6500 2800
Wire Wire Line
	6700 2100 6600 2100
Wire Wire Line
	6500 1900 6700 1900
Wire Wire Line
	9700 1575 9700 1775
Wire Wire Line
	9600 2775 9700 2775
Connection ~ 9700 2775
Wire Wire Line
	9600 2575 9700 2575
Connection ~ 9700 2575
Wire Wire Line
	9600 2275 9700 2275
Connection ~ 9700 2275
Wire Wire Line
	1800 5300 2300 5300
Wire Wire Line
	1300 5300 1125 5300
Wire Wire Line
	1125 5300 1125 5625
Wire Wire Line
	1050 5700 1050 5200
Wire Wire Line
	1050 5200 1300 5200
Wire Wire Line
	1875 5000 1800 5000
Wire Wire Line
	1875 4550 1875 5000
Wire Wire Line
	3000 2800 3000 2900
Wire Wire Line
	3000 2650 3000 2700
Wire Wire Line
	3000 2700 3100 2700
Wire Wire Line
	4200 4100 4050 4100
Wire Wire Line
	4200 4300 4050 4300
Wire Wire Line
	4100 3975 4100 4200
Wire Wire Line
	4100 4200 4050 4200
Wire Wire Line
	4100 3775 4100 3675
Wire Wire Line
	4100 3675 3500 3675
Connection ~ 3500 3675
Wire Wire Line
	2500 4150 2500 4200
Wire Wire Line
	2500 4200 2950 4200
Wire Wire Line
	2775 4100 2950 4100
Wire Wire Line
	2775 4100 2775 3900
Wire Wire Line
	2775 3900 2500 3900
Wire Wire Line
	2500 3900 2500 3950
Wire Wire Line
	1875 4550 1975 4550
Connection ~ 1975 4550
Wire Wire Line
	1800 5100 2950 5100
Wire Wire Line
	2350 5200 2350 4800
Wire Wire Line
	2350 4800 2950 4800
Wire Wire Line
	2300 5300 2300 4500
Wire Wire Line
	2300 4500 2950 4500
Wire Wire Line
	1800 5400 2450 5400
Wire Wire Line
	2450 5400 2450 4700
Wire Wire Line
	2450 4700 2950 4700
Wire Wire Line
	1050 5700 2400 5700
Wire Wire Line
	2400 5700 2400 4600
Wire Wire Line
	2400 4600 2950 4600
Wire Wire Line
	1125 5625 2500 5625
Wire Wire Line
	2500 5625 2500 4900
Wire Wire Line
	2500 4900 2950 4900
Wire Wire Line
	1300 5400 1200 5400
Wire Wire Line
	1200 5400 1200 5550
Wire Wire Line
	1200 5550 2550 5550
Wire Wire Line
	2550 5550 2550 5000
Wire Wire Line
	2550 5000 2950 5000
Wire Wire Line
	2600 5200 2950 5200
Wire Wire Line
	2600 5200 2600 5775
Wire Wire Line
	2600 5775 975  5775
Wire Wire Line
	975  5775 975  5100
Wire Wire Line
	975  5100 1300 5100
Wire Wire Line
	2875 5350 2875 5500
Wire Wire Line
	2875 5500 2950 5500
Wire Wire Line
	2800 5400 2800 6075
Wire Wire Line
	2800 5400 2950 5400
Wire Wire Line
	4050 4500 4775 4500
Wire Wire Line
	4775 2100 4775 4500
Wire Wire Line
	4775 5000 5100 5000
Wire Wire Line
	4850 4800 4050 4800
Wire Wire Line
	4100 5575 4100 5500
Wire Wire Line
	4100 5500 4050 5500
Wire Wire Line
	4050 5200 4625 5200
Wire Wire Line
	4625 2200 4625 5200
Wire Wire Line
	4625 5850 8100 5850
Wire Wire Line
	6550 4700 6700 4700
Wire Wire Line
	8000 5775 4400 5775
Wire Wire Line
	4400 5775 4400 4600
Wire Wire Line
	4400 4600 4050 4600
Wire Wire Line
	7900 5700 4475 5700
Wire Wire Line
	4475 5700 4475 4900
Wire Wire Line
	4475 4900 4050 4900
Wire Wire Line
	6700 4600 4700 4600
Wire Wire Line
	4700 2300 4700 4600
Wire Wire Line
	4700 4700 4050 4700
Wire Wire Line
	4550 5000 4050 5000
Wire Wire Line
	4550 1800 4550 4300
Wire Wire Line
	4550 4300 5150 4300
Wire Wire Line
	5150 4500 6700 4500
Wire Wire Line
	2800 6075 8200 6075
Connection ~ 8200 5100
Wire Wire Line
	6700 4400 4925 4400
Wire Wire Line
	4925 1900 4925 4400
Wire Wire Line
	4925 5100 4050 5100
Wire Wire Line
	4100 1900 4925 1900
Connection ~ 4925 4400
Wire Wire Line
	4100 2000 4850 2000
Connection ~ 4850 4800
Wire Wire Line
	4775 2100 4100 2100
Connection ~ 4775 4500
Wire Wire Line
	4700 2300 4100 2300
Connection ~ 4700 4600
Wire Wire Line
	4625 2200 4100 2200
Connection ~ 4625 5200
Wire Wire Line
	4475 2500 4100 2500
Connection ~ 4475 4900
Wire Wire Line
	6300 4900 6625 4900
Wire Wire Line
	6625 4900 6625 4800
Wire Wire Line
	6625 4800 6700 4800
Wire Wire Line
	8100 5850 8100 4400
Text Notes 6600 4400 0    50   ~ 0
DTR
Wire Wire Line
	4400 2400 4100 2400
Connection ~ 4400 4600
Wire Wire Line
	5150 4300 5150 4500
Connection ~ 4550 4300
Wire Wire Line
	4550 1800 4100 1800
$Comp
L RetroWiFiModem:WeMos_mini U5
U 1 1 6353700A
P 7200 4450
F 0 "U5" H 7200 4950 60  0000 C CNN
F 1 "WeMos_mini" H 7200 3950 60  0000 C CNN
F 2 "modules:wemos-d1-mini-with-pin-header-and-connector" H 7750 3750 60  0001 C CNN
F 3 "" H 7750 3750 60  0000 C CNN
	1    7200 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4500 8200 5100
Wire Wire Line
	1100 3300 1100 3600
Wire Wire Line
	1100 3000 1100 3300
Wire Wire Line
	1100 2700 1100 3000
Wire Wire Line
	1100 2400 1100 2700
Wire Wire Line
	1100 2100 1100 2400
Wire Wire Line
	1100 1800 1100 2100
Wire Wire Line
	1100 1500 1100 1800
Wire Wire Line
	3250 3200 3250 3250
Wire Wire Line
	7800 2800 7800 2950
Wire Wire Line
	7300 3200 7300 3300
Wire Wire Line
	6800 2800 6900 2800
Wire Wire Line
	9700 1775 9700 2075
Wire Wire Line
	9700 2075 9700 2275
Wire Wire Line
	6500 2800 6500 3000
Wire Wire Line
	9700 2775 9700 2875
Wire Wire Line
	9700 2575 9700 2775
Wire Wire Line
	9700 2275 9700 2575
Wire Wire Line
	3500 3675 3500 3900
Wire Wire Line
	1975 4550 1975 4650
Wire Wire Line
	8200 5100 8200 6075
Wire Wire Line
	4925 4400 4925 5100
Wire Wire Line
	4850 4800 4850 5600
Wire Wire Line
	4775 4500 4775 5000
Wire Wire Line
	4700 4600 4700 4700
Wire Wire Line
	4625 5200 4625 5850
Wire Wire Line
	4475 4900 4475 2500
Wire Wire Line
	4400 4600 4400 2400
Wire Wire Line
	4550 4300 4550 5000
$Comp
L RetroWiFiModem:DFPlayer_Mini U6
U 1 1 637662DE
P 9375 4150
F 0 "U6" H 9375 4737 60  0000 C CNN
F 1 "DFPlayer_Mini" H 9375 4631 60  0000 C CNN
F 2 "modules:DFPlayerMini" H 9375 4050 60  0001 C CNN
F 3 "" H 9375 4050 60  0001 C CNN
	1    9375 4150
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:GND #PWR024
U 1 1 6377F2CB
P 8550 4550
F 0 "#PWR024" H 8550 4300 50  0001 C CNN
F 1 "GND" H 8550 4400 50  0000 C CNN
F 2 "" H 8550 4550 50  0001 C CNN
F 3 "" H 8550 4550 50  0001 C CNN
	1    8550 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	8550 4450 8825 4450
$Comp
L RetroWiFiModem:GND #PWR030
U 1 1 6378C250
P 10025 4650
F 0 "#PWR030" H 10025 4400 50  0001 C CNN
F 1 "GND" H 10025 4500 50  0000 C CNN
F 2 "" H 10025 4650 50  0001 C CNN
F 3 "" H 10025 4650 50  0001 C CNN
	1    10025 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	10025 4650 10025 4450
Wire Wire Line
	10025 4450 9925 4450
Wire Wire Line
	8550 4450 8550 4550
$Comp
L RetroWiFiModem:+5V #PWR029
U 1 1 637A5375
P 8725 3775
F 0 "#PWR029" H 8725 3625 50  0001 C CNN
F 1 "+5V" H 8725 3915 50  0000 C CNN
F 2 "" H 8725 3775 50  0001 C CNN
F 3 "" H 8725 3775 50  0001 C CNN
	1    8725 3775
	1    0    0    -1  
$EndComp
Wire Wire Line
	8725 3775 8725 3850
Wire Wire Line
	8725 3850 8825 3850
NoConn ~ 8825 4150
NoConn ~ 8825 4250
NoConn ~ 8825 4050
NoConn ~ 9925 3950
NoConn ~ 9925 4050
NoConn ~ 9925 4150
NoConn ~ 9925 4550
$Comp
L Device:Speaker LS1
U 1 1 63821DE1
P 9025 4900
F 0 "LS1" H 9195 4896 50  0000 L CNN
F 1 "Speaker" H 9195 4805 50  0000 L CNN
F 2 "modules:PinHeader_1x02_P2.54mm_Vertical" H 9025 4700 50  0001 C CNN
F 3 "~" H 9015 4850 50  0001 C CNN
	1    9025 4900
	1    0    0    -1  
$EndComp
Wire Wire Line
	8825 4550 8775 4550
Wire Wire Line
	8775 4550 8775 4900
Wire Wire Line
	8775 4900 8825 4900
Wire Wire Line
	8825 5000 8700 5000
Wire Wire Line
	8700 5000 8700 4350
Wire Wire Line
	8700 4350 8825 4350
Wire Wire Line
	8825 3950 8525 3950
Wire Wire Line
	8525 3950 8525 3725
Wire Wire Line
	8525 3725 6625 3725
Wire Wire Line
	6625 3725 6625 4300
Wire Wire Line
	6625 4300 6700 4300
$Comp
L Diode:1N4148 D9
U 1 1 6385DCFD
P 9375 5425
F 0 "D9" H 9375 5208 50  0000 C CNN
F 1 "1N4148" H 9375 5299 50  0000 C CNN
F 2 "modules:D_DO-35_SOD27_P7.62mm_Horizontal" H 9375 5250 50  0001 C CNN
F 3 "https://assets.nexperia.com/documents/data-sheet/1N4148_1N4448.pdf" H 9375 5425 50  0001 C CNN
	1    9375 5425
	-1   0    0    1   
$EndComp
Wire Wire Line
	9925 3850 10200 3850
Wire Wire Line
	10200 3850 10200 5425
Wire Wire Line
	10200 5425 9525 5425
$Comp
L RetroWiFiModem:R_US R10
U 1 1 6387B35A
P 8400 4200
F 0 "R10" H 8500 4375 50  0000 C CNN
F 1 "10K" H 8525 4275 50  0000 C CNN
F 2 "modules:R3" H 8400 4200 60  0001 C CNN
F 3 "https://www.seielect.com/catalog/sei-cf_cfm.pdf" H 8400 4200 60  0001 C CNN
F 4 "CF18JT10K0CT-ND" H 8400 4200 60  0001 C CNN "DigiKey PN"
F 5 "0.16" H 8400 4200 60  0001 C CNN "Price"
	1    8400 4200
	1    0    0    -1  
$EndComp
$Comp
L RetroWiFiModem:+3V3 #PWR018
U 1 1 6387E865
P 8400 3950
F 0 "#PWR018" H 8400 3800 50  0001 C CNN
F 1 "+3V3" H 8400 4090 50  0000 C CNN
F 2 "" H 8400 3950 50  0001 C CNN
F 3 "" H 8400 3950 50  0001 C CNN
	1    8400 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8400 4300 8400 4600
Wire Wire Line
	8400 4600 7700 4600
Wire Wire Line
	8400 4600 8400 5425
Wire Wire Line
	8400 5425 9225 5425
Connection ~ 8400 4600
Wire Wire Line
	8400 3950 8400 4100
NoConn ~ 9925 4250
NoConn ~ 9925 4350
$EndSCHEMATC
