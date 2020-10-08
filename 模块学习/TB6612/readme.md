## TB6612模块描述

### 规格
- 20.5*20.4MM

### TB6612的的用法：

- TB6612是双驱动，也就是可以驱动两个电机

- 下面分别是控制两个电机的IO口

- STBY口接单片机的IO口清零电机全部停止，置1通过AIN1 AIN2，BIN1，BIN2 来控制正反转

-  VM 接12V以内电源 （2.74-10.8V）

-  VCC 接5V电源

- GND 接电源负极

#### 驱动1路
-  PWMA 接单片机的PWM口
- 真值表：
-  AIN1 0 0 1
-   AIN2 0 1 0
- 停止 正传 反转

-  A01，AO2 接电机1的两个脚
#### 驱动2路
-  PWMB 接单片机的PWM口
- 真值表：
- BIN1 0 0 1
- BIN2 0 1 0
-  停止 正传 反转
- B01，BO2 接电机2的两个脚

### 英文描述
Description:

The TB6612FNG motor driver can control up to two DC motors at a constant current of 1.2A (3.2A peak). Two input signals (IN1 and IN2) can be used to control the motor in one of four function modes - CW, CCW, short-brake, and stop. The two motor outputs (A and B) can be separately controlled, the speed of each motor is controlled via a PWM input signal with a frequency up to 100kHz. The STBY pin should be pulled high to take the motor out of standby mode.



CJMCU.



Logic supply voltage (VCC) can be in the range of 2.7-5.5VDC, while the motor supply (VM) is limited to a maximum voltage of 15VDC. The output current is rated up to 1.2A per channel (or up to 3.2A for a short, single pulse).



Board comes with all components installed as shown. Decoupling capacitors are included on both supply lines. All pins of the TB6612FNG are broken out to two 0.1" pitch headers; the pins are arranged such that input pins are on one side and output pins are on the other.



Features:



Power supply voltage: VM=15V max, VCC=2.7-5.5V



Output current: Iout=1.2A(average) / 3.2A (peak)



Standby control to save power



CW/CCW/short brake/stop motor control modes



Built-in thermal shutdown circuit and low voltage detecting circuit



All pins of the TB6612FNG broken out to 0.1" spaced pins



Filtering capacitors on both supply lines

