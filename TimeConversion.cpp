/*
	As soon as user uses one of the constructor the other format 
	will also be created and saved inside class variables.
	24 hour clock format
*/

/*
	--------------------------------------------------
	|Member		|Type|	Meaning									 |Range|
	--------------------------------------------------
	|tm_sec		|int |	seconds after the minute |0-60*|
	|tm_min		|int |	minutes after the hour	 |0-59 |
	|tm_hour	|int |	hours since midnight		 |0-23 |
	|tm_mday	|int |	day of the month				 |1-31 |
	|tm_mon		|int |	months since January		 |0-11 |
	|tm_year	|int |	years since 1900				 |		 |
	|tm_wday	|int |	days since Sunday				 |0-6  |
	|tm_yday	|int |	days since January 1		 |0-365|
	|tm_isdst	|int |	Daylight Saving Time flag|	   |
	--------------------------------------------------
*/

#include <iostream>
#include <chrono>
#include <ctime>
 
class DateTimeStamp {
private:
	time_t epoch;
	struct tm time;

public:
	// Initialize using day, month, year, hour, min, sec
	// Converts to Epoch 
	DateTimeStamp(int day, int month, int yr, int hr, int min, int sec)
	{
		time.tm_mday = day;
		time.tm_mon = month;
		time.tm_year = yr - 1900;
		time.tm_hour = hr;
		time.tm_min = min;
		time.tm_sec = sec;
		
		epoch = 0;	// Convert Human Readable to Epoch, till then 0
	}

	// Initialization using struct tm
	// Converts Human Readable to Epoch
	DateTimeStamp(struct tm dateTimeStamp) : time {dateTimeStamp}
	{
		epoch = 0;	// Convert Human Readable to Epoch, till then 0
	}

	// Initialize using Unix Epoch Format 
	// param type time_t
	// Converts to Human Readable Format
	DateTimeStamp(time_t epochTime) : epoch {epochTime}
	{
		// Convert Epoch to Human Readable Form
		localtime_s(&time, &epoch);
	}

	void print(std::string format = "default")
	{
		if (format == "default")
		{
			std::cout << time.tm_mday << "/" << time.tm_mon + 1 << "/" 
								<< time.tm_year + 1900 << " " << time.tm_hour << ":" 
								<< time.tm_min << ":" << time.tm_sec << std::endl;
		}

		else if (format == "epoch")
		{
			std::cout << epoch << std::endl;
		}

		else {
			std::cout << "Unsupported Format!!!" << std::endl;
		}
	}
};

int main()
{
  // 1605611104 : Tuesday, 17 November 2020 4:35:04 PM
  DateTimeStamp test = DateTimeStamp(1605611104);
  test.print();
  test.print("epoch");

  std::cout << "Testing with currrent time" << std::endl;
  double now = std::chrono::duration_cast<std::chrono::seconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
  DateTimeStamp testCurr = DateTimeStamp(now);
  testCurr.print();
  testCurr.print("epoch");
  /*
   17/11/2020 16:35:4
   1605611104
   Testing with currrent time
   17/11/2020 18:36:5
   1605618365
  */
}
