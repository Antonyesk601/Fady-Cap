import serial
import time
from serial.serialutil import Timeout
import sys
import glob
class Arduino:
     
    def __init__(self,_port):
        self.arduino = serial.Serial(_port)
        self.ForcedLEDValues= ["0\n" for x in range(4)]
        self.ReportedLEDValues= ["0\n" for x in range(4)]
        self.DesiredLEDValues = ["0\n", "0\n", "0\n", "0\n"]
        self.Voltage = 0.0
        self.Current = 0.0    
        self.Wattage = 0.0

    def ReadData(self):     
        for i in range(4):
            self.ReportedLEDValues[i]=self.arduino.readline()
        self.Voltage=self.arduino.readline()
        self.Current= self.arduino.readline()
   
    def OverwriteDesiredLEDs(self):
        for value in self.DesiredLEDValues:
            self.arduino.write(value.encode())
            #self.arduino.flushInput()
            time.sleep(0.05)
    
    def ForceLEDs(self):
        for value in self.ForcedLEDValues:
            self.arduino.write(value.encode())
            #self.arduino.flushInput()
            time.sleep(0.05)
    def Update(self):
        self.OverwriteDesiredLEDs()
        self.ForceLEDs()
        self.ReadData()
        print(self.ReportedLEDValues,self.ForcedLEDValues,self.DesiredLEDValues)

    def UpdateWattage(self):
        self.Wattage=self.Current* self.Voltage
        return self.Wattage
    # def getSerialPorts():

def main():
    ad= Arduino("COM6")
    ls= ["1\n","0\n","0\n","0\n"]
  #  lm =ls.copy()
    #lm[0]="1\n"
    i =0
    #ad.ForcedLEDValues=lm
    write=True
    while True:
        # if write:
        ad.DesiredLEDValues=ls
        ad.OverwriteDesiredLEDs()
        ad.ForceLEDs()
        ad.arduino.flushInput()
        ad.ReadData()
        print(ad.ReportedLEDValues)
        print(ad.ForcedLEDValues)
        print(ad.Voltage)
        ls[i]="0\n"
        i+=1
        i%=4
        ls[i]="1\n"
        #print(ls)
        time.sleep(0.05)
        # write = input()
        # if write=='y':
        #     write=True
        # else:
        #     write=False

if __name__=="__main__":
    main()
