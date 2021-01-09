#include<stdio.h>
#include<stdlib.h>
#include<locale.h>
#include<string.h>
#include<time.h>
#define tam 50
#define mao 5
#define jog 8

//Estrutura de dado para carta
typedef struct carta{
	int numero;
	int naipe;
}carta;

//Estrutura de dado para pilha baralho inserir carta
typedef struct baralho{
	carta jogo[tam];
	int topo;
}baralho;

//Estrutura de dado para jogador
typedef struct jogador{
	char nome[30];
	int idade;
	int numero_vidas;
}jogador;

//Estrutura de dado para fila de jogador ordem de jogada
typedef struct fila_jogador{
	jogador jogo[jog];
	int inicio;
	int final;
}fila_jogador;

//Estrutura de dado para cartas na mao do jogador
typedef struct cartas_mao_jogad{
	carta jogo[mao];
	int final;
}cartas_mao_jogad;

//Fun��o para criar a pilha de baralho
baralho* criapilha();

//Fun��o para criar a fila de jogador
fila_jogador* criafila();

//Fun��o para criar a lista de cartas na mao
cartas_mao_jogad* crialista(int quant);

//Fun��o para inser��o de carta na mao jogador na lista
int inserir(cartas_mao_jogad *p,int num,int nai);

//Fun��o para inser��o de jogador na fila
int inserir_jogador(fila_jogador *p,char *nomes,int idades,int vidas);

//Fun��o para verificar se a pilha de cartas esta cheia
int estahcheia(baralho *p);

//Fun��o para verificar se a lista estah cheia
int cheia(fila_jogador *p);

//Fun��o para verificar se a pilha de cartas estah vazia
int estahvazia(baralho *p);

//Fun��o para verificar se a lista estah vazia
int vazia(cartas_mao_jogad *p);

//Fun��o para empilhar cartas na pilha baralho
int empilhar(baralho *p,int num,int nai);

//Fun��o para criar baralho com as cartas
void cartas(baralho *p);

//Fun��o para embaralhar as cartas do baralho
void embaralha_cartas(baralho *p,baralho *p_bara,int tama);

//Fun��o para liberar pilha
void libera(baralho *p);

//Fun��o para liberar fila
void liberar(fila_jogador *p);

//Fun��o para liberar lista
void libera_lista(cartas_mao_jogad *p);

//Fun��o para imprimir o baralho
void imprime(baralho *p);

//Fun��o menu
void menu_opc(int *opcao);

//Fun��o para cadastrar dados dos jogadores
void cadastro(fila_jogador *jogad,int quant_jogado);

//Fun��o para mostrar dados dos jogadores
void mostra_dados(fila_jogador *jogad);

//Fun��o para distribuir cartas para os jogadores
void distribui_cartas(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,baralho *p,baralho *q,int cont,int comec);

//Fun��o Remove pilha baralho
int remove_p(baralho *p,baralho *q,int *valor,int *num);

//Fun��o para numeros de jogadores no jogo seja valido
void numero_jogadores(int *quant_jogado);

//Fun��o para remover cartas da mao do jogador
void remove(cartas_mao_jogad *cartas_ma,int i,int *op,int *nume,int *nai);

//Fun��o para verificar o vencedor do jogo
int vencedor(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado);

//Fun��o para verificar quantas rodadas pode fazer
void verifica_rod(int *vetor,int rod,int k,int final,int comec,int val);

//Fun��o para perguntar quantas rodaddas o jogador faz
void pergunta_jogador(FILE *arquivo,cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,carta *jogadores,int *vet,int *p,int comec);

//Fun��o do jogo em andamento
void jogo(FILE *arquivo,cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,carta *jogadores,int comec,int *posi);

//Fun��o para pontua��o do jogo
void pontuacao(int quant_jogado,carta *jogadores,int *vetor,int *posi);

//Fun��o para comparar o numero de rodadas que fazia com a pontua��o
void compara(fila_jogador *jogad,int quant_jogado,int *vet,int *vetor);

//Fun��o para reposionar jogadores depois que tiver vida igual a zero
void realoca_jogadores(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,carta *jogadores,int pos);

//Fun��o para verificar vidas dos jogadores e reorganizar eles dentro do vetor
void verificar_vidas(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int *quant_jogado,carta *jogadores);

//Fun��o para op��o dois
void opcao_dois();

//Fun��o para caso d� empate
int empate(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado);

int main(){
	
	//Biblioteca para Portugues aceitar caracteres no nome
	setlocale(LC_ALL,"Portuguese");
	
	//Cria��o do arquivo
	FILE *arquivo;
	arquivo = fopen("fedap.txt","w+");
	
	//Vari�veis para ajudar no desenvolvimento do jogo
	int opcao=0,menu=0,quant_jogado=0,num,nai,cont=0,k=0,num_cart=5,comec=0,posi=-1,percu;
	//var�vel posi=-1 para armazenar a posi��o do jogador de maior carta na rodada, come�ar a proxima rodada
	
	//Cria��o da pilha Baralho   Fila Jogador  Cartas da m�o do Jogador
 	baralho *p,*p_bara;
	fila_jogador *jogad;
	cartas_mao_jogad *cartas_ma;
	
	//Vari�vel para armazenar as cartas de cada jogador na rodada
	carta *jogadores;
	
	do{
		
		//Menu de op��es
		if(menu == 0){
			menu_opc(&opcao);
			menu = 0;
		}
		
		//Caso o usu�rio vacalhe nas escolhas de op��es
		if(opcao < 0 || opcao > 2 && menu == 0){
			menu_opc(&opcao);
			menu = 0;
		}
		
		//Codigo pra descri��o do jogo
		if(opcao == 2 && menu == 0){
			opcao_dois();
			menu = 0;
		}
		
		//Codigo para sair do jogo
		if(opcao == 0){
			break;
		}
		
		//inicializa��o dos jogadores nome,idade,e vidas igual a 5
		if(opcao == 1 && menu == 0){
			
			//inicializa��o das vari�veis quando come�ar o jogo de novo;
			num,nai,cont=0,k=0,num_cart=5,comec=0,posi=-1,percu,quant_jogado=0;
			
			//inicializa��o das variaveis pilha Baralho
			p = criapilha();
			p_bara = criapilha();
			jogad = criafila();
			
			//Inicializa��o das cartas
			cartas(p);
			//imprime(p);
	
			//Embaralhar as cartas
			embaralha_cartas(p,p_bara,40);
			//imprime(p_bara);
			
			//Quantidade de jogadores
			numero_jogadores(&quant_jogado);
			//Insere jogador nome,idade
			cadastro(jogad,quant_jogado);
			//Mostra o nome ,idade e vidas do jogador
			mostra_dados(jogad);
			//Fun��o que cria a quantiadade de jogadores que vao receber cartas na m�o 
			cartas_ma = crialista(quant_jogado);
			//vari�vel para entrar no percurso do jogo
			percu = 3;
		}
		
		//Percurso do jogo 
		if(percu == 3){
			
			//Trecho de c�digo para volta das cartas para o baralho quando as cartas acabam
			if(estahvazia(p_bara)){
				libera(p_bara);
				p_bara = criapilha();
				embaralha_cartas(p,p_bara,40);
				//imprime(p_bara);
			}
			
			//Fun��o para realocar jogadores de acordo com numero de vidas
			verificar_vidas(cartas_ma,jogad,&quant_jogado,jogadores);
			
			//vetor para guardar a pontua��o de cada jogador
			int *vetor = (int*) calloc(quant_jogado,sizeof(int));
			//Vetor para guardar numero de rodadas que cada jogador faz
			int *vet = (int*)  calloc(quant_jogado,sizeof(int));
			
			//variavel para andar no vetor
			int  l = comec;	
			
			//Distribui as cartas para cada jogador
			distribui_cartas(cartas_ma,jogad,quant_jogado,p_bara,p,num_cart,comec);
			
			//Trecho que delimita quantas rodadas cada jogador pode fazer
			pergunta_jogador(arquivo,cartas_ma,jogad,quant_jogado,jogadores,vet,&l,comec);
			
			//Vari�vel para fazer o controle de n�mero de cartas daquela rodada
			int tot = num_cart;
			
			fprintf(arquivo,"\n\n\nPARTIDA DE %d CARTA:\n\n",tot);
			//Trecho de c�digo para numero de cartas a cada rodada ex: 5 cartas, 4 cartas...
			while(tot!=0){
				//vari�vel criada para guardar as cartas de cada jogador naquela jogada,para comparar a maior carta
				jogadores = (carta*) malloc(quant_jogado * sizeof(carta));
				jogo(arquivo,cartas_ma,jogad,quant_jogado,jogadores,comec,&posi);
				pontuacao(quant_jogado,jogadores,vetor,&posi);
				printf("\n\n");
				tot--;
			}
			
			//Vari�vel para ajudar quando o jogador fizer a maior pontua��o na rodada,determinando que na proxima rodada ele ir� come�ar
			posi = -1;
			
			//Trecho que compara a pontua��o do jogador com numero de rodadas que falou que fazia
			compara(jogad,quant_jogado,vet,vetor);
			mostra_dados(jogad);
			//system("cls");
			
			//vari�vel s� para entrar dentro do if do percurso do jogo		
			percu = 3;
			//vari�vel para decrescer o numero de cartas a cada partida
			num_cart--;
			
			//Esse if � para a rodada onde come�a com uma carta e assim sucessivamente
			if(num_cart == 0){
				percu = 4;
				num_cart = 1;
			}
			
			//Trecho de c�digo para alternar o recebimento de cartas dos jogadores
			comec++;
			if(comec == quant_jogado){
				comec = 0;
			}
			menu = 3;
			
			//if para caso d� empate no jogo
			int empat = empate(cartas_ma,jogad,quant_jogado);
			if(empat == 1){
				system("cls");
				printf("N�o ouve vencedor!!!");
				fprintf(arquivo,"N�o ouve vencedor!!!");
				opcao = -1;
				menu = 0;
				percu = -10;
				libera(p_bara);
				libera(p);
				liberar(jogad);
				libera_lista(cartas_ma);
			}
			
			//if para verificar o vencedor do jogo
			int venc = vencedor(cartas_ma,jogad,quant_jogado);
			if(venc != -1){
				system("cls");
				printf("\n\nO vencedor do jogo foi %s e tem %d vida!!!\n\n",jogad->jogo[venc].nome,jogad->jogo[venc].numero_vidas);
				fprintf(arquivo,"\n\nO vencedor do jogo foi %s e tem %d vida!!!\n\n",jogad->jogo[venc].nome,jogad->jogo[venc].numero_vidas);
				opcao = -1;
				menu = 0;
				percu = -10;
				libera(p_bara);
				libera(p);
				liberar(jogad);
				libera_lista(cartas_ma);
			}	
		}
		
		//Percurso do jogo onde o recebimento das carats come�a com um e assim sucessivamente
		if(percu == 4){
			
			//Trecho de c�digo para volta das cartas para o baralho quando as cartas acabam
			if(estahvazia(p_bara)){
				libera(p_bara);
				p_bara = criapilha();
				embaralha_cartas(p,p_bara,40);
				//imprime(p_bara);
			}
			
			
			//Fun��o para realocar jogadores de acordo com numero de vidas
			verificar_vidas(cartas_ma,jogad,&quant_jogado,jogadores);
			
			//vetor para guardarem as cartas em cada jogada para comparar maior
			int *vetor = (int*) calloc(quant_jogado,sizeof(int));
			//Vetor para guardar numero de rodadas que cada jogador faz
			int *vet = (int*)  calloc(quant_jogado,sizeof(int));
			
			//variavel para andar no vetor pra ajudar a controlar o numero de rodadas que o jogador pode fazer e guardar na posi��o dele
			int  l = comec;
			
			//Distribui as cartas para cada jogador
			distribui_cartas(cartas_ma,jogad,quant_jogado,p_bara,p,num_cart,comec);
			
			//Trecho que delimita quantas rodadas cada jogador pode fazer
			pergunta_jogador(arquivo,cartas_ma,jogad,quant_jogado,jogadores,vet,&l,comec);
			
			//vari�vel auxiliar
			int tot = num_cart;
			fprintf(arquivo,"\n\n\nPARTIDA DE %d CARTA:\n\n",tot);
			//Trecho de c�digo para numero de cartas a cada rodada ex: 5 cartas, 4 cartas...
			while(tot!=0){
				jogadores = (carta*) malloc(quant_jogado * sizeof(carta));
				jogo(arquivo,cartas_ma,jogad,quant_jogado,jogadores,comec,&posi);
				pontuacao(quant_jogado,jogadores,vetor,&posi);
				printf("\n\n");
				tot--;
			}
			posi = -1;
			//Trecho que compara a pontua��o do jogador com numero de rodadas que falou que fazia
			compara(jogad,quant_jogado,vet,vetor);
			mostra_dados(jogad);
			
			//vari�vel para entrar no percurso do jogo		
			percu = 4;
			num_cart++;
			
			if(num_cart == 5){
				opcao = 0;
			}
		
			//Parte para alternar o recebimento de cartas dos jogadores
			comec++;
			if(comec == quant_jogado){
				comec = 0;
			}
			menu = 3;
			
			//if para verificar se ouve empate no jogo
			int empat = empate(cartas_ma,jogad,quant_jogado);
			if(empat == 1){
				system("cls");
				printf("N�o ouve vencedor!!!");
				opcao = -1;
				menu = 0;
				percu = -10;
				libera(p_bara);
				libera(p);
				liberar(jogad);
				libera_lista(cartas_ma);
			}
			
			//Trecho de c�digo para verificar o vencedor do jogo
			int venc = vencedor(cartas_ma,jogad,quant_jogado);
			if(venc != -1){
				system("cls");
				printf("\n\nO vencedor do jogo foi %s e tem %d vida!!!\n\n",jogad->jogo[venc].nome,jogad->jogo[venc].numero_vidas);
				fprintf(arquivo,"\n\nO vencedor do jogo foi %s e tem %d vida!!!\n\n",jogad->jogo[venc].nome,jogad->jogo[venc].numero_vidas);
				opcao = -1;
				menu = 0;
				percu = -10;
				libera(p_bara);
				libera(p);
				liberar(jogad);
				libera_lista(cartas_ma);
			}
		}	
		
	}while(opcao != 0);
	
	return 0;
}

//Fun��o para criar pilha baralho
baralho* criapilha(){
	baralho *p;
	p = (baralho*) malloc(sizeof(baralho));
	p->topo = 0;
	return p;
}

//Fun��o para criar fila jogador
fila_jogador* criafila(){
	fila_jogador *p;
	p = (fila_jogador*) malloc(sizeof(fila_jogador));
	p->inicio = 0;
	p->final = 0;
	return p;
}


//Fun��o para criar lista cartas mao jogador
cartas_mao_jogad* crialista(int quant){
	
	cartas_mao_jogad *p;
	p = (cartas_mao_jogad*) malloc(quant * sizeof(cartas_mao_jogad));
	int i=0;
	
	for(i=0;i<quant;i++){
		p[i].final = 0;
	}
	return p;
}

//Fun��o para verificar se o baralho esta vazio
int estahvazia(baralho *p){
	if(p == NULL){
		return -1;
	}
	else if(p->topo == 0){
		return 1;
	}
	else{
		return 0;
	}
}

//Fun��o para verificar se a fila jogador estah vazia
int vazia(fila_jogador *p){
	if(p == NULL){
		return -1;
	}
	else if(p->final == 0){
		return 1;
	}
	else{
		return 0;
	}
}

//Fun��o para mostrar pilha de baralho
void imprime(baralho *p){
	for(int i=0;i<(p->topo);i++){
		printf("Numero:%d Naipe:%d\n\n",p->jogo[i].numero,p->jogo[i].naipe);
	}
	return;
}

//Fun��o para liberar pilha baralho
void libera(baralho *p){
	free(p);
}

//Fun��o para liberar fila jogador
void liberar(fila_jogador *p){
	free(p);
}

//Fun��o para liberar lista cartas mao jogadores
void libera_lista(cartas_mao_jogad *p){
	free(p);
}

//Fun��o para verificar se a pilha barlho esta cheia
int estahcheia(baralho *p){
	if(p == NULL){
		return -1;
	}
	else if(p->topo == tam){
		return 1;
	}
	else{
		return 0;
	}
}

//Fun��o para verificar se a fila jogador estah cheia
int cheia(fila_jogador *p){
	if(p == NULL){
		return -1;
	}
	else if(p->final == jog){
		return 1;
	}
	else{
		return 0;
	}	
}

//Fun��o para verificar se a lista cartas mao jogador estah cheia
int estacheia(cartas_mao_jogad *p){
	if(p == NULL){
		return -1;
	}
	else if(p->final == jog){
		return 1;
	}
	else{
		return 0;
	}	
}

//Fun��o para empilhar cartas na pilha
int empilhar(baralho *p,int num,int nai){
	if(estahcheia(p)){
		return 0;
	}
	else{
		p->jogo[p->topo].numero = num;
		p->jogo[p->topo].naipe = nai;
		p->topo++;
		return 1;
	}
}

//Fun��o (Lista) para inserir carta na mao dos jogadores 
int inserir(cartas_mao_jogad *p,int num,int nai){
	if(estacheia(p)){
		return 1;
	}
	else{
		p->jogo[p->final].numero = num;
		p->jogo[p->final].naipe = nai;
		p->final++;
		return 0;
	}
}

//Fun��o para inser��o na fila jogador
int inserir_jogador(fila_jogador *p,char *nomes,int idades,int vidas){
	if(cheia(p)){
		return 0;
	}
	else{
		strcpy(p->jogo[p->final].nome,nomes);
		p->jogo[p->final].idade = idades;
		p->jogo[p->final].numero_vidas = vidas;
		p->final++;
		return 1;
	}	
}

//Fun��o para inicializa��o das cartas
void cartas(baralho *p){
	int b,i,j;
	
	for(i=2;i<=7;i++){
		for(j=1;j<=4;j++){
			b = empilhar(p,i,j);
		}
	}
	
	for(i=11;i<=14;i++){
		for(j=1;j<=4;j++){
			b = empilhar(p,i,j);
		}
	}
	
	return;
}

//Fun��o para embaralhar as cartas 
void embaralha_cartas(baralho *p,baralho *p_bara,int tama){
	
	int i=0,vetor[40],num=0,j=0,b,r;
	srand((unsigned)time(NULL));
	
	for(i=0;i<40;i++){
		vetor[i] = i;
	}
	
	for(i=0;i<tama;i++){
		r = rand() % tama;
		int temp = vetor[i];
		vetor[i] = vetor[r];
		vetor[r] = temp;
	}	
	
	for(j=0;j<tama;j++){
		b = empilhar(p_bara,p->jogo[vetor[j]].numero,p->jogo[vetor[j]].naipe);
	}
	return;
}

//Fun��o menu
void menu_opc(int *opcao){
	int op;
	printf("\nBem Vindo ao Jogo Fedaputa:\n\n");
	printf("0 - N�o Jogar\n");
	printf("1 - Jogar Fedaputa\n");
	printf("2 - Creditos\n\n");
	printf("Op��o: ");
	scanf("%d",&op);
	*opcao = op;
	return;
}

//Fun��o para cadastrar dados dos jogadores no jogo
void cadastro(fila_jogador *jogad,int quant_jogado){
	int i=0,idades,vidas=5,b;
	char nome[30];
	for(i=0;i<quant_jogado;i++){
		printf("\n\n%d � Jogador:\n\n",i+1);
		printf("Digite o nome jogador: ");
		setbuf(stdin,NULL);
		gets(nome);
		printf("Digite a idade do jogador: ");
		scanf("%d",&idades);
		b = inserir_jogador(jogad,nome,idades,vidas);
	}	
}

//Fun��o para mostrar dados dos jogadores
void mostra_dados(fila_jogador *jogad){
	int i=0;
	for(i=0;i<jogad->final;i++){
		system("cls");
		printf("\n\n%d� Jogador:\n\n",i+1);
		printf("Nome:%s\n",jogad->jogo[i].nome);
		printf("Idade:%d\n",jogad->jogo[i].idade);
		printf("Vidas:%d",jogad->jogo[i].numero_vidas);	
	}
}


//Fun��o para distribuir cartas para os jogadores
void distribui_cartas(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,baralho *p,baralho *q,int cont,int comec){
	int i=0,j=0,num,nai,b;
	for(i=comec;i<jogad->final;i++){
		printf("\n\n\n");
		for(j=0;j<cont;j++){
			b = remove_p(p,q,&num,&nai);
			if(b == 1){
				libera(p);
				p = criapilha();
				embaralha_cartas(q,p,40);
				b = remove_p(p,q,&num,&nai);
			}
			if(estacheia(cartas_ma)){
				break;
			}
			else{
				cartas_ma[i].jogo[j].numero = num;
				cartas_ma[i].jogo[j].naipe = nai;
				cartas_ma[i].final++;
			}
		}
	}
	//Fun��o ainda em teste
	for(i=0;i<comec;i++){
		printf("\n\n\n");
		for(j=0;j<cont;j++){
			b = remove_p(p,q,&num,&nai);
			if(b == 1){
				libera(p);
				p = criapilha();
				embaralha_cartas(q,p,40);
				b = remove_p(p,q,&num,&nai);
			}
			if(estacheia(cartas_ma)){
				break;
			}
			else{
				cartas_ma[i].jogo[j].numero = num;
				cartas_ma[i].jogo[j].naipe = nai;
				cartas_ma[i].final++;
			}
		}
	}
	//Exibir dados dos jogadores
	for(i=0;i<jogad->final;i++){
		printf("\n\nJogador %s:\n\nCartas:\n\n",jogad->jogo[i].nome);
		for(j=0;j<cartas_ma[i].final;j++){
			printf("Numero: %2d  ",cartas_ma[i].jogo[j].numero);
			printf("Naipe: %2d\n\n",cartas_ma[i].jogo[j].naipe);
		}
		printf("Vidas:%d",jogad->jogo[i].numero_vidas);
		printf("\n\n");
		system("cls");
	}
	return;
}

//Fun��o Remove pilha
int remove_p(baralho *p,baralho *q,int *valor,int *num){
	if(estahvazia(p)){
		return 1;
	}
	else{
		p->topo--;
		*valor = p->jogo[p->topo].numero;
		*num = p->jogo[p->topo].naipe;
		return 0;
	}
}

//Fun��o para determinar a quantidade de jogadores
void numero_jogadores(int *quant_jogado){
	int num;
	do{
		printf("\nDigite a quantidade de jogadores do jogo: ");
		scanf("%d",&num);
		*quant_jogado = num;
		if(num<2 || num >8){
			printf("\nQuantidade de jogadores invalido!!!\n");
		}
	}while(num<2 || num >8);	
}

//Fun��o para perguntar quantas rodadas o jogador faz
void pergunta_jogador(FILE *arquivo,cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,carta *jogadores,int *vet,int *p,int comec){
	
	int mata,i,j,val;
	for(i=comec;i<jogad->final;i++){
			printf("\n\nJogador %s:\n\nCartas:\n\n",jogad->jogo[i].nome);
			fprintf(arquivo,"\n\nJogador %s:\n",jogad->jogo[i].nome);
			for(j=0;j<cartas_ma[i].final;j++){
				printf("Numero: %2d  ",cartas_ma[i].jogo[j].numero);
				printf("Naipe: %2d\n\n",cartas_ma[i].jogo[j].naipe);
			}
			printf("Vidas:%d",jogad->jogo[i].numero_vidas);
			fprintf(arquivo,"Vidas: %d\n\n",jogad->jogo[i].numero_vidas);
			printf("\nQuantas rodadas voc� faz: ");
			scanf("%d",&mata);
			verifica_rod(vet,mata,*p,cartas_ma[i].final,comec,val);
			fprintf(arquivo,"Rodadas que faz: %d",vet[*p]);
			(*p)++;
			printf("\n\n");
			system("cls");
	}
	
	
	val = *p;
	
	//Parte para ver quantas rodadas o jogador faz	
	for(i=0;i<comec;i++){
			printf("\n\nJogador %s:\n\nCartas:\n\n",jogad->jogo[i].nome);
			fprintf(arquivo,"\n\nJogador %s:\n",jogad->jogo[i].nome);
			for(j=0;j<cartas_ma[i].final;j++){
				printf("Numero: %2d  ",cartas_ma[i].jogo[j].numero);
				printf("Naipe: %2d\n\n",cartas_ma[i].jogo[j].naipe);
			}
			printf("Vidas:%d",jogad->jogo[i].numero_vidas);
			fprintf(arquivo,"Vidas: %d\n\n",jogad->jogo[i].numero_vidas);
			printf("\nQuantas rodadas voc� faz: ");
			scanf("%d",&mata);
			*p = i;
			verifica_rod(vet,mata,*p,cartas_ma[i].final,comec,val);
			fprintf(arquivo,"Rodadas que faz: %d",vet[*p]);
			(*p)++;
			printf("\n\n");
			system("cls");
		}	
}

//Fun��o verifica vencedor
int vencedor(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado){
	int i,cont=0,pos=0;
	for(i=0;i<jogad->final;i++){
		if(jogad->jogo[i].numero_vidas > 0){
			cont++;
			pos = i;
		}
	}	
	if(cont == 1){
		return pos;	
	}
	else{
		return -1;
	}
}

//Fun��o para remover cartas da m�o do jogador
void remove(cartas_mao_jogad *cartas_ma,int i,int *op,int *nume,int *nai){
	int nu=0;
	do {
		printf("\nEscolha a posi��o de uma carta para jogar na rodada: ");
		scanf("%d",&nu);
	}while(nu >cartas_ma[i].final-1);
	*op = nu;
	*nume = cartas_ma[i].jogo[*op].numero;
	*nai = cartas_ma[i].jogo[*op].naipe;
	int j;
	for(j = *op;j<cartas_ma[i].final-1;j++){
		cartas_ma[i].jogo[j].numero = cartas_ma[i].jogo[j+1].numero;
		cartas_ma[i].jogo[j].naipe = cartas_ma[i].jogo[j+1].naipe;
	}
	cartas_ma[i].final -= 1;		
	return;
}


//Fun��o para verificar quantas rodadas pode fazer
void verifica_rod(int *vetor,int rod,int k,int final,int comec,int val){
	int soma = 0,i=0;
	
	if(k == comec && rod <= final){
		vetor[k] = rod;
	}
	
	else if(k == comec && rod > final){
		while( rod > final ){
			printf("Digite a quantidade de rodadas que voce faz: ");
			scanf("%d",&rod);
		}
		vetor[k] = rod;
	}
	
	else{
		
		//if armazena rodadas que jogador pode fazer
		if(k == comec){
			while( rod > final ){
				printf("Digite a quantidade de rodadas que voce faz: ");
				scanf("%d",&rod);
			}
			vetor[k] = rod;
		}
		///////
		
		else if( k < comec){
			for(i=comec;i<val;i++){
				soma+= vetor[i];
			}
			while(((soma + rod) == final) || (rod > final)){
				printf("Digite a quantidade de rodadas que voce faz: ");
				scanf("%d",&rod);
			}
			vetor[k] = rod;
		}
		
		
		else{
			
			for(i=comec;i<k;i++){
				soma+= vetor[i];
			}
			while(((soma + rod) == final) || (rod > final)){
				printf("Digite a quantidade de rodadas que voce faz: ");
				scanf("%d",&rod);
			}
			vetor[k] = rod;	
		}
		
	}
}

//Fun��o do jogo em andamento
void jogo(FILE *arquivo,cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado,carta *jogadores,int comec,int *posi){
	
	int i,j,op,nume,nai;
	
	if(*posi != -1){
		comec = *posi;
	}
	
	for(i=comec;i<jogad->final;i++){
			printf("\n\nJogador %s:\n\nCartas:\n\n",jogad->jogo[i].nome);
			fprintf(arquivo,"\nJogador %s:\n\n",jogad->jogo[i].nome);
			for(j=0;j<cartas_ma[i].final;j++){
				printf("Numero: %2d  ",cartas_ma[i].jogo[j].numero);
				printf("Naipe: %2d\n\n",cartas_ma[i].jogo[j].naipe);
			}
			printf("Vidas:%d",jogad->jogo[i].numero_vidas);
			remove(cartas_ma,i,&op,&nume,&nai);
			jogadores[i].numero = nume;
			jogadores[i].naipe = nai;
			fprintf(arquivo,"Carta escolhida: N�mero: %d  Naipe: %d\n\n",jogadores[i].numero,jogadores[i].naipe);
			printf("\n\n");
			system("cls");
		}
		
		//Essa parte come�a os jogadores que n�o jogaram depois do sentido hor�rio
	for(i=0;i<comec;i++){
		printf("\n\nJogador %s:\n\nCartas:\n\n",jogad->jogo[i].nome);
		fprintf(arquivo,"\nJogador %s:\n\n",jogad->jogo[i].nome);
		for(j=0;j<cartas_ma[i].final;j++){
			printf("Numero: %2d  ",cartas_ma[i].jogo[j].numero);
			printf("Naipe: %2d\n\n",cartas_ma[i].jogo[j].naipe);
		}
		printf("Vidas:%d",jogad->jogo[i].numero_vidas);
		remove(cartas_ma,i,&op,&nume,&nai);
		jogadores[i].numero = nume;
		jogadores[i].naipe = nai;
		fprintf(arquivo,"Carta escolhida: N�mero: %d  Naipe: %d\n\n",jogadores[i].numero,jogadores[i].naipe);
		printf("\n\n");
		system("cls");
	}
}

//Fun��o para verificar a pontua��o
void pontuacao(int quant_jogado,carta *jogadores,int *vetor,int *posi){
	
	int pos,i;
	
	//Vari�vel para armazenar maior valor junto naipe, para compara o naipe quando as cartas forem iguais
	carta maior;
	maior.numero=0;
	maior.naipe=0;
	
	//Fun��o para facilitar a compara��o das maiores cartas atribuindo um valor altissimo para elas 
	for(i=0;i<quant_jogado;i++){
	  //zape
		if(jogadores[i].numero == 4 && jogadores[i].naipe == 4){
			jogadores[i].numero = 50;
		}
		// 7 copas
		if(jogadores[i].numero == 7 && jogadores[i].naipe == 1){
			jogadores[i].numero = 49;
		}
		//�S de espadas
		if(jogadores[i].numero == 14 && jogadores[i].naipe == 3){
			jogadores[i].numero = 48;
		}
		//7 de ouros
		if(jogadores[i].numero == 7 && jogadores[i].naipe == 2){
			jogadores[i].numero = 47;
		}
		//N�mero 3
		if(jogadores[i].numero == 3 ){
			jogadores[i].numero = 46;
		}
		//N�mero 2
		if(jogadores[i].numero == 2){
			jogadores[i].numero = 45;
		}
	}
	
	//Trecho para comparar as maiores cartas e comparar quando as cartas forem iguais considerar o valor pelo naipe		
	for(i=0;i<quant_jogado;i++){
		if(jogadores[i].numero == maior.numero){
			if(jogadores[i].naipe == 4 && maior.naipe == 1){
				maior.numero = jogadores[i].numero;
				maior.naipe  = jogadores[i].naipe;
				pos = i;
			}
			else if(jogadores[i].naipe == 4 && maior.naipe == 3){
				maior.numero = jogadores[i].numero;
				maior.naipe  = jogadores[i].naipe;
				pos = i;
			}
			else if(jogadores[i].naipe == 4 && maior.naipe == 2){
				maior.numero = jogadores[i].numero;
				maior.naipe  = jogadores[i].naipe;
				pos = i;
			}
			else if(jogadores[i].naipe == 1 && maior.naipe == 3){
				maior.numero = jogadores[i].numero;
				maior.naipe  = jogadores[i].naipe;
				pos = i;
			}
			else if(jogadores[i].naipe == 1 && maior.naipe == 2){
				maior.numero = jogadores[i].numero;
				maior.naipe  = jogadores[i].naipe;
				pos = i;
			}
			else if(jogadores[i].naipe == 3 && maior.naipe == 2){
				maior.numero = jogadores[i].numero;
				maior.naipe  = jogadores[i].naipe;
				pos = i;
			}
			else{
				//N�o faz nada
			}	
		}
		else if(jogadores[i].numero > maior.numero){
			maior.numero = jogadores[i].numero;
			maior.naipe  = jogadores[i].naipe;
			pos = i;
		}	
	}
	
	//Trecho de codigo que compara a posi��o do jogador de maior carta com sua posi��o no vetor jogador, se forem iguais soma um ponto 
	for(i=0;i<quant_jogado;i++){
		if(i == pos){
			vetor[i] += 1;
		}
	}
	*posi = pos;
	return;
}

//Fun��o para comparar o numero de rodadas que fazia com a pontua��o
void compara(fila_jogador *jogad,int quant_jogado,int *vet,int *vetor){
	int i=0,soma=0;
	for(i=0;i<quant_jogado;i++){
		if(vet[i] != vetor[i]){
			if(vet[i] > vetor[i]){
				soma = vet[i] - vetor[i];
			}
			if(vet[i] < vetor[i]){
				soma = vetor[i] - vet[i];
			}
			jogad->jogo[i].numero_vidas -= soma;
		}
	}
	return;
}

//Fun��o para reposionar jogadores depois que tiver vida igual a zero
void realoca_jogadores(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int *quant_jogado,carta *jogadores,int pos){
	int j;
	for(j = pos;j<jogad->final-1;j++){
		jogad->jogo[j].idade = jogad->jogo[j+1].idade;
		jogad->jogo[j].numero_vidas = jogad->jogo[j+1].numero_vidas;
		strcpy(jogad->jogo[j].nome,jogad->jogo[j+1].nome);
	}		
	return;	
}


//Fun��o para realocar jogador na posi��o eliminando os que tem vida igual a zero
void verificar_vidas(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int *quant_jogado,carta *jogadores){
	int i=0;
	for(i=0;i<jogad->final;i++){
		if(jogad->jogo[i].numero_vidas <= 0 && i < *quant_jogado-1){
			realoca_jogadores(cartas_ma,jogad,quant_jogado,jogadores,i);
			*quant_jogado-=1;
			jogad->final--;
			i=-1;
		}
		if(jogad->jogo[i].numero_vidas <= 0 && i == *quant_jogado-1){
			*quant_jogado-=1;
			jogad->final--;
			i=-1;	
		}
	}
	return;
}

//Fun��o para Opcao 2 do menu
void opcao_dois(){
	printf("\nAs cartas mais fortes do baralho s�o: \n\n");
	printf("Zape 4 - 4\n\nSete copas 7 - 1\n\n�s de espadas 14 - 3\n\nSete de ouros 7 - 2\n");
	printf("\n\nOrdem das cartas ( da menor para maior ):\n\n");
	printf("4,5,6,7,11,12,13,14,2,3\n\n");
	printf("Ocorreu as trocas de cartas pelos n�meros:\n\n");
	printf("Q = 11\n\nJ = 12\n\nK = 13\n\n�s = 14\n\n");
	printf("Observa��o: as escolhas das cartas � a partir da posi��o 0 !!!\n\n");
	return;
}

//Fun��o verifica empate do jogo
int empate(cartas_mao_jogad *cartas_ma,fila_jogador *jogad,int quant_jogado){
	int i,cont=0,pos=0;
	for(i=0;i<quant_jogado;i++){
		if(jogad->jogo[i].numero_vidas <= 0){
			cont++;
		}
	}	
	if(cont == quant_jogado){
		return 1;	
	}
	else{
		return 0;
	}
}
