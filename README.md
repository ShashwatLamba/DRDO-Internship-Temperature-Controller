# DRDO-Internship-Temperature-Controller
Temperature Controller project using thermistor sensor — analog (Op-Amp) and digital (Arduino PID) designs developed during DRDO internship under Mr. Pankaj Aggarwal (June–July 2025)

A closed loop temperture control can be made using 2 approaches.

1) Using a Microcontroller
Any microcontroller could be used taken as the primary controll unit.
In this prooject, an Arduino was used to sense and regulate temperature using a thermistor as the feedback element.

The microcontroller reads the temperature value(converted from thermistor's resistance), compares it with a referense setpoint, and adjusts the output accordingly using PID control logic.

This output drives the heater or cooling element to maintain the desired temperature precisely.

Key Components
1) Arduino Uno
2) NTC Thermistor
3) MOSFET
4) PID controll algorithm
5) Potentiometer


2) Using an analog Ciruit
In this approach, the temperature controller is designed using operational amplifier (op-amp) in Multisim.

The LM-35 sensor is utilised because of its linearly characteristics of temperature with voltage.

The voltage produced form the LM-35 sensor is then compared with a reference voltage using a differential amplifier configuration.

The difference in the voltages is then fed to a PID configuration using 3 op-amps.

The output of the combination of the PID configuration is summed up using a summer and this output is used in a gate driver IC.

Key componenets:
1) LM - 35
2) Op - amp (LM 741)
3) Potentiometer (providing reference voltage)
4) Driver IC
5) Heater
