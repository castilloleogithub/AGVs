
void recepcion_comando();

void  mov_dist_rel(long);
void  mov_dist_abs(long);
void  mov_gps_rel(float,float);
void  mov_gps_abs(float,float);
void  rot_ang_rel(float);
void  rot_ang_abs(float);
void  rot_brj_rel(float);
void  rot_brj_abs(float);
void  nueva_rutina(String);
void  ejecutar_rutina(String);
long  distancia(String);
float coordinadas(String,String);
float angulo(String);



void setup() 
{
  Serial.begin(9600);

}

void loop() 
{
  

}

void recepcion_comando()
{
  String ingreso;
  String comando;
  if(Serial.available() > 0)
  {
    ingreso = Serial.readStringUntil('\n');
  }
  comando = ingreso.substring(0,1);

  if(comando == "MR")
  {
     
  }

  if(comando == "MA")
  {
     
  }

  if(comando == "RR")
  {
     
  }

  if(comando == "RA")
  {
     
  }

  if(comando == "NR")
  {
     
  }

  if(comando == "XR")
  {
    
  }
  
  if(comando == "NN")
  {
     
  }
  
}
