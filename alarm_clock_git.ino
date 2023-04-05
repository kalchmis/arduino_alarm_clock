int time1, time2, press_time, unpress_time, last_press_time;


enum CLOCK_MODE{
	NORMAL_STATE,
	TIME_SETTING,
	ALARM_TIME_SETTING,
	MUSIC_SELECT
};
enum CLOCK_MODE mode_flag =NORMAL_STATE;

void button_isr()
{
  Serial.print(digitalRead(2));
  Serial.print("==>");
  Serial.print(millis());
  Serial.print(":");
  if(digitalRead(2)==0) 
  {
    time1 = millis();
    unpress_time = time1 - time2;
    Serial.print("UN: ");
    Serial.println(unpress_time); 
  }
  else
  {
    time2 = millis();
    last_press_time = press_time;
    press_time = time2 -time1; 
    Serial.print("PR: ");    
    Serial.println(press_time);
    if(press_time>1000)
    {
      Serial.println("Long Key");
      mode_flag = ALARM_TIME_SETTING;
    }
    if(last_press_time <500 && press_time < 500 && unpress_time <500)
    {
      Serial.println("Double click");
      mode_flag = MUSIC_SELECT;
    }
  }
  
}

void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  attachInterrupt(0,button_isr,CHANGE);
}

void loop() {
  if(mode_flag ==ALARM_TIME_SETTING)
  {

    mode_flag = NORMAL_STATE;
  }
  else if(mode_flag == MUSIC_SELECT)
  {

    mode_flag = NORMAL_STATE;
  }
}
