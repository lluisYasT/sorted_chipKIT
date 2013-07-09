#include <chipKITEthernet.h>
#include "funciones.h"

// Enter a MAC address and IP address for your controller below. 
// A zero MAC address means that the chipKIT MAC is to be used
byte mac[] = {	
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//			 !!MODIFY THIS!!
// The IP address will be dependent on your local network:
byte ip[] = { 
	10,0,0,8 };

byte gateway[] = { 10,0,0,1 };
byte subnet[] = { 255, 255, 255, 0 };

// telnet defaults to port 23
Server server(23);
boolean gotAMessage = false; // whether or not you got a message from the client yet

typedef enum comandos {
	NOP,
	HELP,
	BUBBLE0,
	BUBBLE1,
	BUBBLE2,
	BUBBLE3,
	QUICK0,
	QUICK1,
	QUICK2,
	QUICK3,
	SEL0,
	SEL1,
	SEL2,
	SEL3,
} comandos;

void print_array(int *array, int len);
int copia_a_resultado(int size);
comandos deco_comando(void);
void ejecuta_comando(Client *client, comandos, int);

void setup() 
{
	// initialize the ethernet device
	//	Ethernet.begin(mac, ip, gateway, subnet);
	Ethernet.begin(mac,ip);
	// start listening for clients
	server.begin();
	// open the serial port
	Serial.begin(9600);
}

uint8_t message[1000];
char comando[16];
int number_array[512];
int resultado[512];


void loop() 
{
	// wait for a new client:
	Client client = server.available();
	uint message_size = 0;
	int cantidad_num = 0;
	int n = 0;
	int size = 0;
	int data_ini = 0;
	comandos num_comando = NOP;

	if (client) {
		message = {0};
		comando = {0};
		number_array = {NULL};

		message_size = client.available();
		Serial.print("Message size: ");
		Serial.println(message_size);
		if(message_size > 16)
		{
			message_size = client.read(message, 1000);
			for (int i = 0; i < message_size; ++i)
			{
				//message[i] = client.read();
				if(message[i] == ' ' || message[i] == '\n' || message[i] == '\r')
				{
					if(cantidad_num == 0)
					{
						if(i>16){
							num_comando = NOP;
							cantidad_num = 0;
							break;
						}
						memcpy(comando, message, i);
						if((num_comando = deco_comando()) != NOP)
						{
							data_ini = i + 1;
						}
					}
					cantidad_num++;
				}
			}

			Serial.println(comando);
			if(cantidad_num > 0) //Tenemos datos
			{ 
				char numero[16] = {0};
				int j = 0;
				n = 0;
				for(int i = data_ini; i < message_size; ++i)
				{
					if(message[i] != ' ' && message[i] != '\n')
					{
						numero[j] = message[i];
						j++;
					} else {
						//number_array[n] = atoi(numero);
						if(sscanf(numero, "%d", &number_array[n]) < 1)
						{
							Serial.println("Error al convertir");
						Serial.print("Num: ");
							Serial.println(numero);
							size = 0;
							number_array = {NULL};
							break;
						} else
						{
						 n++;
						 j = 0;
						 numero = {0};
						}
					}
				}
				size = n;
				Serial.print("Tamaño del array: ");
				Serial.println(size);
			}
		}
		
		client.flush();

		ejecuta_comando(&client, num_comando, size);
		if(size)
		{
			print_array(resultado, size);
		}
	}
}

void print_array(int *array, int len)
{
	for(int i = 0;i < len; ++i)
	{
		server.print(array[i]);
		Serial.print(array[i]);
		server.print(' ');
		Serial.print(' ');
	}
	server.print('\n');
	Serial.println("");
}

int copia_a_resultado(int size)
{
	
	for (int i = 0; i < size; ++i)
	{
		resultado[i] = number_array[i];
	}
	return 0;
}

comandos deco_comando(void)
{
	if (!strcmp(comando, "bubble0"))
	{
		return BUBBLE0;
	} else if (!strcmp(comando, "bubble1"))
	{
		return BUBBLE1;
	} else if (!strcmp(comando, "bubble2"))
	{
		return BUBBLE2;
	} else if (!strcmp(comando, "bubble3"))
	{
		return BUBBLE3;
	} else if (!strcmp(comando, "quick0"))
	{
		return QUICK0;
	} else if (!strcmp(comando, "quick1"))
	{
		return QUICK1;
	} else if (!strcmp(comando, "quick2"))
	{
		return QUICK2;
	} else if (!strcmp(comando, "quick3"))
	{
		return QUICK3;
	} else if (!strcmp(comando, "sel0"))
	{
		return SEL0;
	} else if (!strcmp(comando, "sel1"))
	{
		return SEL1;
	} else if (!strcmp(comando, "sel2"))
	{
		return SEL2;
	} else if (!strcmp(comando, "sel3"))
	{
		return SEL3;
	} else if (!strcmp(comando, "help"))
	{
		return HELP;
	} else {
		return NOP;
	}
}

void ejecuta_comando(Client *client, comandos comando, int size)
{
	uint16_t antes, despues;
	copia_a_resultado(size);
	switch(comando)
	{
		case BUBBLE0:
			antes = micros();
			bubble0(resultado, size);
			despues = micros();

			(*client).print("Tiempo Bubble0: ");
			(*client).println(despues - antes);
			break;

		case BUBBLE1:
			antes = micros();
			bubble1(resultado, size);
			despues = micros();

			(*client).print("Tiempo Bubble1: ");
			(*client).println(despues - antes);
			break;

		case BUBBLE2:
			antes = micros();
			bubble2(resultado, size);
			despues = micros();

			(*client).print("Tiempo Bubble2: ");
			(*client).println(despues - antes);
			break;

		case BUBBLE3:
			antes = micros();
			bubble3(resultado, size);
			despues = micros();

			(*client).print("Tiempo Bubble3: ");
			(*client).println(despues - antes);
			break;

		case QUICK0:
			antes = micros();
			quicksort0(resultado, 0, size - 1);
			despues = micros();

			(*client).print("Tiempo QuickSort0: ");
			(*client).println(despues - antes);
			break;

		case QUICK1:
			antes = micros();
			quicksort1(resultado, 0, size - 1);
			despues = micros();

			(*client).print("Tiempo QuickSort1: ");
			(*client).println(despues - antes);
			break;

		case QUICK2:
			antes = micros();
			quicksort2(resultado, 0, size - 1);
			despues = micros();

			(*client).print("Tiempo QuickSort2: ");
			(*client).println(despues - antes);
			break;

		case QUICK3:
			antes = micros();
			quicksort3(resultado, 0, size - 1);
			despues = micros();

			(*client).print("Tiempo QuickSort3: ");
			(*client).println(despues - antes);
			break;

		case SEL0:
			antes = micros();
			selection0(resultado, size);
			despues = micros();

			(*client).print("Tiempo Selection0: ");
			(*client).println(despues - antes);
			break;

		case SEL1:
			antes = micros();
			selection1(resultado, size);
			despues = micros();

			(*client).print("Tiempo Selection0: ");
			(*client).println(despues - antes);
			break;

		case SEL2:
			antes = micros();
			selection2(resultado, size);
			despues = micros();

			(*client).print("Tiempo Selection0: ");
			(*client).println(despues - antes);
			break;

		case SEL3:
			antes = micros();
			selection3(resultado, size);
			despues = micros();

			(*client).print("Tiempo Selection0: ");
			(*client).println(despues - antes);
			break;

		case HELP:
			(*client).println("Comandos disponibles:\n");
			(*client).println("bubble0")
			(*client).println("bubble1")
			(*client).println("bubble2")
			(*client).println("bubble3")
			(*client).println("quick0")
			(*client).println("quick1")
			(*client).println("quick2")
			(*client).println("quick3")
			(*client).println("sel0")
			(*client).println("sel1")
			(*client).println("sel2")
			(*client).println("sel3")
			break;

		default:
			(*client).println("Comando invalido");
			break;

	}
}