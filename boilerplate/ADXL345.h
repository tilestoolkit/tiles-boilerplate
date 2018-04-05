#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

#define ACC_INT_TAP           0x40
#define ACC_INT_DOUBLE_TAP    0x20
#define ACC_INT_ACT           0x10
#define ACC_INT_INACT         0x08
#define ACC_FIR_SIZE          (uint8_t)2
#define ACC_SHAKE_THRESH      200
#define ACC_TILT_THRESH       180 /// 90 -> ~25º, 180 -> ~45º

class ADXL345
{

    public:
      ADXL345();
      
      int x;  /// X acceleration instantaneous value
      int y;  /// Y acceleration instantaneous value
      int z;  /// Z acceleration instantaneous value

      bool isShaked ();       // True if the sensor has been tapped once 
      bool isTapped ();       // True if the sensor has been tapped once
      bool isDoubleTapped (); // Returns true if the sensor has been double tapped
      int isTilted ();        // Return the tilt axis according to enum Axis, else returns false
      void RefreshValues ();  // Reads the accelerations components

      enum Axis{X_AXIS = 1, Y_AXIS = 2};
	  
	    bool SensorAvailable;
      
    private:
      Adafruit_ADXL345_Unified accel;  /// Object representing the used sensor

      int x_FIR[ACC_FIR_SIZE];    // Samples being filtered
      int y_FIR[ACC_FIR_SIZE];    //
      int z_FIR[ACC_FIR_SIZE];    //
      uint8_t FIR_Sample;         // Current sample
      
      int32_t x_Filtered;   // FIR Output for x
      int32_t y_Filtered;   // FIR Output for y
      int32_t z_Filtered;   // FIR Output for z
      
      int d_x;          // d_x = x[n] - x[n-1]
      int d_y;          // d_y = x[n] - y[n-1]
      int d_z;          // d_z = x[n] - z[n-1]

      bool Shaked;        // True if sensor is shaked, Reset on read with isShaked()
      bool Tapped;        // True if tapped once, Reset on read with isTapped()
      bool DoubleTapped;  // True if tapped twice, Reset on read with isDoubleTapped()
      bool Tilted;        // True if the ADXL345 is tilted
      int TiltAxis;       // Axis on wich ADXL345 is tilted

      const float alpha = 0.5;
      double fXg = 0;
      double fYg = 0;
      double fZg = 0;

      double pitch, roll, Xg, Yg, Zg;
      int tilt_angle;

};
