#include <chipKITEthernet.h>
#include <IOShieldOled.h>
#include "funciones.h"

#define MAX_LONG_MENSAJE 	8192
#define MAX_LONG_ARRAY		MAX_LONG_MENSAJE / 2

uint8_t mensaje[MAX_LONG_MENSAJE];
char comando[16];
int array_numeros[MAX_LONG_ARRAY];
bool	primer_mensaje = true;


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

void print_array(int *array, int len);
void ejecuta_comando(Client *cliente, char *, int *, int);
void array_aleatorio(void);

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

	if (cliente)
	{
		if(primer_mensaje)
		{
			cliente.flush();
			primer_mensaje = false;
		}
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
							//num_comando = NOP;
							cantidad_num = 0;
							break;
						}
						memcpy(comando, mensaje, i);
						//num_comando = deco_comando();
					} else
					{
						if (mensaje[i - 1] != '\r')
						{
							if(sscanf(numero, "%d", &array_numeros[n]) < 1)
							{
								Serial.println("Error al convertir");
								Serial.print("Num: ");
								Serial.println(numero);
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

		ejecuta_comando(&cliente, comando, array_numeros,longitud);
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

void ejecuta_comando(Client *cliente, char *comando, int *array, int longitud)
{
	uint16_t antes_micros, despues_micros, antes_millis, despues_millis;
	char tiempos[16];
	void (*fcomando)(int *, int );
	bool comando_valido = true;

	IOShieldOled.clear();
	IOShieldOled.setCursor(0,0);
	
	//Configuramos el pin 70 (LD1 en la placa IOShield) como salida digital
	TRISAbits.TRISA0 = 0;
	LATAbits.LATA0 = 0;
	if (!strcmp(comando, "bubble0"))
	{
		fcomando = bubble0;
	} else if (!strcmp(comando, "bubble1"))
	{
		fcomando = bubble1;
	} else if (!strcmp(comando, "bubble2"))
	{
		fcomando = bubble2;
	} else if (!strcmp(comando, "bubble3"))
	{
		fcomando = bubble3;
	} else if (!strcmp(comando, "quick0"))
	{
		fcomando = quick0;
	} else if (!strcmp(comando, "quick1"))
	{
		fcomando = quick1;
	} else if (!strcmp(comando, "quick2"))
	{
		fcomando = quick2;
	} else if (!strcmp(comando, "quick3"))
	{
		fcomando = quick3;
	} else if (!strcmp(comando, "sel0"))
	{
		fcomando = selection0;
	} else if (!strcmp(comando, "sel1"))
	{
		fcomando = selection1;
	} else if (!strcmp(comando, "sel2"))
	{
		fcomando = selection2;
	} else if (!strcmp(comando, "sel3"))
	{
		fcomando = selection3;
	} else if (!strcmp(comando, "help"))
	{
		(*cliente).println("");
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
		(*cliente).println("comparar");
		(*cliente).println("exit");
		(*cliente).println("");
		comando_valido = false;
	} else if (!strcmp(comando, "comparar"))
  {
     // return COMP;
     comando_valido = false;
  } else if (!strcmp(comando, "exit"))
	{
		(*cliente).stop();
		Serial.println("Cliente desconectado");
		primer_mensaje = true;
		comando_valido = false;
	} else {
		//return NOP;
		(*cliente).println("Comando invalido");
		comando_valido = false;
	}

	if(comando_valido)
	{
		antes_micros = micros();
		antes_millis = millis();
		LATAbits.LATA0 = 1;
		(*fcomando)(array, longitud);
		LATAbits.LATA0 = 0;
		despues_micros = micros();
		despues_millis = millis();

		(*cliente).print("Tiempo en microsegundos: ");
		(*cliente).println(despues_micros - antes_micros);
		(*cliente).print("Tiempo en milisegundos: ");
		(*cliente).println(despues_millis - antes_millis);

		IOShieldOled.putString("Tiempos");
		IOShieldOled.setCursor(0,1);
		sprintf(tiempos,"%d ms - %d us", despues_millis - antes_millis, despues_micros - antes_micros);
		IOShieldOled.putString(tiempos);
	}

}

/*
 * Rellena array_numeros con numeros aleatorios
 */
void array_aleatorio(void)
{
	for (int i = 0; i < MAX_LONG_ARRAY; i++)
	{
		array_numeros[i] = (int)random(1L<<(sizeof(int)*8 - 1));
	}
}
