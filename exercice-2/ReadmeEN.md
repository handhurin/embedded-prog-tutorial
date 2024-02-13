# Exercise 2: Embedded programming

In this exercise we are going to introduce the concepts of bare metal embedded programming. The idea is to focus on bare metal programming around a use case based on the LM75. In particular, we will look at
- The concept of hardware driver, how to write a driver. What are the right formalisms to adopt
- The concept of interrupts, in particular using the LM75's overtemperature output.
- What are the standards to be respected in embedded programming?

Low-level driver programming is not covered by this exercise. It is a long and tedious exercise, especially for fairly large microcontrollers such as the STM32H7. I recommend practising on 8-bit AVR processors to code low-level drivers. 

## 1. Use Case

In this exercise we are going to program a temperature control system in bare metal. The specifications are as follows:
- The temperature must be measured every second and stored internally.
- Between each temperature measurement, the micro-controller must switch to low power.
- A button must be used to download all the data via the serial link (uart print connected to the STLINK).
- At any time, if the temperature exceeds a threshold of 30°, the system must indicate that an overtemperature has been detected by means of a light signal.

## 2. LM75 Equipment Driver

In this section, the aim is to create an equipment driver for the LM75. We propose to limit ourselves to the LM75_drv.h and LM75_drv.c files in this part. (However, the main file can be used to test the functions).

The LM75 is a temperature sensor with the following characteristics:
- Resolution: 9 bits (LSB = 0.5°C, 1 sign bit)
- Operating range: -55°C to +125°C
- LSB
- Accuracy: ±2°C
- Interface: I2C 
- Feature: Overtemperature Detector (sensor OS pin)

The LM75 is a digital temperature sensor with an overtemperature detector, which allows the sensor to drive a ventilation system or an alarm system without having to use a microcontroller (except for programming the sensor). In our case, we'll use this feature to detect overtemperature in the next section.

## 3. Overtemperature Output management

## 4. System programming

## 5. Programming standard: MISRA C

For copyright reasons, I cannot provide a copy of the MISRA C standard in this section. If this exercise is carried out face-to-face and I am present, we can do this section together. If this is not the case and you do not have a copy of the MISRA C guidelines, I invite you to skip this section.

**Question X:** Run the `make verif` command, what types of errors have been made (bracket at the end of the error). 

**Question X:** Correct the errors until there are no more errors detected by cppcheck. In the case of a false positive, add the comment "// cppcheck-suppress error-name" to the line that triggers a false positive.

**Question X:** You can also check that the documentation has been correctly written by running the update-doc.sh script.
