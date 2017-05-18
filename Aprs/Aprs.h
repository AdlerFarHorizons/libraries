/*DESCRIPTION
 * This is a library implementation of retrieving common info from a given APRS sentence
 * To use this library, do: aprs <instance name here> = aprs("validCallsignsHere");
 * and then call giveAprsString(<your aprs input string here>);
 * 
 * To get info out of the stored string, read this file (aprs.h) and check out the available functions.
 * example: <yourVariable> = <obj instance>.getCallsign();
 * --KD9BVO
  */

#ifndef Aprs_h
#define Aprs_h
#if ARDUINO < 100
    #include <WProgram.h>
#else
    #include <Arduino.h>
#endif

class Aprs{
	public:
		Aprs(String validCallsigns);
		String getCallsign();
    boolean putAprsString(String aprsString);
    float getLatitude();
    float getLongitude();
    long getAltitude();
    int getGroundspeed();
    int getCourse();
	private:
		String _calls; //TODO: valid callsigns check
    String _aprsString;
    String _callsign;
    float _latitude;
    float _longitude;
    int _groundspeed;
    int _course;

    String _altString;
    long _alt;
		
};
#endif
