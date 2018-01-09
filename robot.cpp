#include "WPILib.h"
#include "CANTalon.h"
#include <CameraServer.h>
#include <IterativeRobot.h>
#include <thread>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

class MecanumDefaultCode : public IterativeRobot
{
  CANTalon lf;
  CANTalon lr;
  CANTalon rf;
  CANTalon rr;
  CANTalon rope;
  
  frc::RobotDrive myRobot { 0, 8 };
  
  public:
    
      RobotDrive *m_robotDrive;
      Joystick *m_driveStick;
      Joystick *m_auxilaryStick;
      
      
      MecanumDefaultCode(void) : lf(4), lr(2), rf(6), rr(12), rope(8)
      {
        CameraServer::GetInstance()->StartAutomaticCapture();
        /* Set every Talon to reset the motor safety timeout. */
        lf.Set(0);
        lr.Set(0);
        rf.Set(0);
        rr.Set(0);
        rope.Set(0);
        m_robotDrive = new RobotDrive (lf, lr, rf, rr);
        m_robotDrive->SetExpiration(0.5);
        m_robotDrive->SetSafetyEnabled(false);
        m_driveStick = new Joystick(2);
        m_auxilaryStick = new Joystick(1);
      }
      
     void AutonomousInit()
     {
        CameraServer::GetInstance()->StartAutomaticCapture();
        lf.Set(0.6);
        lr.Set(0.5);
        rf.Set(-0.5);
        rr.Set(-0.5);
        Wait(3.0);
        lf.Set(0.0);
        lr.Set(0.0);
        rf.Set(0.0);
        rr.Set(0.0);
     }
     
     void TeleopPeriodic(void)
     {
        m_robotDrive->MecanumDrive_Cartesian(   (-m_driveStick->GetX()),
                                                (m_driveStick->GetY()),
                                                (m_driveStick->GetZ()));
       m_robotDrive->SetInvertedMotor(RobotDrive::kFrontRightMotor, true);
       m_robotDrive->SetInvertedMotor(RobotDrive::kFrontLeftMotor, true);
       m_robotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);
       m_robotDrive->SetInvertedMotor(RobotDrive::kRearLeftMotor, true);
       if(m_auxilaryStick->GetRawButton(7)) { rope.Set(10); } else{ rope.Set(0); }
     }
     
};
START_ROBOT_CLASS(MecanumDefaultCode);
       
