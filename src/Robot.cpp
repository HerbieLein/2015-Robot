#include "WPILib.h"
#include "NetworkTables/NetworkTable.h"

/**
 * This is a demo program showing the use of the RobotDrive class.
 * The SampleRobot class is the base of a robot application that will automatically call your
 * Autonomous and OperatorControl methods at the right time as controlled by the switches on
 * the driver station or the field controls.
 *
 * WARNING: While it may look like a good choice to use for your code if you're inexperienced,
 * don't. Unless you know what you are doing, complex code will be much more difficult under
 * this system. Use IterativeRobot or Command-Based instead if you're new.
 */


class Robot: public SampleRobot
{
	RobotDrive *myRobot; // robot drive system
	Joystick* stick; // only joystick

	Talon  *FrontLeft;
	Talon  *RearLeft;
	Talon  *RearRight;
	Talon  *FrontRight;

	NetworkTable *table;

	//Gyro gyro;
	//Accelerometer* accel;

	//DriverStationLCD DS;
	//double value = stick.GetRawAxis(0);


public:
	Robot() {
		myRobot = new RobotDrive(1,2,3,4);
		stick = new Joystick(0);
		FrontLeft = new Talon(4);
		RearLeft = new Talon(1);
		RearRight = new Talon(3);
		FrontRight = new Talon(2);

		table = new NetworkTable;

	}

	/**
	 * Runs the motors with arcade steering.
	 */
	void OperatorControl()
	{

		myRobot->SetInvertedMotor(RobotDrive::MotorType::kRearRightMotor, true);
		myRobot->SetInvertedMotor(RobotDrive::MotorType::kFrontLeftMotor, true);

		//stick->SetAxisChannel(Joystick::kYAxis,1);
		//stick->SetAxisChannel(Joystick::kTwistAxis,2);
		//stick->SetAxisChannel(Joystick::kXAxis,0);

		while (IsOperatorControl() && IsEnabled())
		{
			myRobot->HolonomicDrive(stick->GetMagnitude(),stick->GetDirectionDegrees(),stick->GetTwist()); // drive with arcade style (use right stick)

			table->PutNumber("Joystick x",stick->GetX());

			//myRobot->MecanumDrive_Polar(stick->GetX(),stick->GetY(),stick->GetTwist());
			/*
			if(stick.GetX() > -.25){
				FrontLeft->Set(0.5);
				FrontRight->Set(0.5);
				RearRight->Set(0.5);
				RearLeft->Set(0.5);
			}
			else if(stick.GetX() < .25){
				FrontLeft->Set(-0.5);
				FrontRight->Set(-0.5);
				RearRight->Set(-0.5);
				RearLeft->Set(-0.5);
			}*/

			Wait(0.005);				// wait for a motor update time
		}
	}

};

START_ROBOT_CLASS(Robot);
