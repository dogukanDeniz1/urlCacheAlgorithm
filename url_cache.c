#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 100



struct Node {
	int sayac;
	struct Node* next;
	struct Node* prew;
	char adres[max];
}typedef NODE;



NODE* makeHead(NODE*, char []);
NODE* insertNode(NODE *, char[]);
int adresAra(NODE *, char[], int, int*);
void printNodes(NODE *);
void deleteLastNode(NODE *);
void clearList(NODE *);


int main() {

	int esik_deger, kapasite, kullanilanNode = 1,secim,exit = 0;//de�i�ken tan�mlamalar�. 'secim' men� de gezmek i�in.
	char buffer[max];											//buffer stringi txt dosyas�ndan veya kullan�c�dan ald���m�z de�erleri ge�ici olarak tutar.
	int flag = 0;
	
	NODE *head = (NODE*)malloc(sizeof(NODE));					//head i�in yer a�ma

	head->next = NULL;											//ilk tan�mlamalar
	head->prew = NULL;
	
	printf("input.txt den veri almak icin ( 1 ) e basiniz.\nManuel olarak girmek icin ( 2 ) ye basiniz.\n");
	scanf("%d",&secim);
	
	// input.txt ile alma
	if(secim == 1){
		
		FILE *fp;
		fp = fopen("input.txt", "r");
		if(fp == NULL){
			printf("Dosya yok.");
			return 0;
		}
		fscanf(fp, "%s", buffer);
		// Esik degeri ve kapasiteyi input.txt dosyasindan set ettik;
		// not defterinde de�erler T=4 , L=5 gibi yaz�lmal�. Bo�luklar dahil !
		if (buffer[0] == 84) {
			esik_deger = (int)buffer[2] - 48;	// 48 s�f�r�n ascii de�eri. 
												//onu ��kararak buffer[2] deki karakterin say�sal kar��l���n� elde ediyoruz.
			fscanf(fp, "%s", buffer);
		
			fscanf(fp, "%s", buffer);
	
			if (buffer[0] == 76) {
				kapasite = (int)buffer[2] - 48;	// 48 s�f�r�n ascii de�eri.
												//onu ��kararak buffer[2] deki karakterin say�sal kar��l���n� elde ediyoruz.
			}
			else{
				printf("Yazim hatasi !!!!");
				return 0;
			}
		}
		else{
			printf("Yazim hatasi !!!!");
			return 0;
		}
		
	
		//***********************************
	
		printf("Esik deger :%d\n", esik_deger);
		printf("Kapasite :%d\n", kapasite);
		
		
		fscanf(fp, "%s", buffer);		// headi yerlestirdik
		strcpy(head->adres, buffer);	
		head->sayac = 1;
		
		
		printNodes(head);
	
		while (!feof(fp)) {					
			fscanf(fp, "%s", buffer);		//file �n sonuna kadar taramas� i�in !feof(fp) yazd�k.
				
			if (!adresAra(head, buffer, esik_deger,&flag)) {	
																	//adresAra fonksiyonu filedan ald���m�z adresin mevcut olup olmad���na bakar.
			                                                      	// mevcut ise 1 d�nd�r�r de�ilse 0.
				if (kullanilanNode == kapasite) {	
					deleteLastNode(head);							//Mevcut nodelar�n sayisi tutuluyor.
					kullanilanNode--;								// A�ma varsa en son node siliniyor.
					
				}
																	//Kullan�lan node sayisini artt�rmam�z laz�m.
				kullanilanNode++;									//adresAra fonksiyonunda bulamad��m�z i�in yeni bir node olu�turmam�z gerek.
				head = insertNode(head, buffer);					//Bununda head olmas� i�in fonksiyon yeni eklenen node un adresini d�nd�r�yor.
			}														
			else{
				
				if(flag == 1){
					
					head = makeHead(head, buffer);					//Bu fonksiyon E�ik de�eri a�an (T) node u head yapar. Flag bize e�ik de�eri
					flag = 0;										//a�an bir node oldu�unu g�sterir.
				}
			}
		
			printNodes(head);										//Yazd�rma fonksiyonu
		}
	}
	
	// manuel alma
	else if(secim == 2){
		printf("Kapasite (L) yi giriniz.\n");
		scanf("%d",&kapasite);
		printf("Esik degeri (T) giriniz.\n");		// T ve L yi ald�k.
		scanf("%d",&esik_deger);
		
		printf("Esik deger :%d\n", esik_deger);
		printf("Kapasite :%d\n", kapasite);
		
		printf("ilk addresi giriniz.\n");			//Headi yerle�tirdik.
		scanf("%s",buffer);
		strcpy(head->adres,buffer);
		head->sayac = 1;
	
		while (!exit) {								//Kullan�c� ��k�� yapmak isteyene kadar adres al�caz.
			printf("Adres giriniz.\n");				
			printf("Cikmak icin STOP yaziniz.\n");
			scanf("%s",buffer);						//Adresi ald�k. Bufferda sakl�yoruz.
			
			if(strcmp(buffer,"STOP")){				//E�er stop ise strcmp() fonksiyonu 0 d�nd�r�cek ve buraya girmicek ak��.
				if (!adresAra(head, buffer, esik_deger,&flag)) {	//adresAra fonksiyonu filedan ald���m�z adresin mevcut olup olmad���na bakar.
																	// mevcut ise 1 d�nd�r�r de�ilse 0.
					if (kullanilanNode == kapasite) {
						deleteLastNode(head);						//Mevcut nodelar�n sayisi tutuluyor.
						kullanilanNode--;							// A�ma varsa en son node siliniyor.
						
					}
																	//Kullan�lan node sayisini artt�rmam�z laz�m.
					kullanilanNode++;								//adresAra fonksiyonunda bulamad��m�z i�in yeni bir node olu�turmam�z gerek.
					head = insertNode(head, buffer);				//Bununda head olmas� i�in fonksiyon yeni eklenen node un adresini d�nd�r�yor.
				}
				else{
					
					if(flag == 1){
					
						head = makeHead(head, buffer);				//Bu fonksiyon E�ik de�eri a�an (T) node u head yapar. Flag bize e�ik de�eri
						flag = 0;									//a�an bir node oldu�unu g�sterir.
					}	
				}
			}
			
			else {
				exit = 1;											//While d�n�g�s�nden ��kar�r.
			}
		
			printNodes(head);										//Yazd�rma fonksiyonu
		}			
		
		
	}
	
	
	printf("Cache i temizlemek icin ( 1 ) e basiniz. ?\n");
	printf("Bir sey yapmamak icin ( 2 ) e basiniz ? ");
	scanf("%d",&secim);
	
	if(secim == 1){
		clearList(head);											//B�t�n nodelar� free eder.
		printf("Temizlendi");
	}	
	
	
	return 0;
}
void clearList(NODE *head){
	
	NODE *current;
	
	while(head->next != NULL){
		current = head;				//S�ras� �ok �nemlidir. Current headin bir �ncesini tutar. Current free edilir. 
		head=head->next;			
		free(current);
	}
	
}
void deleteLastNode(NODE *head) {
	NODE *current = head;
	while (current->next != NULL) {
										//Listenin sonuna gider.
		current = current->next;
	}
	current->prew->next = NULL;			//Bir �nceki Node un nextini null yapar�z.
	free(current);						//Son node un adresini serbest b�rak�r�z.
}
void printNodes(NODE *head) {
	NODE *current = head;
	while (current != NULL) {	
		printf("( %s , %d )", current->adres, current->sayac);	//Head den son node a kadar ad�m ad�m ilerleyerek yazd�r�r�z.
		current = current->next;
	}
	printf(" \n");
}

int adresAra(NODE *head, char buffer[max], int esik_degeri, int *flag) { // 1 d�nerse var 0 d�nerse yeni node a�mamiz lazim
	NODE *current = head;							
													//B�t�n nodelarda buffer daki stringle ayn� olan bir adres var m� diye kontrol etmemiz gerek.
	while (current != NULL) {

		if (!strcmp(current->adres, buffer)) {		//Adres ayn� de�ilse bir sonrakini deneriz.Ayn� ise..
			current->sayac++;						//Saya��n� 1 artt�r�r�z.
			
			if (current->sayac > esik_degeri  ) {
				*flag = 1;							//E�ik de�erden b�y�k olduysa Head yapmam�z gerek.
													//Flagi 1 yaparak bir Node un e�i�i a�t���n� belirticez.
													//Her seferinde aramam�za gerek kalm�cak.
			}

			return 1;
		}
		current = current->next;
	}
	return 0;
}
NODE* makeHead(NODE *head, char buffer[max]) {
	
	NODE *current = head;						
	while(strcmp(current->adres,buffer)){
		current = current->next;					//head yap�ca��m�z node u bulur.
	}
	
	if ((current->next != NULL) && (current->prew != NULL)) {	//E�er Node listenin aras�ndaysa b�yle yapmam�z gerek
		current->prew->next = current->next;					//�nceki ve sonraki node lar� birbirine ba�lar�z
		current->next->prew = current->prew;					//B�ylece bozulmaz.
		
	}
	
	
	else if(current->next == NULL && current->prew != NULL){	//Listenin sonundaysa
		current->prew->next = NULL;
	}
	
	
	else {														//E�er ba��ndaysa
		return current;
	}
	
	head->prew = current;
	current->next = head;
	current->prew = NULL;
	

	return current;


}



NODE* insertNode(NODE *head, char buffer[max]) {

	NODE *newHead = (NODE*)malloc(sizeof(NODE));		// Yeni node i�in yer a�ar�z.
	head->prew = newHead;								//headin �ncesine yerle�tirmemiz gerekir.
	newHead->next = head;								
	newHead->prew = NULL;								//Head oluca�� i�in prew null olmas� laz�m.
	newHead->sayac = 1;
	strcpy(newHead->adres, buffer);

	return newHead;
}

