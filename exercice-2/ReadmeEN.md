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
- Interface: I2C (default address 0x90)
- Feature: Overtemperature Detector (sensor OS pin)

The LM75 is a digital temperature sensor with an overtemperature detector, which allows the sensor to drive a ventilation system or an alarm system without having to use a microcontroller (except for programming the sensor). In our case, we'll use this feature to detect overtemperature in the next section.

In I2C, the LM75 can be seen as a memory containing 4 registers:
| Register Name | Address | Default State | Right |
|---------------|---------|---------------|-------|
| Temperature   | 0x00    | 0x0000        | RO    |
| Configuration | 0x01    | 0x00          | RW    |
| T_HYST        | 0x02    | 0x4B00        | RW    |
| T_OS          | 0x03    | 0x5000        | RW    |

The Configuration, T_HYST and T_OS registers are configurable (read/write access), while Temperature is read-only.

The Temperature, T_HYST and T_OS registers correspond to temperatures. Temperature corresponds to the current temperature, T_HYST corresponds to the low threshold temperature of the overtemperature detector and T_OS corresponds to the high threshold temperature of the detector i.e. if the temperature exceeds T_OS then the OS pin is set to 0 and if the temperature falls below T_HYST then the OS pin is set to 1 (hysteresis system see Figure 1. in the datasheet).
The stored temperatures are defined as follows:
| D15  | D14  | 13   | D12  | D11 | D10 | D9  | D8  | D7    | D6 | D5 | D4 | D3 | D2 | D1 | D0 |
|------|------|------|------|-----|-----|-----|-----|-------|----|----|----|----|----|----|----|
| Sign | 64°C | 32°C | 16°C | 8°C | 4°C | 2°C | 1°C | 0.5°C | X  | X  | X  | X  | X  | X  | X  |

The Configuration register contains the following bits :
| D7 | D6 | D5 | D4          | D3          | D2          | D1      | D0       |
|----|----|----|-------------|-------------|-------------|---------|----------|
| 0  | 0  | 0  | Fault Queue | Fault Queue | OS Polarity | OS Mode | ShutDown |

The Fault Queue registers determine the number of faults required to trigger an OS condition (0b00 = 1, 0b01 = 2, 0b10 = 4, 0b11 = 6). OS Polarity indicates whether the OS pin is active low (OS Polarity = 0b0) or active high (OS Polarity = 0b1). OS Acquisition Mode indicates whether it is in :
- Comparator: If the temperature rises above T_OS then the OS pin is active (0 by default), if the temperature falls below T_HYST then the OS pin is passive (1 by default).
- Interrupt: The state of the OS pin is determined only when the sensor reads the temperature data.
The comparator mode will be used.

**Question 1:** In the LM75_driver.c file, in the Macro definition section, define the following constants: TEMP_REG_ADDR, CONF_REG_ADDR, T_HYST_REG_ADDR, T_OS_REG_ADDR with the addresses of the 4 registers as defined above. Then, still in the LM75_driver.c file, define FAULT_QUEUE_OFFSET, FAULT_QUEUE_MASK, OS_POLARITY_OFFSET, OS_POLARITY_MASK, OS_MODE_OFFSET, OS_MODE_MASK, SHUTDOWN_OFFSET, SHUTDOWN_MASK.

**Note:** We have chosen to place the #define in the C file instead of the H file, so that these #define are only accessible to the elements defined in the LM75_drv.c file and not all the files that would include LM75_drv.h. 

Generally speaking, you need to be careful about the definition scope of macros, variables and functions. They should always be defined in the smallest possible scope. This makes it possible to "privatise" the macros, variables and functions and reduce the interfaces between the various codes to a few macros, variables and functions.

Note that to read from or write to LM75, you always perform the same transactions:
- Reading: We start with an I2C write in which we indicate the address of the **register** we wish to read (it is understood that the slave address is sent at the start of the frame). An I2C read is then performed to read the contents of the register (1 or 2 bytes).
- Write: An I2C write is performed in which the address of the **register** that is to be modified is first indicated (it being understood that the slave address is sent at the start of the frame), then the contents of the register (1 or 2 bytes) are transmitted on the same transaction. 
This is why we propose to write generic functions to meet this need.

**Question 2:** Write the function LM75GetReg which reads the contents of a register. The function must have the following declaration:
```
static equipmentsStatus_t LM75GetReg(int8_t reg_addr,int8_t *content, uint8_t size);
```
This function must write and then read. The size of the read must be dependent on the address (basically, if the address = CONF_REG_ADDR, only one byte is read). We can check the size argument and return EQUIPMENTS_INVALID_PARAM if the size is not consistent with the register we wish to read.
In addition, the function must be declared in such a way as to remain within the scope of the LM75 driver (delimited by the LM75_drv.c file), which is why the *static* attribute is added in front of the function to indicate that the function has a scope limited to its source file. The function must be declared in the .c file (in the "Functions Declarations" category), otherwise the static attribute is meaningless.

**Question 3:** In the same way as for LM75GetReg, write the function LM75SetReg which reads the contents of a register. The function must have the following declaration:
```
static equipmentsStatus_t LM75SetReg(int8_t reg_addr,int8_t *content, uint8_t size);
```

**Question 4:** Create a function LM75ReadTemperature which reads the temperature of the LM75. The function must have the following declaration:
```
equipmentsStatus_t LM75ReadTemperature(int8_t *temperature);
```
The function must return an error code of type equipmentsStatus_t (defined in equipments_type.h) depending on whether or not an error has occurred. The temperature must be passed as a pointer. Don't forget to **declare** the function in the header (.h) and **define** the function in the source file (.c) because this time the function is intended to be used outside the driver.

**Note:** It is better for any function to use the return to report its status and not to return the input data. This makes it possible to evaluate whether the function was executed correctly, and passing outputs as pointer variables means that you are not limited to a single variable.

**Question 5:** Create a function LM75SetOSTemperatures which regulates temperatures T_HYST and T_OS. The function must have the following declaration:
```
equipmentsStatus_t LM75SetOSTemperatures(int8_t t_hyst, int8_t t_os);
```
This function needs to set the temperature T_HYST **and** T_OS (the order doesn't matter) so 2 transactions are required.

**Question 6:** Similarly, create a function LM75GetOSTemperatures which obtains the values of T_HYST and T_OS. The function must have the following declaration:
```
equipmentsStatus_t LM75GetOSTemperatures(int8_t *t_hyst, int8_t *t_os);
```

**Question 7:** Create a structure type lm75Conf_t which contains the four elements of the sensor configuration: fault_queue, os_polarity, os_mode, shutdown. We will use uint8_t to store each of the fields.

**Question 8:** Create a function LM75GetConf which regulates the configuration of the LM75.
```
equipmentsStatus_t LM75GetConf(lm75Conf_t *lm75_conf);
```

**Question 9:** Create a LM75SetConf function that sets the LM75 configuration.
```
equipmentsStatus_t LM75SetConf(lm75Conf_t lm75_conf);
```

So far we've covered most of the useful functions for using the LM75, but our functions only work if there's only one sensor and/or one I2C bus. We therefore propose to create an instance (a bit like an object in object-oriented programming) which is a structure that will be passed to each of the driver functions and which allows the bus and sensor parameters to be passed.

The following structure is proposed:
```
/** 
 * @struct lm75Inst_t
 * @brief Struct type definition of a LM75 instance
 */
typedef struct
{
    iicInst_t *iic_instance; /**< @brief Pointer to the I2C instance with whom the LM75 is connected to */
    iicSlaveAddr_t sensor_addr; /**< @brief LM75 I2C address */
} lm75Inst_t;
```

**Question 10:** Modify all the LM75 driver functions so as to pass the lm75 instance as a pointer. The following declarations are proposed:
```
// In the .c file
static equipmentsStatus_t LM75GetReg(int8_t reg_addr,int8_t *content, uint8_t size);
static equipmentsStatus_t LM75SetReg(int8_t reg_addr,int8_t *content, uint8_t size);
// In the .h file
equipmentsStatus_t LM75ReadTemperature(int8_t *temperature);
equipmentsStatus_t LM75SetOSTemperatures(int8_t t_hyst, int8_t t_os);
equipmentsStatus_t LM75GetOSTemperatures(int8_t *t_hyst, int8_t *t_os);
equipmentsStatus_t LM75GetConf(lm75Conf_t *lm75_conf);
equipmentsStatus_t LM75SetConf(lm75Conf_t lm75_conf);
```

## 3. Overtemperature Output management

## 4. System programming

## 5. Programming standard: MISRA C

For copyright reasons, I cannot provide a copy of the MISRA C standard in this section. If this exercise is carried out face-to-face and I am present, we can do this section together. If this is not the case and you do not have a copy of the MISRA C guidelines, I invite you to skip this section.

**Question X:** Run the `make verif` command, what types of errors have been made (bracket at the end of the error). 

**Question X:** Correct the errors until there are no more errors detected by cppcheck. In the case of a false positive, add the comment "// cppcheck-suppress error-name" to the line that triggers a false positive.

**Question X:** You can also check that the documentation has been correctly written by running the update-doc.sh script.
