// test.h : Include file for standard system include files,
// or project specific include files.

#pragma once

//#include <iostream>
#include <stdio.h>

// TODO: Reference additional headers your program requires here.

struct port_data {
	char hostname[200];
	char f_port[6];
	char l_port[6];
	int fport;
	int lport;
	int c_port;
};

void port_scanner(struct port_data pdata);

void* scan_ports(void* pdata);