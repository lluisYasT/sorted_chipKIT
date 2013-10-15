#include <chipKITEthernet.h>
#include <IOShieldOled.h>
#include "funciones.h"

#define MAX_LONG_MENSAJE 	8192
#define MAX_LONG_ARRAY		MAX_LONG_MENSAJE / 2

uint8_t mensaje[MAX_LONG_MENSAJE];
char comando[16];
int array_numeros[MAX_LONG_ARRAY];

// Enter a MAC address and IP address for your controller below.
// A zero MAC address means that the chipKIT MAC is to be used
byte mac[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

//			 !!MODIFY THIS!!
// The IP address will be dependent on your local network:
byte ip[] = {
	10,0,0,8 };

//Estos campos estan comentados ya que no necesitamos acceso
//fuera de la red local. En caso de necesitarlo (para acceder
//desde una red externa) se pueden descomentar y cambiar la
//linea Ethernet.begin dentro de la funcion setup por la que
//esta comentada.
//byte router[] = { 10,0,0,1 };
//byte subred[] = { 255, 255, 255, 0 };

// Iniciamos el servidor en el puerto 23 (Telnet)
Server server(23);

typedef enum comandos {
	NOP,
	HELP,
	EXIT,
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
    COMP,
} comandos;

void print_array(int *array, int len);
comandos deco_comando(void);
void ejecuta_comando(Client *cliente, comandos, int *, int);

void setup()
{
	// Inicializamos el dispositivo de red.
	//	Ethernet.begin(mac, ip, router, subred);
	Ethernet.begin(mac,ip);
	// Inicializamos el servidor
	server.begin();
	// Abrimos el puerto serie
	Serial.begin(9600);

	//Inicializamos la pantalla Oled
	IOShieldOled.begin();
	IOShieldOled.setCursor(0, 0);
	IOShieldOled.putString("Sorted ChipKIT");
}



void loop()
{
	Client cliente = server.available();
	uint long_mensaje = 0;
	int cantidad_num = 0;
	int n = 0;
	int longitud = 0;
	comandos num_comando = NOP;

	//Mensaje de prueba en la pantalla Oled
	//IOShieldOled.clearBuffer();

	if (cliente)
	{
		mensaje = {0};
		comando = {0};
		array_numeros = {NULL};

		if(cliente.available())
		{
			//Recepcion del mensaje
			char c;
			do
			{
				c = cliente.read();
				if(c != -1)
				{
					mensaje[long_mensaje] = c;
					if(long_mensaje < MAX_LONG_MENSAJE - 1)
					{
						long_mensaje++;
					} else
					{
						cliente.println("Array demasiado largo");
						mensaje = {0};
						long_mensaje = 0;
						break;
					}
				}
			} while(c != '\n');

			Serial.print("Longitud del mensaje: ");
			Serial.println(long_mensaje);

			char numero[16] = {0};
			int j = 0;

			for (int i = 0; i < long_mensaje; ++i)
			{
				if(mensaje[i] == ' '
					|| mensaje[i] == ','
					|| mensaje[i] == '\t'
					|| mensaje[i] == '\r'
					|| mensaje[i] == '\n')
				{
					if(cantidad_num == 0)
					{
						if(i>16)
						{
							num_comando = NOP;
							cantidad_num = 0;
							break;
						}
						memcpy(comando, mensaje, i);
						num_comando = deco_comando();
					} else
					{
						if (mensaje[i - 1] != '\r')
						{
							if(sscanf(numero, "%d", &array_numeros[n]) < 1)
							{
								Serial.println("Error al convertir");
								Serial.print("Num: ");
								Serial.println(numero);
								//longitud = 0;
								//array_numeros = {NULL};
								//break;
							} else
							{
								n++;
								j = 0;
								numero = {0};
							}
						}

					}
					cantidad_num++;
				} else
				{
					if(cantidad_num > 0)
					{
						numero[j] = mensaje[i];
						j++;
					}
				}
			}

			if(cantidad_num > 0)
			{
				longitud = n;
				Serial.print("Longitud del array: ");
				Serial.println(longitud);
			}

			Serial.println(comando);
		}

		cliente.flush();

		ejecuta_comando(&cliente, num_comando, array_numeros,longitud);
		if(longitud)
		{
			print_array(array_numeros, longitud);
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
	} else if (!strcmp(comando, "comparar"))
    {
        return COMP;
    } else if (!strcmp(comando, "exit"))
	{
		return EXIT;
	} else {
		return NOP;
	}
}

void ejecuta_comando(Client *cliente, comandos comando, int *array, int longitud)
{
	uint16_t antes_micros, despues_micros, antes_millis, despues_millis;
	char tiempos[16];

	IOShieldOled.clear();
	IOShieldOled.setCursor(0,0);

	switch(comando)
	{
		case BUBBLE0:
			antes_micros = micros();
			antes_millis = millis();
			bubble0(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Bubble0 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Bubble0 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos Bubble0");
			IOShieldOled.setCursor(0,1);
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case BUBBLE1:
			antes_micros = micros();
			antes_millis = millis();
			bubble1(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Bubble1 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Bubble1 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos Bubble1");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case BUBBLE2:
			antes_micros = micros();
			antes_millis = millis();
			bubble2(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Bubble2 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Bubble2 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos Bubble2");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case BUBBLE3:
			antes_micros = micros();
			antes_millis = millis();
			bubble3(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Bubble3 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Bubble3 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos Bubble3");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case QUICK0:
			antes_micros = micros();
			antes_millis = millis();
			quicksort0(array, 0, longitud - 1);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo QuickSort0 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Quicksort0 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos quick0");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case QUICK1:
			antes_micros = micros();
			antes_millis = millis();
			quicksort1(array, 0, longitud - 1);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo QuickSort1 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Quicksort1 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos quick1");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case QUICK2:
			antes_micros = micros();
			antes_millis = millis();
			quicksort2(array, 0, longitud - 1);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo QuickSort2 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Quicksort2 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos quick2");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case QUICK3:
			antes_micros = micros();
			antes_millis = millis();
			quicksort3(array, 0, longitud - 1);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo QuickSort3 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Quicksort3 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos quick3");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case SEL0:
			antes_micros = micros();
			antes_millis = millis();
			selection0(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Selection0 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Selection0 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos sel0");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case SEL1:
			antes_micros = micros();
			antes_millis = millis();
			selection1(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Selection1 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Selection1 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos sel1");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case SEL2:
			antes_micros = micros();
			antes_millis = millis();
			selection2(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Selection2 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Selection2 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos sel2");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

		case SEL3:
			antes_micros = micros();
			antes_millis = millis();
			selection3(array, longitud);
			despues_micros = micros();
			despues_millis = millis();

			(*cliente).print("Tiempo Selection3 en microsegundos: ");
			(*cliente).println(despues_micros - antes_micros);
			(*cliente).print("Tiempo Selection3 en milisegundos: ");
			(*cliente).println(despues_millis - antes_millis);

			IOShieldOled.putString("Tiempos sel3");
			IOShieldOled.setCursor(0,1);
			
			sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
			IOShieldOled.putString(tiempos);
			break;

        case COMP:
            /*
             * Debe generar un array grande con numeros aleatorios
             * y ejecutar todas las funciones anteriores, mostrando
             * los resultados al cliente
             */
            break;

		case HELP:
			(*cliente).println("Comandos disponibles:\n");
			(*cliente).println("bubble0");
			(*cliente).println("bubble1");
			(*cliente).println("bubble2");
			(*cliente).println("bubble3");
			(*cliente).println("quick0");
			(*cliente).println("quick1");
			(*cliente).println("quick2");
			(*cliente).println("quick3");
			(*cliente).println("sel0");
			(*cliente).println("sel1");
			(*cliente).println("sel2");
			(*cliente).println("sel3");
			(*cliente).println("");
			break;

		case EXIT:
			(*cliente).stop();
			Serial.println("Cliente desconectado");
			break;

		default:
			(*cliente).println("Comando invalido");
			break;

	}
}
