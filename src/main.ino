
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float32.h>
#include <std_srvs/Empty.h>

#include <aeropendulum_common_messages/GraphPlotData.h>
#include <aeropendulum_common_messages/SetPoint.h>
#include <aeropendulum_common_messages/SetPid.h>
#include <aeropendulum_common_messages/GetPid.h>
#include <aeropendulum_common_messages/GetSteadyState.h>
#include <aeropendulum_common_messages/StepResponseData.h>

#include <TimerThree.h>
#include <Servo.h>
#include <PID_v1.h>

#include <math.h>

#define pino_motor 6
#define N 10
#define MATEUS 10

//variáveis
int i = 0;
int n = 0;
double setPoint; // setpoint
int potcru;
int potmap; // valor não mapeado do potenciômetro
int mapReference;

double anguloAtual; //entrada 
double saida;
double deg;
float soma = 0;
float filtrado;

double u;

float kP = 0.39003;
float kI = 0.48455; 
float kD = 0.059492;
float pidPeriodo;

float semArredondar;

int cont = 0;

bool calibrationOk = false;

float angulo;
uint8_t calibracao;


float correnteMotor; 

bool nSampleReset;
bool stepResponseOn = false;
bool callSetPoint = false;

unsigned long tempoAtual;
unsigned long tempoAtualFiltro;
unsigned long tempoAnterior;
unsigned long tempoAnteriorFiltro;
unsigned long tempoAnteriorConta;
unsigned long intervaloDeTempo = 10;

float buffer[N];

ros::NodeHandle  nh; //inicializa o handle do ros

/* Tipos de mensagens do ROS*/

aeropendulum_common_messages::GraphPlotData graphdata;
aeropendulum_common_messages::StepResponseData stepdata;
std_msgs::UInt16 rpot;
std_msgs::Float64 mpot;
std_msgs::Float64 outputPID;


std_msgs::Float32 mcurr;

//instanciamento dos publishers
ros::Publisher graph_plot("graph_plot", &graphdata);
ros::Publisher step_response("step_response", &stepdata);
ros::Publisher rawpot("rpot", &rpot);
ros::Publisher mappot("mpot", &mpot);
ros::Publisher outpid("outpid", &outputPID);

ros::Publisher mcurrent("motor_current", &mcurr);

//instanciamento do PID
PID aeropendulumPID(&anguloAtual, &saida, &setPoint, kP, kI, kD, DIRECT);

/* Funções de callback para os serviços do ROS*/                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
void setSetPoint(const aeropendulum_common_messages::SetPoint::Request & req, aeropendulum_common_messages::SetPoint::Response & res){
  setPoint = req.angle;
  res.done = true;
  callSetPoint = true;
  stepResponseOn = false;
}

void stepResponse(const aeropendulum_common_messages::SetPoint::Request & req, aeropendulum_common_messages::SetPoint::Response & res){
  setPoint = req.angle;
  res.done = true;
  stepResponseOn = true;
  callSetPoint = false;
  n = 0;
}

void setPID(const aeropendulum_common_messages::SetPid::Request & req, aeropendulum_common_messages::SetPid::Response & res){
  kP = req.kp;
  kI = req.ki;
  kD = req.kd;
  pidPeriodo = req.pidPeriod;
  aeropendulumPID.SetTunings(kP,kI,kD);
}

void getPID(const aeropendulum_common_messages::GetPid::Request & req, aeropendulum_common_messages::GetPid::Response & res){
  res.kp = kP;
  res.ki = kI;
  res.kd = kD;
  res.pidPeriod = pidPeriodo;
}

void angCal(const std_srvs::Empty::Request & req, std_srvs::Empty::Response & res){
  mapReference = analogRead(A0);
  calibrationOk = true;
}

void estadoEstacionario(const aeropendulum_common_messages::GetSteadyState::Request & req, aeropendulum_common_messages::GetSteadyState::Response & res){
  double rad = (double)(anguloAtual*PI)/180.00;
  res.angle = sin(rad);
  res.controlSignal = setPoint;
}



/* Instanciamento dos serviços do ROS*/
ros::ServiceServer<aeropendulum_common_messages::SetPoint::Request, aeropendulum_common_messages::SetPoint::Response> setpoint("set_point",&setSetPoint);
ros::ServiceServer<aeropendulum_common_messages::SetPid::Request, aeropendulum_common_messages::SetPid::Response> setpid("set_pid_parameters",&setPID);
ros::ServiceServer<aeropendulum_common_messages::GetPid::Request, aeropendulum_common_messages::GetPid::Response> getpid("get_pid_parameters",&getPID);
ros::ServiceServer<std_srvs::Empty::Request, std_srvs::Empty::Response> angcal("angle_calibration",&angCal);
ros::ServiceServer<aeropendulum_common_messages::GetSteadyState::Request, aeropendulum_common_messages::GetSteadyState::Response> estEsta("steady_state",&estadoEstacionario);
ros::ServiceServer<aeropendulum_common_messages::SetPoint::Request, aeropendulum_common_messages::SetPoint::Response> stepresponse("unit_step_response",&stepResponse);

//instanciamento do servomotor
Servo ServoMotor;

float floatMap(int x, float in_min, float in_max, float out_min, float out_max) {//fução para interpolação de valores   
   float y = out_min - (((in_min - x)*(out_min-out_max))/(in_min - in_max));
   semArredondar = y;
   float c = floor(y);
   return y ; 
}

void setup(){
  
  setPoint = 0;
  u = 15.0;
  mapReference = analogRead(A0);
  

  aeropendulumPID.SetOutputLimits(-127, 127);


  nh.initNode();

  nh.advertise(graph_plot);
  nh.advertise(rawpot);
  nh.advertise(mappot);
  nh.advertise(mcurrent);
  nh.advertise(step_response);
  nh.advertise(outpid);

  nh.advertiseService(setpoint);
  nh.advertiseService(stepresponse);
  nh.advertiseService(setpid);
  nh.advertiseService(getpid);  
  nh.advertiseService(angcal);
  nh.advertiseService(estEsta);

  pinMode(A0, INPUT);

  ServoMotor.attach(pino_motor);

  aeropendulumPID.SetSampleTime(MATEUS);

  aeropendulumPID.SetMode(AUTOMATIC);

}

void loop(){
 

  potcru = analogRead(A0);
  potmap = floatMap(potcru, mapReference, mapReference - 440.000, 0.0000, 90.0000);

  tempoAtualFiltro = millis();
  if(tempoAtualFiltro - tempoAnteriorFiltro >= 1)
  {
    buffer[0]=potmap;

    for(int c = N - 1; c > 0; c--)
    {
      buffer[c]=buffer[c-1];
    }
    for(int i = 0; i < N; i++)
    {
      soma = soma + buffer[i];
    }
    filtrado = soma/N;
    soma = 0;
    anguloAtual = filtrado;

  }

  aeropendulumPID.Compute();

  tempoAtual = millis();

  if(tempoAtual-tempoAnterior >= intervaloDeTempo)
  {
    graphdata.angle = anguloAtual;
    graphdata.nSample = i;
    graphdata.setPointAngle = setPoint;
    graphdata.angleError = setPoint - anguloAtual;
    graphdata.controlSignal = u;
    
    stepdata.angle = anguloAtual;
    stepdata.nSample = n;
    stepdata.setPointAngle = setPoint;

    mcurr.data = correnteMotor;

    outputPID.data = saida;
    rpot.data = potcru;
    
    mpot.data = semArredondar;

    rawpot.publish(&rpot);
    mappot.publish(&mpot);
    outpid.publish(&outputPID);

    if(stepResponseOn)
    {
      step_response.publish(&stepdata);
      n++;
    }
    if(callSetPoint)
    {
      graph_plot.publish(&graphdata);
      i++;
    }
    mcurrent.publish(&mcurr);
    nh.spinOnce();

    tempoAnterior = tempoAtual;
  }

  if(cont>=10000){
        deg = anguloAtual*DEG_TO_RAD;
        u = 33.35 * sin(deg) + 56.6 + saida;
        if(u < 0.0)
        {
          u = 0.0;
        }
        if(u > 90.0)
        {
          u = 90.0;
        }
        tempoAnteriorConta = tempoAtual;
  }
  else{
    cont++;
  }
    ServoMotor.write(u);
}
