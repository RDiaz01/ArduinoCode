
//Controller Parameters
#define PID_KP 2.0f
#define PID_KI 0.5f
#define PID_KD 0.25f

#define PID_TAU 0.02f

#define PID_LIM_MIN -10.0f
#define PID_LIM_MAX  10.0f

#define PID_LIM_MIN_INT -5.0f
#define PID_LIM_MAX_INT  5.0f

#define SAMPLE_TIME_S 0.01f

//Maxium run-time of Simulation
#define SIMULATION_TIME_MAX 4.0f

float PID_setPoint;
float PID_measurement;



typedef struct{

  //controller Gains
  float Kp;
  float Ki;
  float Kd;


  //Derivative low-pass filter time constant
  float tau;

  //output limits
  float limMin;
  float limMax;

  //Integrator limits
  float limMinInt;
  float limMaxInt;

  //sample time in seconds
  float T;

  //Controller "Memory"
  float integrator;
  float prevError;   //reauired for integretator
  float diffentiator;
  float prevMeasurement;  //required for differentiator

  //controller output
  float out;

}PIDController;

PIDController pidController = { PID_KP, PID_KI, PID_KD,
                                PID_TAU,
                                PID_LIM_MIN, PID_LIM_MAX,
                                PID_LIM_MIN_INT, PID_LIM_MAX_INT,
                                SAMPLE_TIME_S };

void setup() {
  pidController.integrator      = 0.0f;
  pidController.prevError       = 0.0f;
  
  pidController.diffentiator    = 0.0f;
  pidController.prevMeasurement = 0.0f;

  pidController.out             = 0.0f;

  PID_setPoint = 1.0f;
}

// int main()
// {
//     /* Initialise PID controller */
//     PIDController pid = { PID_KP, PID_KI, PID_KD,
//                           PID_TAU,
//                           PID_LIM_MIN, PID_LIM_MAX,
// 			  PID_LIM_MIN_INT, PID_LIM_MAX_INT,
//                           SAMPLE_TIME_S };

//     PIDController_Init(&pid);

//     /* Simulate response using test system */
//     float setpoint = 1.0f;

//     printf("Time (s)\tSystem Output\tControllerOutput\r\n");
//     for (float t = 0.0f; t <= SIMULATION_TIME_MAX; t += SAMPLE_TIME_S) {

//         /* Get measurement from system */
//         float measurement = TestSystem_Update(pid.out);

//         /* Compute new control signal */
//         PIDController_Update(&pid, setpoint, measurement);

//         printf("%f\t%f\t%f\r\n", t, measurement, pid.out);

//     }

//     return 0;
// }

// float TestSystem_Update(float inp) {

//     static float output = 0.0f;
//     static const float alpha = 0.02f;

//     output = (SAMPLE_TIME_S * inp + output) / (1.0f + alpha * SAMPLE_TIME_S);

//     return output;
// }


void loop() {
/*


*/


  

}

float PID_ControllerUpdate(float setPoint, float measurement){

  //Error Signal
  float error = setPoint - measurement;

  //proportional
  float proportional = pidController.Kp * error;

  //Integral
  pidController.integrator = pidController.integrator + 0.5f * pidController.Ki * pidController.T * (error + pidController.prevError);

  //Anti-wind-up via integrator clamping
  if(pidController.integrator > pidController.limMaxInt)
  {

    pidController.integrator = pidController.limMaxInt;

  }else if (pidController.integrator < pidController.limMinInt){

      pidController.integrator = pidController.limMinInt;
  }

  //derivative (band-limited differentiator)
  pidController.diffentiator = -(2.0f  * pidController.Kd * (measurement - pidController.prevMeasurement)
                                + (2.0f * pidController.tau - pidController.T) * pidController.diffentiator)
                                / (2.0f * pidController.tau + pidController.T);

  //Compute output and apply limits
  pidController.out = proportional + pidController.integrator + pidController.diffentiator;

  if ( pidController.out > pidController.limMax){

    pidController.out = pidController.limMax;

  } else if (pidController.out < pidController.limMin){

    pidController.out = pidController.limMin;

  }

  //Store error and measurement for later use
  pidController.prevError       = error;
  pidController.prevMeasurement = measurement;

  return pidController.out;

}
