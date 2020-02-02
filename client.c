#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

struct sockaddr_in indirizzo; // globale solo per inizializzarla a zero

int main() {
	
	int s;
	int t;
	char request[1000];
	char response[1000];
	
	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1){
		
		perror("FAILED SOCKET"); // mette i ':' in automatico + una stringa di errore
		
	}
	
	indirizzo.sin_family = AF_INET; // va riscritto perchè ci possono essere famiglie compatibili
	indirizzo.sin_port = htons(80); // http , htons per convertire short in network byte order
	((unsigned char *)&(indirizzo.sin_addr.s_addr)) [0] = 216; 
	((unsigned char *)&(indirizzo.sin_addr.s_addr)) [1] = 58;    // singoli byte 0 - 255 dell'indirizzo ip
	((unsigned char *)&(indirizzo.sin_addr.s_addr)) [2] = 213; 	// es. 216.58.213.228 --> www.google.com
	((unsigned char *)&(indirizzo.sin_addr.s_addr)) [3] = 228;
	
	t = connect(s, (struct sockaddr *) &indirizzo, sizeof(struct sockaddr_in));
	if (t == -1){
		
		perror("CONNECT FALLITA"); // mette i ':' in automatico + una stringa di errore
		
	}
	
	sprintf(request, "GET /\r\n"); // '\n' e altri sono un solo carattere
	printf("Aspetta. . .");
	scanf("%d", &t);
	write(s, request, 7); // 7 caratteri nella stringa dentro sprintf
	t = read(s, response, 1000);
	response[t]=0;
	printf("%s", response);
	
}



