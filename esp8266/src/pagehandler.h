#ifndef PAGEHANDLER_H
#define PAGEHANDLER_H

#include "httpserver.h"

class PageHandler{
	public:
		PageHandler();
		static void handlePageRequest(HTTPServer *server);
};

#endif
