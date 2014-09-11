STM32L100-DISCOVERY
===================

For those who also have problems with default configuration with this discovery board. After PLL configuration system clock is 32MHz. Remove SB16, SB17, SB18, R22 and R23. 

Call this function with: clockCorrection(); in main(); at the begining. 
