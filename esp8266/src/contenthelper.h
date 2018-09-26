#ifndef CONTENTHELPER_H
#define CONTENTHELPER_H

#include <Arduino.h>

class ContentHelper{
	public:
		static void getCardView(String filename, char *buffer);
		static void getLatestCard(String filename, char *buffer);
		static void getSysinfo(char *buffer);
};

#endif
