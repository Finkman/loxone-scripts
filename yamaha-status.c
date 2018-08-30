#define RESPONSE_SIZE 40000
#define READ_BUFFER_SIZE 1024
#define OUT_STATUS 0

#define OUT_POWER_ON 1
#define POWER_ON_TEXT "on"

#define OUT_IS_2CH 2
#define IS_2CH_TEXT "2ch_stereo"

#define OUT_INPUT_SELECTED 3
#define HDMI2_SELECTED_TEXT "hdmi2"

#define OUT_DEBUG 12
#define PERIOD_MS 1000

#define INPUT_IP_ADDRESS 0

#define TAG_POWER "\power\":\""
#define TAG_SOUND_PROGRAM "\"sound_program\":\""
#define TAG_INPUT "\"input\":\""

#define GET_STATUS "/YamahaExtendedControl/v1/main/getStatus"

int mapResponseToOuput(char* json, char* tag, char* expect, int output){
  // search for "tag" on json response
  char *search = strstrskip(json, tag);
  if(search == 0){
    setoutput(output, 0);
    return -1;
  }

  // check power value is "expect"
  if(strncmp(search, expect, strlen(expect)) == 0){
    setoutput(output, 1);
  }else{
    setoutput(output, 0);
  }

  return 0;
}


while(true)
{
  setoutput(OUT_STATUS, 1);
  sleep(PERIOD_MS);

  char* ipAddress = getinputtext(INPUT_IP_ADDRESS);

  char* response = httpget(ipAddress, GET_STATUS);

  if(response == 0){
    setoutput(OUT_STATUS, 100);
    setoutput(OUT_POWER_ON, 0);
    setoutput(OUT_INPUT_SELECTED, 0);
    setoutput(OUT_IS_2CH, 0);
    sleeps(2);
	continue;
  }

  int ret;

  ret = mapResponseToOuput(response, TAG_POWER, POWER_ON_TEXT, OUT_POWER_ON);
  if(ret != 0){
    setoutput(OUT_STATUS, 101);
    continue;
  }

  ret = mapResponseToOuput(response, TAG_SOUND_PROGRAM, IS_2CH_TEXT, OUT_IS_2CH);
  if(ret != 0){
    setoutput(OUT_STATUS, 102);
    continue;
  }

  ret = mapResponseToOuput(response, TAG_INPUT, HDMI2_SELECTED_TEXT, OUT_INPUT_SELECTED);
  if(ret != 0){
    setoutput(OUT_STATUS, 103);
    continue;
  }

  free(response);
  setoutput(OUT_STATUS, 10);
}