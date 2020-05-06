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

	int esik_deger, kapasite, kullanilanNode = 1,secim,exit = 0;//deðiþken tanýmlamalarý. 'secim' menü de gezmek için.
	char buffer[max];											//buffer stringi txt dosyasýndan veya kullanýcýdan aldýðýmýz deðerleri geçici olarak tutar.
	int flag = 0;
	
	NODE *head = (NODE*)malloc(sizeof(NODE));					//head için yer açma

	head->next = NULL;											//ilk tanýmlamalar
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
		// not defterinde deðerler T=4 , L=5 gibi yazýlmalý. Boþluklar dahil !
		if (buffer[0] == 84) {
			esik_deger = (int)buffer[2] - 48;	// 48 sýfýrýn ascii deðeri. 
												//onu çýkararak buffer[2] deki karakterin sayýsal karþýlýðýný elde ediyoruz.
			fscanf(fp, "%s", buffer);
		
			fscanf(fp, "%s", buffer);
	
			if (buffer[0] == 76) {
				kapasite = (int)buffer[2] - 48;	// 48 sýfýrýn ascii deðeri.
												//onu çýkararak buffer[2] deki karakterin sayýsal karþýlýðýný elde ediyoruz.
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
			fscanf(fp, "%s", buffer);		//file ýn sonuna kadar taramasý için !feof(fp) yazdýk.
				
			if (!adresAra(head, buffer, esik_deger,&flag)) {	
																	//adresAra fonksiyonu filedan aldýðýmýz adresin mevcut olup olmadýðýna bakar.
			                                                      	// mevcut ise 1 döndürür deðilse 0.
				if (kullanilanNode == kapasite) {	
					deleteLastNode(head);							//Mevcut nodelarýn sayisi tutuluyor.
					kullanilanNode--;								// Aþma varsa en son node siliniyor.
					
				}
																	//Kullanýlan node sayisini arttýrmamýz lazým.
				kullanilanNode++;									//adresAra fonksiyonunda bulamadðýmýz için yeni bir node oluþturmamýz gerek.
				head = insertNode(head, buffer);					//Bununda head olmasý için fonksiyon yeni eklenen node un adresini döndürüyor.
			}														
			else{
				
				if(flag == 1){
					
					head = makeHead(head, buffer);					//Bu fonksiyon Eþik deðeri aþan (T) node u head yapar. Flag bize eþik deðeri
					flag = 0;										//aþan bir node olduðunu gösterir.
				}
			}
		
			printNodes(head);										//Yazdýrma fonksiyonu
		}
	}
	
	// manuel alma
	else if(secim == 2){
		printf("Kapasite (L) yi giriniz.\n");
		scanf("%d",&kapasite);
		printf("Esik degeri (T) giriniz.\n");		// T ve L yi aldýk.
		scanf("%d",&esik_deger);
		
		printf("Esik deger :%d\n", esik_deger);
		printf("Kapasite :%d\n", kapasite);
		
		printf("ilk addresi giriniz.\n");			//Headi yerleþtirdik.
		scanf("%s",buffer);
		strcpy(head->adres,buffer);
		head->sayac = 1;
	
		while (!exit) {								//Kullanýcý Çýkýþ yapmak isteyene kadar adres alýcaz.
			printf("Adres giriniz.\n");				
			printf("Cikmak icin STOP yaziniz.\n");
			scanf("%s",buffer);						//Adresi aldýk. Bufferda saklýyoruz.
			
			if(strcmp(buffer,"STOP")){				//Eðer stop ise strcmp() fonksiyonu 0 döndürücek ve buraya girmicek akýþ.
				if (!adresAra(head, buffer, esik_deger,&flag)) {	//adresAra fonksiyonu filedan aldýðýmýz adresin mevcut olup olmadýðýna bakar.
																	// mevcut ise 1 döndürür deðilse 0.
					if (kullanilanNode == kapasite) {
						deleteLastNode(head);						//Mevcut nodelarýn sayisi tutuluyor.
						kullanilanNode--;							// Aþma varsa en son node siliniyor.
						
					}
																	//Kullanýlan node sayisini arttýrmamýz lazým.
					kullanilanNode++;								//adresAra fonksiyonunda bulamadðýmýz için yeni bir node oluþturmamýz gerek.
					head = insertNode(head, buffer);				//Bununda head olmasý için fonksiyon yeni eklenen node un adresini döndürüyor.
				}
				else{
					
					if(flag == 1){
					
						head = makeHead(head, buffer);				//Bu fonksiyon Eþik deðeri aþan (T) node u head yapar. Flag bize eþik deðeri
						flag = 0;									//aþan bir node olduðunu gösterir.
					}	
				}
			}
			
			else {
				exit = 1;											//While dönügüsünden çýkarýr.
			}
		
			printNodes(head);										//Yazdýrma fonksiyonu
		}			
		
		
	}
	
	
	printf("Cache i temizlemek icin ( 1 ) e basiniz. ?\n");
	printf("Bir sey yapmamak icin ( 2 ) e basiniz ? ");
	scanf("%d",&secim);
	
	if(secim == 1){
		clearList(head);											//Bütün nodelarý free eder.
		printf("Temizlendi");
	}	
	
	
	return 0;
}
void clearList(NODE *head){
	
	NODE *current;
	
	while(head->next != NULL){
		current = head;				//Sýrasý çok önemlidir. Current headin bir öncesini tutar. Current free edilir. 
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
	current->prew->next = NULL;			//Bir önceki Node un nextini null yaparýz.
	free(current);						//Son node un adresini serbest býrakýrýz.
}
void printNodes(NODE *head) {
	NODE *current = head;
	while (current != NULL) {	
		printf("( %s , %d )", current->adres, current->sayac);	//Head den son node a kadar adým adým ilerleyerek yazdýrýrýz.
		current = current->next;
	}
	printf(" \n");
}

int adresAra(NODE *head, char buffer[max], int esik_degeri, int *flag) { // 1 dönerse var 0 dönerse yeni node açmamiz lazim
	NODE *current = head;							
													//Bütün nodelarda buffer daki stringle ayný olan bir adres var mý diye kontrol etmemiz gerek.
	while (current != NULL) {

		if (!strcmp(current->adres, buffer)) {		//Adres ayný deðilse bir sonrakini deneriz.Ayný ise..
			current->sayac++;						//Sayaçýný 1 arttýrýrýz.
			
			if (current->sayac > esik_degeri  ) {
				*flag = 1;							//Eþik deðerden büyük olduysa Head yapmamýz gerek.
													//Flagi 1 yaparak bir Node un eþiði açtýðýný belirticez.
													//Her seferinde aramamýza gerek kalmýcak.
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
		current = current->next;					//head yapýcaðýmýz node u bulur.
	}
	
	if ((current->next != NULL) && (current->prew != NULL)) {	//Eðer Node listenin arasýndaysa böyle yapmamýz gerek
		current->prew->next = current->next;					//Önceki ve sonraki node larý birbirine baðlarýz
		current->next->prew = current->prew;					//Böylece bozulmaz.
		
	}
	
	
	else if(current->next == NULL && current->prew != NULL){	//Listenin sonundaysa
		current->prew->next = NULL;
	}
	
	
	else {														//Eðer baþýndaysa
		return current;
	}
	
	head->prew = current;
	current->next = head;
	current->prew = NULL;
	

	return current;


}



NODE* insertNode(NODE *head, char buffer[max]) {

	NODE *newHead = (NODE*)malloc(sizeof(NODE));		// Yeni node için yer açarýz.
	head->prew = newHead;								//headin öncesine yerleþtirmemiz gerekir.
	newHead->next = head;								
	newHead->prew = NULL;								//Head olucaðý için prew null olmasý lazým.
	newHead->sayac = 1;
	strcpy(newHead->adres, buffer);

	return newHead;
}

