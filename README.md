# CowCounter_for_Arduino
This challenge starts with a field, a matrix of NxN, where M cows are scattered randomly. Each cow has its number, which is assumed to be the cow's identity. This project aims to fulfill two requested tasks: 1) the number of cows in the corners and 2) the number of cows that are neighbors.
The program receives the field size, N, and number of cows, M, and then randomly distributes cows on the NxN size field. The cows also are numbered randomly. It means that cow number 1 might be much closer to the down button than cow number M. It should be noted that M is always less than or equal to NxN.

You can enter the field size and the cow number using a string with the following format: SZxxCWxx#

In the above line, SZ stands for the field size, and CW stands for the cow number. 

Please note that the field size is limited to 10 due to the limited memory size of the microcontroller.

The program is designed and developed using the Arduino IDE for Arduino Uno; however, you may build and run it using any AVR C compiler. 
