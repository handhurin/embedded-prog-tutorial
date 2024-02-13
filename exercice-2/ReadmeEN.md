# Exercise 2: Embedded programming

In this exercise we are going to introduce the concepts of bare metal embedded programming. The idea is to focus on bare metal programming around a use case based on the LM75. In particular, we will look at
- The concept of hardware driver, how to write a driver. What are the right formalisms to adopt
- The concept of interrupts, in particular using the LM75's overtemperature output.
- What are the standards to be respected in embedded programming?

Low-level driver programming is not covered by this exercise. It is a long and tedious exercise, especially for fairly large microcontrollers such as the STM32H7. I recommend practising on 8-bit AVR processors to code low-level drivers. 

## 1. LM75 Equipment Driver

In this part, the aim is to create an equipment driver for the LM75.

## 2. Overtemperature Output management

## 3. System programming

## 4. Programming standard: MISRA C

For copyright reasons, I cannot provide a copy of the MISRA C standard in this section. If this exercise is carried out face-to-face and I am present, we can do this section together. If this is not the case and you do not have a copy of the MISRA C guidelines, I invite you to skip this section.

**Question 1:** Run the `make verif` command, what types of errors have been made (bracket at the end of the error). 

**Question 2:** Correct the errors until there are no more errors detected by cppcheck. In the case of a false positive, add the comment "// cppcheck-suppress error-name" to the line that triggers a false positive.

**Question 3:** You can also check that the documentation has been correctly written by running the update-doc.sh script.