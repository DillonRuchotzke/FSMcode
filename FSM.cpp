// .----------------------------------------------------.
// | name: 	Dillon Ruchotzke 							|
// | code:	Junior Software Engineer Application Code	|
// | date: 	April 22nd 2014 (last edit)					|
// | program:	Sensor and Motor Program				|
// .____________________________________________________.


#include <iostream>
using namespace std;

	
///////////////////////////////////////////////////////////////////////////	
// Task: Use the following as the basis for the Sensor and Motor classes //
//		 implement the door latch class yourself.					     //
///////////////////////////////////////////////////////////////////////////


/*
Code Overview:

Class 1: Door Latch
	- 	checks the state of the door sensor - returns true if latched

Class 2: Sensor
	- 	calibrates the sensors and initialization of class variables
	- 	reads data in from sensors (hard code array) to the data array and processes 
	  	the data array to obtain the average distance value.
		
Class 3: Motor
	- 	resets motor distance to 0
	-	moves motor by taking the distance value from the sensor and assigning it to the
		motor distance.
		

Main:
	-	creates instance of motor, latch, sensor classes.
	-	runs sensor calibration test to ensure system is okay to run.
		- 	if fails, system quits
	- 	otherwise, reads in sensor values and find the average values to position motor
	-	runs latch check to ensure door is closed -> latched
		-	if fails, motor will not be changed, system quits
	-	otherwise, motor is adjusted
	- 	system is finished.
	
	
	
system limitations:
	- 	obviously i am not able to work with sensors, so to simulate sensors and errors
		make changes to the following.
		
		- bool latched [Class: DoorLatch]	- TRUE (Latched) / FALSE (unlatched)
		- bool state [Class: CSensor]	- TRUE (sensors okay) / FALSE (sensor fail)
*/

class DoorLatch			//--- DOOR-LATCH CLASS -----------------------------//
{
	public:
	
	bool latched;				// sensor value to check if the door is latched => true
	
	bool CheckLatch();			// check if the door is latched

};


bool DoorLatch::CheckLatch()
{
	// checks if the door is latched, in which case we do no need to operate the motor

  	cout << "Checking Latch..." << endl;

	bool latched = true;	// assuming the door is closed --> okay to operate
	//bool latched = false;	// indicating latch error.		(uncomment and comment out above)
	
	if(latched == true)
		return true; 	// meaning the system is cleared to operate
	else		
		return false;	//meaning the door is open, do not operate
}	




class CSensor			//--- SENSOR CLASS -----------------------------//
{ 	
	public:	
	
	int data[100];				// sensor data array, can hold 100 values
  	int distance;				// single sensor data point
  	int position;				// position in data array
  	
	bool Calibrate(); 			// calibrates the sensor
  	void ReadData(int data[]); 	// Reads the data from the sensor, given data and length

};


bool CSensor::Calibrate()
{
	// calibrate/initialize the system
	
	cout << "Calibrating..." << endl;
	
	bool state;			// true if the state is properly initialized
						// false if there is an error			
				
	distance = 0;	// initialize variables
	position = 0;	// set start point of array
					// also indicates when the array is past the end of sensor data

	// some other initialization steps can be performed here
	// would implement a check for all these sensors and components -> state = true/false?
	// i am assume the sensor for the latched door is false, meaning its open
	
	state = true;		// assuming every thing is okay, state = true;
	//state = false;	// sensor error (uncomment and comment out above)
	
	return state;	// return the results of Calibration
}


void CSensor::ReadData(int data[]) 
{
	//read in and set distance read from sensor, based on average of sensor data
	
	cout << "Obtaining Sensor Data..." << endl;
	int pos = 0;		// temp position variable for DATA_ARRAY	
	
	int DATA_ARRAY [] = { 100, 101, 105, 110, 210, 100, 102, 110, 150, 100, '\0'}; // hardcoded sensor data
	
	int len = sizeof(DATA_ARRAY)/sizeof(int);	// length gets the number of data values
	
	while(pos < len)		// simulates reading data from sensor into array
	{ 
		data[pos] = DATA_ARRAY [pos];		// assign data to sensor array
		//cout << data[position] << " ";
		pos++;
	} 	
	
	
	
	while(data[position] != '\0') // when we find the end of the sensor data array --> DONE
	{
		distance += data[position];		// sum value from sensor array
		position ++; 					//next position in array for next sensor value	
	}
	
	distance = distance/(position);			// takes the average distance				
											// +1 accounts for the 0 start of the array

	cout << "Data Aquired -- Avg Sensor Distance: "<< distance << endl << endl;
}
  	  	
  	
  	
class CMotor		//--- MOTOR CLASS -----------------------------//
{  	
	public:	
	
	int MotorPosition;				// hold to position for the motor.
	
	void ResetMotor(); 				// moves motor to the starting position
  	void MoveMotor(int distance); 	// Moves motor to the measurement position
};
  	
void CMotor::ResetMotor()
{
	// Reset the motor position;
	
	MotorPosition = 0;	
}  	
 
void CMotor::MoveMotor(int distance) 
{
	// moves the motor
	
	printf("Adjusting Motor Distance: %i \n", distance);	// print to screen

} 	
  	
  	
  	
  	
int main()	// MAIN //////////////////////////////////////////////////////
{  	

	cout << "\nFinite State Machine Program\n";
	cout << "=============================\n" << endl;
  	bool run_system;		// checks if the system is okay to run
  	
  	
  	CMotor Motor1;			// instance of a motor
  	CSensor Sensor1;		// instance of a sensor
  	DoorLatch Latch1;		// instance of a doorlatch 
  	
  	
  	run_system = Sensor1.Calibrate();
  	if(run_system == true)	//system properly calibrated
  	{
  		cout << "Calibration Finished" << endl << endl;
  	}
  	else		//run_system == false
  	{
  		cout << "Calibration Error! Please Check Sensors." << endl << endl;
  		return 0;		// done
  	}
  	
  
    Sensor1.ReadData(Sensor1.data);		// read in sensor data
	Motor1.ResetMotor();				// reset the motor prior to new data  	
  	
  	run_system = Latch1.CheckLatch();	// check if the system is latched
  	if(run_system == true)
  	{
  		cout << "Door Latch Secured" << endl << endl;
  		
		Motor1.MoveMotor(Sensor1.distance);	// set motor position using sensor data
	}
	else
	{
		cout << "Door Not Latched. Execution Aborted. "<< endl << endl;
		return 0;		// done
	}
  	

	cout << "\nProgram Completed." << endl << endl;
	
	return 0;		// finished
	  	
}
